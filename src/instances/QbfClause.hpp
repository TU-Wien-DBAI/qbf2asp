#ifndef QBF2ASP_INSTANCES_QBFCLAUSE_H_
#define QBF2ASP_INSTANCES_QBFCLAUSE_H_

#include <qbf2asp/global>

#include <qbf2asp/IQbfClause.hpp>

#include <unordered_set>

namespace qbf2asp
{
	class QBF2ASP_LOCAL QbfClause : public IQbfClause
	{
	public:
		QbfClause(const IQbfInstance &instance);
		virtual ~QbfClause();

		virtual void addVariable(variable_t variable) override;
		virtual void addVariable(variable_t variable, bool negated) override;

		virtual const IQbfInstance &instance() const override;
		
		virtual bool contains(variable_t variable) const override;
		virtual bool isNegated(variable_t variable) const override;

		virtual bool checkSatisfaction(
				const variable_vector &trueVariables,
				const variable_vector &falseVariables) const override;

		virtual const_iterator begin() const override;
		virtual const_iterator end() const override;

	private:
		const IQbfInstance &instance_;
		std::unordered_set<variable_t> variables_;
		std::unordered_set<variable_t> negated_;

		typedef sharp::ConstEnumerator<
			variable_t,
			std::unordered_set<variable_t>::const_iterator> ConstEnum;

	}; // class QbfClause

} // namespace qbf2asp

#endif // QBF2ASP_INSTANCES_QBFCLAUSE_H_
