#ifndef QBF2ASP_QBF2ASP_IQBFINSTANCE_H_
#define QBF2ASP_QBF2ASP_IQBFINSTANCE_H_

#include <qbf2asp/global>

#include <qbf2asp/Variable.hpp>
#include <qbf2asp/Clause.hpp>
#include <qbf2asp/IQbfClause.hpp>

#include <sharp/main>

#include <htd/main.hpp>

#include <string>
#include <utility>
#include <cstddef>

namespace qbf2asp
{

	class QBF2ASP_API IQbfInstance : public sharp::IInstance
	{
	protected:
		IQbfInstance &operator=(IQbfInstance &) { return *this; }

	public:
		typedef sharp::IConstEnumerator<IQbfClause>::Iterator const_iterator;

		virtual ~IQbfInstance() = 0;

		virtual void addVariableName(
				variable_t variable,
				const std::string &name) = 0;

		virtual void addVariable(variable_t variable) = 0;
		virtual void addClause(IQbfClause *clause) = 0;

		virtual bool isClause(htd::vertex_t vertex) const = 0;
		virtual bool isVariable(htd::vertex_t vertex) const = 0;

		virtual const IQbfClause &clause(clause_t clause) const = 0;

		virtual const_iterator begin() const = 0;
		virtual const_iterator end() const = 0;

	}; // class IQbfInstance

	inline IQbfInstance::~IQbfInstance() { }

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_IQBFINSTANCE_H_
