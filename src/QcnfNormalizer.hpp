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
    class QBF2ASP_LOCAL VariableGenerator
    {
      public:
	VariableGenerator(const logic::IQbfInstance * instance);
	logic::variable_t freshVariable();
      private:
	const logic::IQbfInstance * instance = NULL;
	logic::variable_t variableCounter;
    };
  
    class QBF2ASP_LOCAL QbfLiteral {
    private:
	bool polarity_;
	logic::variable_t variable_;
    public:
	QbfLiteral(logic::variable_t variable, bool polarity);
	logic::variable_t variable(void) const;
	bool polarity(void) const;
	bool operator==(const QbfLiteral & other);
	bool operator<(const QbfLiteral & other);
    };
  
    class QBF2ASP_API QcnfNormalizer
    {
      public:
	QcnfNormalizer(unsigned int maxClauseSize);

	unsigned int maxClauseSize() const;
    
	virtual std::pair<std::list<QbfLiteral>*,std::list<QbfLiteral>*> partitionClause(
	    std::list<QbfLiteral> * literals, const logic::IQbfInstance & instance) = 0;

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

    class QBF2ASP_API NaiveQcnfNormalizer : public QcnfNormalizer
    {
      public:
	NaiveQcnfNormalizer(unsigned int maxClauseSize);
	
	virtual std::pair<std::list<QbfLiteral> *, std::list<QbfLiteral> *> partitionClause(
	    std::list<QbfLiteral> * literals, const logic::IQbfInstance & instance);
    };

    unsigned int clauseCount(const logic::IQbfInstance & instance);
  
    void QBF2ASP_API print_qbf_qdimacs(
        std::ostream & out,
        const logic::IQbfInstance & instance);

    const logic::IQbfInstance * buildQbfInstance(
	const std::list<std::list<QbfLiteral>*> * newClauses,
	const std::set<logic::variable_t> * splitVariables,
	const logic::IQbfInstance & instance);
    
    void copyLiteralListToClause(std::list<QbfLiteral> * literals, logic::IQbfClause & clause);
    
    std::list<QbfLiteral> * clauseToLiteralList(const logic::IQbfClause & clause);

}

#endif // QBF2ASP_QBF2ASP_QCNFNORMALIZER_H_
