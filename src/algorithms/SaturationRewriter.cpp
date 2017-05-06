#include "../preamble.h"
#include "SaturationRewriter.hpp"

namespace qbf2asp
{
	using logic::IQbfInstance;

	using std::ostream;
	using std::endl;

	SaturationRewriter::SaturationRewriter() { }

	SaturationRewriter::~SaturationRewriter() { }

	void SaturationRewriter::rewrite(
			const IQbfInstance &instance) const
	{
		rewrite(instance, std::cout);
	}

	void SaturationRewriter::rewrite(
			const IQbfInstance &instance,
			ostream &out) const
	{
		// TODO
		out << "Implement classic saturation rewriting here." << endl;
	}

} // namespace qbf2asp
