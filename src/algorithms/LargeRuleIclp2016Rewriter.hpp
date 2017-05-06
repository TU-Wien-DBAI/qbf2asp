#ifndef QBF2ASP_QBF2ASP_LARGERULEICLP2017REWRITER_H_
#define QBF1ASP_QBF2ASP_LARGERULEICLP2017REWRITER_H_

#include <qbf2asp/global>

#include <qbf2asp/IQbf2AspRewriter.hpp>

namespace qbf2asp
{

	class QBF2ASP_LOCAL LargeRuleIclp2016Rewriter : public IQbf2AspRewriter
	{
	protected:
		LargeRuleIclp2016Rewriter &operator=(LargeRuleIclp2016Rewriter &)
		{ return *this; }

	public:
		LargeRuleIclp2016Rewriter();
		virtual ~LargeRuleIclp2016Rewriter() override;

		virtual void rewrite(
				const logic::IQbfInstance &instance) const override;

		virtual void rewrite(
				const logic::IQbfInstance &instance,
				std::ostream &out) const override;
		
	}; // class LargeRuleIclp2016Rewriter

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_LARGERULEICLP2017REWRITER_H_
