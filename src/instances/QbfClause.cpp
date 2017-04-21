#ifdef HAVE_CONFIG_H
	#include <config.h>
#endif
#include "../util/debug.hpp"

#include "QbfClause.hpp"

#include <qbf2asp/IQbfInstance.hpp>

namespace qbf2asp
{
	using std::vector;
	using std::unordered_map;

	QbfClause::QbfClause(const IQbfInstance &instance) : instance_(instance) { }

	QbfClause::~QbfClause() { }

	void QbfClause::addVariable(variable_t variable)
	{
		this->addVariable(variable, false);
	}

	void QbfClause::addVariable(variable_t variable, bool negated)
	{
		variables_.insert(variable);
		if(negated)
			negated_.insert(variable);
	}

	const IQbfInstance &QbfClause::instance() const
	{
		return instance_;
	}

	bool QbfClause::contains(variable_t variable) const
	{
		return variables_.find(variable) != variables_.end();
	}

	bool QbfClause::isNegated(variable_t variable) const
	{
		return negated_.find(variable) != negated_.end();
	}

	bool QbfClause::checkSatisfaction(
			const variable_vector &trueVariables,
			const variable_vector &falseVariables) const
	{
		if(instance_.isCnf())
		{
			for(const variable_t variable : falseVariables)
				if(isNegated(variable))
					return true;

			for(const variable_t variable : trueVariables)
				if(contains(variable) && !isNegated(variable))
					return true;

			return false;
		}
		else
		{
			for(const variable_t variable : trueVariables)
				if(isNegated(variable))
					return false;

			for(const variable_t variable : falseVariables)
				if(contains(variable) && !isNegated(variable))
					return false;

			return true;
		}
	}

	IQbfClause::const_iterator QbfClause::begin() const
	{
		return IQbfClause::const_iterator(new ConstEnum(
					variables_.begin(),
					variables_.end()));
	}

	IQbfClause::const_iterator QbfClause::end() const
	{
		return IQbfClause::const_iterator(new ConstEnum(
					variables_.end()));
	}

} // namespace qbf2asp
