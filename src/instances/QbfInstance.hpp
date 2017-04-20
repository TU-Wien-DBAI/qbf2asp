#ifndef QBF2ASP_INSTANCES_QBFINSTANCE_H_
#define QBF2ASP_INSTANCES_QBFINSTANCE_H_

#include <qbf2asp/global>

#include <qbf2asp/IQbfInstance.hpp>

#include <unordered_map>
#include <vector>

namespace qbf2asp
{
	class QBF2ASP_LOCAL QbfInstance : public IQbfInstance
	{
	public:
		QbfInstance();
		virtual ~QbfInstance();

		virtual void addVariableName(
				variable_t variable,
				const std::string &name) override;
		
		virtual void addVariable(variable_t variable) override;
		virtual void addClause(IQbfClause *clause) override;

		virtual htd::IHypergraph *toHypergraph() const override;

		virtual bool isClause(htd::vertex_t vertex) const override;
		virtual bool isVariable(htd::vertex_t vertex) const override;

		virtual const IQbfClause &clause(clause_t clause) const override;

		virtual const_iterator begin() const override;
		virtual const_iterator end() const override;

	private:
		std::size_t maxVariable_;
		std::unordered_map<variable_t, std::string> variableNames_;
		std::vector<IQbfClause *> clauses_;

		typedef sharp::ConstEnumerator<
			IQbfClause, 
			std::vector<IQbfClause *>::const_iterator> ConstEnum;

	}; // class QbfInstance

} // namespace qbf2asp

#endif // QBF2ASP_INSTANCES_QBFINSTANCE_H_
