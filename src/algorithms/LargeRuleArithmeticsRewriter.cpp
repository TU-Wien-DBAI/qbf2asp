#include "../preamble.h"
#include "LargeRuleArithmeticsRewriter.hpp"

namespace qbf2asp
{
	using logic::IQbfInstance;

	using std::ostream;
	using std::endl;

	LargeRuleArithmeticsRewriter::LargeRuleArithmeticsRewriter() { }

	LargeRuleArithmeticsRewriter::~LargeRuleArithmeticsRewriter() { }

	void LargeRuleArithmeticsRewriter::rewrite(
			const IQbfInstance &instance) const
	{
		rewrite(instance, std::cout);
	}

	void LargeRuleArithmeticsRewriter::rewrite(
			const IQbfInstance &instance,
			ostream &out) const
	{
		// TODO
		out << "Implement arithmetics rewriting here." << endl;
	}

} // namespace qbf2asp
