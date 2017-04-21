#ifdef HAVE_CONFIG_H
	#include <config.h>
#endif
#include "../util/debug.hpp"

#include "QbfInstance.hpp"

#include <qbf2asp/create.hpp>

#include <utility>
#include <stdexcept>

namespace qbf2asp
{
	using htd::IHypergraph;
	using htd::IMutableHypergraph;
	using htd::vertex_t;
		
	using std::size_t;
	using std::unordered_map;
	using std::unique_ptr;

	QbfInstance::QbfInstance() { }

	QbfInstance::~QbfInstance()
	{
		for(IQbfClause *clause : clauses_)
			delete clause;
	}

	void QbfInstance::setCnf()
	{
		dnf_ = false;
	}

	void QbfInstance::setDnf()
	{
		dnf_ = true;
	}

	void QbfInstance::setVariableCount(size_t variableCount)
	{
		variableCount_ = variableCount;
	}

	void QbfInstance::setQuantifierLevel(variable_t variable, short level)
	{
		if(variable > variableCount_)
			throw std::invalid_argument(
					"Argument 'variable' is not a variable.");
		if(level < 0)
			throw std::invalid_argument("Argument 'level' cannot be negative.");

		quantifierLevels_[variable] = level;

		if(outermostQuantifierLevel_ < level)
			outermostQuantifierLevel_ = level;
	}

	IQbfClause &QbfInstance::newClause()
	{
		IQbfClause *clause = create::clause(*this);
		clauses_.push_back(clause);
		return *clause;
	}

	IHypergraph *QbfInstance::toHypergraph() const
	{
		unique_ptr<IQbfToHypergraphConverter> converter(
				create::hypergraphConverter());

		return converter->convert(*this);
	}

	bool QbfInstance::isClause(vertex_t vertex) const
	{
		return vertex > variableCount_
			&& vertex <= variableCount_ + clauses_.size();
	}

	bool QbfInstance::isVariable(vertex_t vertex) const
	{
		return vertex <= variableCount_;
	}

	bool QbfInstance::isExistential(variable_t variable) const
	{
		// if the quantifier level is even, and we are a cnf, return true
		// if the quantifier level is odd, and we are a dnf, return true
		return getQuantifierLevel(variable) % 2 ? !dnf_ : dnf_;
	}

	bool QbfInstance::isUniversal(variable_t variable) const
	{
		// if the quantifier level is odd, and we are a cnf, return true
		// if the quantifier level is even, and we are a dnf, return true
		return getQuantifierLevel(variable) % 2 ? dnf_ : !dnf_;
	}

	short QbfInstance::getQuantifierLevel(variable_t variable) const
	{
		unordered_map<size_t, short>::const_iterator iter;
		if((iter = quantifierLevels_.find(variable)) == quantifierLevels_.end())
		{
			return outermostQuantifierLevel_ % 2 ?
				outermostQuantifierLevel_ + 1 : outermostQuantifierLevel_;
		}
		return iter->second;
	}

	size_t QbfInstance::getVariableCount() const
	{
		return variableCount_;
	}

	bool QbfInstance::isCnf() const
	{
		return !dnf_;
	}

	bool QbfInstance::isDnf() const
	{
		return dnf_;
	}

	const IQbfClause &QbfInstance::clause(clause_t clause) const
	{
		if(!isClause(clause))
			throw std::invalid_argument("Argument 'clause' is not a clause.");

		return *clauses_[clause - variableCount_ - 1];
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
