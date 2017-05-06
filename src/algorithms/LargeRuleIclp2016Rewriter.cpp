#include "../preamble.h"
#include "LargeRuleIclp2016Rewriter.hpp"

namespace qbf2asp
{
	using logic::IQbfInstance;

	using std::ostream;
	using std::endl;

	LargeRuleIclp2016Rewriter::LargeRuleIclp2016Rewriter() { }

	LargeRuleIclp2016Rewriter::~LargeRuleIclp2016Rewriter() { }

	void LargeRuleIclp2016Rewriter::rewrite(
			const IQbfInstance &instance) const
	{
		rewrite(instance, std::cout);
	}

	void LargeRuleIclp2016Rewriter::rewrite(
			const IQbfInstance &instance,
			ostream &out) const
	{
		// TODO
		out << "Implement ICLP2016 rewriting here." << endl;
	}

} // namespace qbf2asp
