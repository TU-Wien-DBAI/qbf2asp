#ifndef QBF2ASP_QBF2ASP_IQBFINSTANCE_H_
#define QBF2ASP_QBF2ASP_IQBFINSTANCE_H_

#include <qbf2asp/global>

#include <qbf2asp/Variable.hpp>
#include <qbf2asp/Clause.hpp>
#include <qbf2asp/IQbfClause.hpp>

#include <sharp/main>

#include <htd/main.hpp>

#include <unordered_set>

namespace qbf2asp
{

	class QBF2ASP_API IQbfInstance : public sharp::IInstance
	{
	protected:
		IQbfInstance &operator=(IQbfInstance &) { return *this; }

	public:
		typedef sharp::IConstEnumerator<IQbfClause>::Iterator const_iterator;

		virtual ~IQbfInstance() = 0;

		virtual void setCnf() = 0;
		virtual void setDnf() = 0;
		virtual void setVariableCount(variable_t variableCount) = 0;

		virtual void setQuantifierLevel(variable_t variable, short level) = 0;
		virtual IQbfClause &newClause() = 0;

		virtual bool isClause(htd::vertex_t vertex) const = 0;
		virtual bool isVariable(htd::vertex_t vertex) const = 0;
		virtual bool isExistential(variable_t variable) const = 0;
		virtual bool isUniversal(variable_t variable) const = 0;
		virtual short quantifierLevel(variable_t variable) const = 0;
		virtual short outermostQuantifierLevel() const = 0;
		virtual const std::unordered_set<variable_t> &variables(
				short level) const = 0;
		virtual variable_t variableCount() const = 0;
		virtual bool isCnf() const = 0;
		virtual bool isDnf() const = 0;

		virtual const IQbfClause &clause(clause_t clause) const = 0;

		virtual const_iterator begin() const = 0;
		virtual const_iterator end() const = 0;

	}; // class IQbfInstance

	inline IQbfInstance::~IQbfInstance() { }

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_IQBFINSTANCE_H_
