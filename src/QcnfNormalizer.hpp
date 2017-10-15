#ifndef QBF2ASP_QBF2ASP_QCNFNORMALIZER_H_
#define QBF2ASP_QBF2ASP_QCNFNORMALIZER_H_

#include <qbf2asp/global>
#include <logic/parsers>
#include <set>
#include <utility>
#include <list>

namespace qbf2asp
{

    using std::pair;
    using std::list;
    using std::set;
  
    using logic::IQbfClause;
    using logic::IQbfInstance;
    using logic::IQbfInstanceBuilder;
    using logic::variable_t;

    class QBF2ASP_LOCAL VariableGenerator
    {
      public:
	VariableGenerator(const IQbfInstance * instance);
	variable_t freshVariable();
      private:
	const IQbfInstance * instance = NULL;
	variable_t variableCounter;
    };
  
    class QBF2ASP_LOCAL QbfLiteral {
    private:
	bool polarity_;
	variable_t variable_;
    public:
	QbfLiteral(variable_t variable, bool polarity);
	variable_t variable(void) const;
	bool polarity(void) const;
	bool operator==(const QbfLiteral & other);
	bool operator<(const QbfLiteral & other);
    };
  
    class QBF2ASP_API QcnfNormalizer
    {
      public:
	QcnfNormalizer(unsigned int maxClauseSize);

	unsigned int maxClauseSize() const;
    
	virtual pair<list<QbfLiteral>*,list<QbfLiteral>*> partitionClause(
	    list<QbfLiteral> * literals, const IQbfInstance & instance) = 0;

	const IQbfInstance * normalize(const IQbfInstance & instance);

      private:
	unsigned int maxClauseSize_;

      private:
	list<list<QbfLiteral> *> * normalizeClause(
	    const IQbfClause & clause,
	    set<variable_t> * variables,
	    VariableGenerator variableGenerator,
	    const IQbfInstance & instance);
    
    };

    class QBF2ASP_API NaiveQcnfNormalizer : public QcnfNormalizer
    {
      public:
	NaiveQcnfNormalizer(unsigned int maxClauseSize);
	
	virtual pair<list<QbfLiteral> *, list<QbfLiteral> *> partitionClause(
	    list<QbfLiteral> * literals, const IQbfInstance & instance);
    };

    unsigned int clauseCount(const IQbfInstance & instance);
  
    void QBF2ASP_API printQbfQdimacs(const IQbfInstance & instance);

    void printQbfQdimacs(const IQbfInstance & instance);

    const IQbfInstance * buildQbfInstance(
	const list<list<QbfLiteral>*> * newClauses,
	const set<variable_t> * splitVariables,
	const IQbfInstance & instance);
    
    void copyLiteralListToClause(list<QbfLiteral> * literals, IQbfClause & clause);
    
    list<QbfLiteral> * clauseToLiteralList(const IQbfClause & clause);

}

#endif // QBF2ASP_QBF2ASP_QCNFNORMALIZER_H_
