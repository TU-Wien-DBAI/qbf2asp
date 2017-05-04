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

		virtual void setCnf() override;
		virtual void setDnf() override;
		virtual void setVariableCount(variable_t variableCount) override;

		virtual void setQuantifierLevel(
				variable_t variable,
				short level) override;

		virtual IQbfClause &newClause() override;

		virtual htd::IHypergraph *toHypergraph() const override;

		virtual bool isClause(htd::vertex_t vertex) const override;
		virtual bool isVariable(htd::vertex_t vertex) const override;
		virtual bool isExistential(variable_t variable) const override;
		virtual bool isUniversal(variable_t variable) const override;
		virtual short quantifierLevel(variable_t variable) const override;
		virtual short outermostQuantifierLevel() const override;
		virtual const std::unordered_set<variable_t> &variables(
				short level) const override;
		virtual variable_t variableCount() const override;
		virtual bool isCnf() const override;
		virtual bool isDnf() const override;

		virtual const IQbfClause &clause(clause_t clause) const override;

		virtual const_iterator begin() const override;
		virtual const_iterator end() const override;

	private:
		bool dnf_;
		variable_t variableCount_;
		std::unordered_map<variable_t, short> quantifierLevels_;
		std::unordered_map<short, std::unordered_set<variable_t> > variables_;
		std::unordered_set<variable_t> unquantified_;
		short outermostQuantifierLevel_;
		std::vector<IQbfClause *> clauses_;

		typedef sharp::ConstEnumerator<
			IQbfClause, 
			std::vector<IQbfClause *>::const_iterator> ConstEnum;

	}; // class QbfInstance

} // namespace qbf2asp

#endif // QBF2ASP_INSTANCES_QBFINSTANCE_H_
