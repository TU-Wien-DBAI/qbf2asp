#include "preamble.h"
#include <qbf2asp/create.hpp>

// tree decomposition-based conditional includes
#ifdef ENABLE_DECOMPOSITION

#  include "instances/QbfToPrimalHypergraphConverter.hpp"
#  include "algorithms/Qbf2DatalogTreeAlgorithm.hpp"

#endif // ENABLE_DECOMPOSITION

#include <memory>
#include <stdexcept>

namespace qbf2asp
{
	using std::unique_ptr;

	namespace
	{
		IQbf2AspAlgorithmFactory *algorithmFactory_ = nullptr;	
	}

	void create::set(IQbf2AspAlgorithmFactory *factory)
	{
		if(algorithmFactory_)
			delete algorithmFactory_;
		algorithmFactory_ = factory;
	}

// conditional code if tree decompositions are disabled
#ifndef ENABLE_DECOMPOSITION

	IQbf2AspAlgorithm *create::algorithm()
	{
		if(algorithmFactory_)
			return algorithmFactory_->create();

		return nullptr;
	}

#else // conditional code if tree decompositions are enabled

	IQbf2AspAlgorithm *create::algorithm()
	{
		if(algorithmFactory_)
			return algorithmFactory_->create();

		return new Qbf2DatalogTreeAlgorithm();
	}

	using htd::LibraryInstance;

	namespace
	{
		IQbfToHypergraphConverterFactory *converterFactory_ = nullptr;
		unique_ptr<LibraryInstance> htdlib_(nullptr);
	}

	void create::set(IQbfToHypergraphConverterFactory *factory)
	{
		if(converterFactory_)
			delete converterFactory_;
		converterFactory_ = factory;
	}

	void create::set(LibraryInstance *htdlib)
	{
		htdlib_.reset(htdlib);
	}

	IQbfToHypergraphConverter *create::hypergraphConverter()
	{
		if(converterFactory_)
			return converterFactory_->create();

		return new QbfToPrimalHypergraphConverter();
	}

	const LibraryInstance &create::htdlib()
	{	
		if(!htdlib_.get())
			htdlib_.reset(htd::createManagementInstance(htd::Id::FIRST));
		return *htdlib_;
	}

#endif // ENABLE_DECOMPOSITION

} // namespace qbf2asp

