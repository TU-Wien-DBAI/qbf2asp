#ifndef QBF2ASP_QBF2ASP_IQBFCLAUSE_H_
#define QBF2ASP_QBF2ASP_IQBFCLAUSE_H_

#include <qbf2asp/global>

#include <qbf2asp/Variable.hpp>

#include <sharp/main>

namespace qbf2asp
{
	class IQbfInstance;

	class QBF2ASP_API IQbfClause
	{
	protected:
		IQbfClause &operator=(IQbfClause &) { return *this; }

	public:
		typedef sharp::IConstEnumerator<variable_t>::Iterator const_iterator;

		virtual ~IQbfClause() = 0;

		virtual void addVariable(variable_t variable) = 0;
		virtual void addVariable(variable_t variable, bool negated) = 0;

		virtual const IQbfInstance &instance() const = 0;
		
		virtual bool contains(variable_t variable) const = 0;
		virtual bool isNegated(variable_t variable) const = 0;

		virtual bool checkSatisfaction(
				const variable_vector &trueVariables,
				const variable_vector &falseVariables) const = 0;

		virtual const_iterator begin() const = 0;
		virtual const_iterator end() const = 0;

	}; // class IQbfClause

	inline IQbfClause::~IQbfClause() { }

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_IQBFCLAUSE_H_
