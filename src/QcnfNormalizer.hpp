#ifndef QBF2ASP_QBF2ASP_QCNFNORMALIZER_H_
#define QBF2ASP_QBF2ASP_QCNFNORMALIZER_H_

#include <qbf2asp/global>
#include <logic/parsers>

#include <set>
#include <utility>
#include <list>
#include <ostream>

namespace qbf2asp
{
    /**
     * @brief A variable generator.
     * This class is intended to create variables that do
     * not intersect the variables of a given formula.
     */
    class QBF2ASP_LOCAL VariableGenerator
    {
      public:
        
        /**
         * @brief Constructs a new variable generator.
         * @param instance The formula associated with this variable generator.
         */
	VariableGenerator(const logic::IQbfInstance * instance);

        /**
         * @brief Creates a new variable.
         * @return A variable that has not been previously returned by
         * a call to this method and which does not occur in the
         * associated formula.
         */
	logic::variable_t freshVariable();
        
      private:

        /** @brief The formula associated to this variable generator */
	const logic::IQbfInstance * instance = NULL;

        /** @brief A counter to keep track of the previously
         * enumerated variables. 
         */
	logic::variable_t variableCounter;
    };

    /**
     * @brief This class represents propositional literals.
     * A literal consists of a variable and a polarity. The polarity
     * indicates whether the literal is negated or not.
     */
    class QBF2ASP_LOCAL QbfLiteral {
        
    private:
        
	bool polarity_;
        
	logic::variable_t variable_;
        
    public:

        /**
         * @brief Constructs a new literal.
         * @param variable The literal's variable.
         * @param polarity The literal's polarity.
         */
	QbfLiteral(logic::variable_t variable, bool polarity);

        /**
         * @brief Returns a literal's variable.
         */
	logic::variable_t variable(void) const;

        /**
         * @brief Returns a literal's polarity.
         */
	bool polarity(void) const;

        /**
         * @brief Compares literals for equality.
         * @param other A literal.
         * @return Returns `true` if this literal and other have the
         * same variable and the same polarity, `false` otherwise.
         */
	bool operator==(const QbfLiteral & other);

        /**
         * @brief Compares literals.
         * @param other A literal.
         * @return Returns `true` if either this literal has negative
         * polarity and other has positive polarity or this literal's
         * variable precedes the other literal's variable. Otherwise
         * `false` is returned.
         */
	bool operator<(const QbfLiteral & other);
    };

    /**
     * @brief Normalizes QBF formulas to formulas having clauses of a
     * given fixed maximum size.
     */
    class QBF2ASP_API QcnfNormalizer
    {
      public:

        /**
         * @brief Constructs a new normalizer.
         * @param maxClauseSize The maximum clause size to be used by
         * this normalizier.
         */
	QcnfNormalizer(unsigned int maxClauseSize);

        /**
         * @brief Retrieves the maximum clause size of this
         * normalizer.
         */
	unsigned int maxClauseSize() const;
    
	virtual std::pair<std::list<QbfLiteral>*,std::list<QbfLiteral>*> partitionClause(
	    std::list<QbfLiteral> * literals, const logic::IQbfInstance & instance) = 0;

        /**
         * @brief Normalizes a given QBF formula.
         * @param instance The formula that is to be normalized.
         * @return A new satisfiability equivalent formula whose
         * clauses have size less than or equal to the maximum clause
         * size of this normalizer. The caller is responsible for
         * freeing the resulting instance.
         */
	const logic::IQbfInstance * normalize(const logic::IQbfInstance & instance);

      private:

	unsigned int maxClauseSize_;

      private:
        
	std::list<std::list<QbfLiteral> *> * normalizeClause(
	    const logic::IQbfClause & clause,
	    std::set<logic::variable_t> * variables,
	    VariableGenerator variableGenerator,
	    const logic::IQbfInstance & instance);
    
    };

    /**
     * @brief Represents QBF normalizers with trivial partitioning.
     * The clause is partitioned into the first maximum clause size -
     * 1 elements and the remaining elements.
     */
    class QBF2ASP_API NaiveQcnfNormalizer : public QcnfNormalizer
    {
      public:

        /**
         * @see qbf2asp::QcnfNormalizer::QcnfNormalizer().
         */
	NaiveQcnfNormalizer(unsigned int maxClauseSize);

        /**
         * @see qbf2asp::QcnfNormalizer::partitionClause().
         * @return The first component of the returned pair contains
         * the first maximum clause size - 1 elements of the input
         * clause and the second component contains the remaining
         * elements.
         */
	virtual std::pair<std::list<QbfLiteral> *, std::list<QbfLiteral> *> partitionClause(
	    std::list<QbfLiteral> * literals, const logic::IQbfInstance & instance);
    };

    /**
     * @brief Computes the number of clauses of a QBF.
     */
    unsigned int clauseCount(const logic::IQbfInstance & instance);

    /**
     * @brief Prints a QBF in QDIMACS format.
     * @param out The QBF is printed to this output stream.
     * @param instance The QBF that is printed.
     */
    void QBF2ASP_API print_qbf_qdimacs(
        std::ostream & out,
        const logic::IQbfInstance & instance);

    /**
     * @brief Constructs a QBF.
     * @param The clauses of the new QBF.
     * @param The variables that were introduced during splitting.
     * @param The original instance.
     * @return A new instance having clauses newClauses. The caller is
     * responsible for freeing the returned instance.
     */
    const logic::IQbfInstance * buildQbfInstance(
	const std::list<std::list<QbfLiteral>*> * newClauses,
	const std::set<logic::variable_t> * splitVariables,
	const logic::IQbfInstance & instance);

    void copyLiteralListToClause(std::list<QbfLiteral> * literals, logic::IQbfClause & clause);
    
    std::list<QbfLiteral> * clauseToLiteralList(const logic::IQbfClause & clause);

}

#endif // QBF2ASP_QBF2ASP_QCNFNORMALIZER_H_
