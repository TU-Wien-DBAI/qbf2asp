#ifdef HAVE_CONFIG_H
	#include <config.h>
#endif
#include "../util/debug.hpp"

#include "QbfInstance.hpp"

#include "QbfClause.hpp"

#include <qbf2asp/create.hpp>

#include <utility>
#include <stdexcept>

namespace qbf2asp
{
	using htd::IHypergraph;
	using htd::IMutableHypergraph;
	using htd::vertex_t;
		
	using std::string;
	using std::size_t;
	using std::make_pair;
	using std::pair;
	using std::unordered_map;
	using std::unique_ptr;

	QbfInstance::QbfInstance() : maxVariable_(0) { }

	QbfInstance::~QbfInstance()
	{
		for(IQbfClause *clause : clauses_)
			delete clause;
	}

	void QbfInstance::addVariableName(variable_t variable, const string &name)
	{
		addVariable(variable);
		variableNames_[variable] = name;
	}

	void QbfInstance::addVariable(variable_t variable)
	{
		if(maxVariable_ < variable) maxVariable_ = variable;
	}

	void QbfInstance::addClause(IQbfClause *clause)
	{
		if(!clause)
			throw std::invalid_argument("Argument 'clause' cannot be null!");

		clauses_.push_back(clause);
	}

	IHypergraph *QbfInstance::toHypergraph() const
	{
		unique_ptr<IQbfToHypergraphConverter> converter(
				create::hypergraphConverter());

		return converter->convert(*this);
	}

	bool QbfInstance::isClause(vertex_t vertex) const
	{
		return vertex > maxVariable_
			&& vertex <= maxVariable_ + clauses_.size();
	}

	bool QbfInstance::isVariable(vertex_t vertex) const
	{
		return vertex <= maxVariable_;
	}

	const IQbfClause &QbfInstance::clause(clause_t clause) const
	{
		if(!isClause(clause))
			throw std::invalid_argument("Argument 'clause' is not a clause.");

		return *clauses_[clause - maxVariable_ - 1];
	}

	IQbfInstance::const_iterator QbfInstance::begin() const
	{
		return IQbfInstance::const_iterator(new ConstEnum(
					clauses_.begin(),
					clauses_.end()));
	}

	IQbfInstance::const_iterator QbfInstance::end() const
	{
		return IQbfInstance::const_iterator(new ConstEnum(clauses_.end()));
	}

}// namespace qbf2asp
