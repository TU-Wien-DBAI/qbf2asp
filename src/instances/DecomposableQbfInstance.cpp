#include "../preamble.h"
#include <qbf2asp/DecomposableQbfInstance.hpp>

#include <qbf2asp/create.hpp>

#include <memory>

namespace sharp
{
	template<>
	htd::IMultiHypergraph *
	DecomposableInstance<logic::IQbfInstance>::toHypergraph() const
	{
		std::unique_ptr<qbf2asp::IQbfToHypergraphConverter> converter(
				qbf2asp::create::hypergraphConverter());
		return converter->convert(content_);
	}

} // namespace sharp
