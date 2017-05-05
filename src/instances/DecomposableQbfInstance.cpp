#include "../preamble.h"
#include <qbf2asp/DecomposableQbfInstance.hpp>

#include <qbf2asp/create.hpp>

#include <memory>

namespace qbf2asp
{
	using htd::IHypergraph;

	using std::unique_ptr;

	/*
	IHypergraph *DecomposableQbfInstance::toHypergraph()
	{
		unique_ptr<IQbfToHypergraphConverter> converter(
				create::hypergraphConverter());
		return converter->convert(content());
	}
	*/

} // namespace qbf2asp
