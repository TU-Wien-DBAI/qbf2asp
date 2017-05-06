#include "preamble.h"
#include <qbf2asp/create.hpp>

#include "algorithms/SaturationRewriter.hpp"
#include "algorithms/LargeRuleArithmeticsRewriter.hpp"
#include "algorithms/LargeRuleIclp2016Rewriter.hpp"

// tree decomposition-based conditional includes
#ifdef ENABLE_DECOMPOSITION

#  include "algorithms/Qbf2DatalogTreeRewriter.hpp"
#  include "algorithms/Qbf2DatalogTreeAlgorithm.hpp"
#  include "instances/PrimalHypergraphConverter.hpp"

#endif // ENABLE_DECOMPOSITION

#include <memory>
#include <stdexcept>

namespace qbf2asp
{
	using std::unique_ptr;
	using std::invalid_argument;

	namespace
	{
		IQbf2AspRewriterFactory *rewriterFactory_ = nullptr;	
	}

	void create::set(IQbf2AspRewriterFactory *factory)
	{
		if(rewriterFactory_)
			delete rewriterFactory_;
		rewriterFactory_ = factory;
	}

	IQbf2AspRewriter *create::rewriter()
	{
		if(rewriterFactory_)
			return rewriterFactory_->create();

		return rewriter(SATURATION);
	}

	IQbf2AspRewriter *create::rewriter(Rewriter type)
	{
		switch(type)
		{
		case SATURATION:
			return new SaturationRewriter();

		case LARGE_RULE_ICLP2016:
			return new LargeRuleIclp2016Rewriter();

		case LARGE_RULE_ARITHMETICS:
			return new LargeRuleArithmeticsRewriter();

#ifdef ENABLE_DECOMPOSITION
		case DATALOG_VIA_DECOMPOSITION:
			return new Qbf2DatalogTreeRewriter();
#endif // ENABLE_DECOMPOSITION

		default:
			throw invalid_argument("Paramter 'type' is invalid.");
		}
	}

#ifdef ENABLE_DECOMPOSITION 
	using htd::LibraryInstance;

	namespace
	{
		IQbf2AspTreeRewriterFactory *treeRewriterFactory_ = nullptr;
		IQbf2AspTreeAlgorithmFactory *algorithmFactory_ = nullptr;
		IQbfToHypergraphConverterFactory *converterFactory_ = nullptr;
		unique_ptr<LibraryInstance> htdlib_(nullptr);
	}

	void create::set(IQbf2AspTreeRewriterFactory *factory)
	{
		if(treeRewriterFactory_)
			delete treeRewriterFactory_;
		treeRewriterFactory_ = factory;
	}
	
	void create::set(IQbf2AspTreeAlgorithmFactory *factory)
	{
		if(algorithmFactory_)
			delete algorithmFactory_;
		algorithmFactory_ = factory;
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

	IQbf2AspTreeAlgorithm *create::treeAlgorithm()
	{
		if(algorithmFactory_)
			return algorithmFactory_->create();

		return new Qbf2DatalogTreeAlgorithm();
	}

	IQbf2AspTreeRewriter *create::treeRewriter()
	{
		if(treeRewriterFactory_)
			return treeRewriterFactory_->create();

		return new Qbf2DatalogTreeRewriter();
	}

	IQbfToHypergraphConverter *create::hypergraphConverter()
	{
		if(converterFactory_)
			return converterFactory_->create();

		return new PrimalHypergraphConverter();
	}

	const LibraryInstance &create::htdlib()
	{	
		if(!htdlib_.get())
			htdlib_.reset(htd::createManagementInstance(htd::Id::FIRST));
		return *htdlib_;
	}

#endif // ENABLE_DECOMPOSITION

} // namespace qbf2asp

