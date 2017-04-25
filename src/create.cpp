#include "preamble.h"
#include <qbf2asp/create.hpp>

#include "parsers/QDIMACSParser.hpp"
#include "instances/QbfClause.hpp"
#include "instances/QbfInstance.hpp"
#include "instances/QbfToPrimalHypergraphConverter.hpp"
#include "algorithms/Qbf2DatalogTreeAlgorithm.hpp"

#include <memory>
#include <stdexcept>

namespace qbf2asp
{
	using htd::LibraryInstance;

	using std::unique_ptr;

	namespace
	{
		IQDIMACSParserFactory *parserFactory_ = nullptr;
		IQbfClauseFactory *clauseFactory_ = nullptr;
		IQbfInstanceFactory *instanceFactory_ = nullptr;
		IQbfToHypergraphConverterFactory *converterFactory_ = nullptr;
		IQbf2AspAlgorithmFactory *algorithmFactory_ = nullptr;	
		unique_ptr<LibraryInstance> htdlib_(nullptr);
	}

	void create::set(IQDIMACSParserFactory *factory)
	{
		if(parserFactory_)
			delete parserFactory_;
		parserFactory_ = factory;
	}

	void create::set(IQbfClauseFactory *factory)
	{
		if(clauseFactory_)
			delete clauseFactory_;
		clauseFactory_ = factory;
	}

	void create::set(IQbfInstanceFactory *factory)
	{
		if(instanceFactory_)
			delete instanceFactory_;
		instanceFactory_ = factory;
	}

	void create::set(IQbfToHypergraphConverterFactory *factory)
	{
		if(converterFactory_)
			delete converterFactory_;
		converterFactory_ = factory;
	}

	void create::set(IQbf2AspAlgorithmFactory *factory)
	{
		if(algorithmFactory_)
			delete algorithmFactory_;
		algorithmFactory_ = factory;
	}

	void create::set(LibraryInstance *htdlib)
	{
		htdlib_.reset(htdlib);
	}

	IQDIMACSParser *create::parser()
	{
		if(parserFactory_)
			return parserFactory_->create();
		
		return new QDIMACSParser();
	}
	
	IQbfClause *create::clause(const IQbfInstance &instance)
	{
		if(clauseFactory_)
			return clauseFactory_->create(instance);
		
		return new QbfClause(instance);
	}

	IQbfInstance *create::instance()
	{
		if(instanceFactory_)
			return instanceFactory_->create();

		return new QbfInstance();
	}

	IQbfToHypergraphConverter *create::hypergraphConverter()
	{
		if(converterFactory_)
			return converterFactory_->create();

		return new QbfToPrimalHypergraphConverter();
	}

	IQbf2AspAlgorithm *create::algorithm()
	{
		if(algorithmFactory_)
			return algorithmFactory_->create();

		return new Qbf2DatalogTreeAlgorithm();
	}

	const LibraryInstance &create::htdlib()
	{	
		if(!htdlib_.get())
			htdlib_.reset(htd::createManagementInstance(htd::Id::FIRST));
		return *htdlib_;
	}

} // namespace qbf2asp

