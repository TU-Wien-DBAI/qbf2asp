#ifndef QBF2ASP_QBF2ASP_IQBFCLAUSEFACTORY_H_
#define QBF2ASP_QBF2ASP_IQBFCLAUSEFACTORY_H_

#include <qbf2asp/global>

#include <qbf2asp/IQbfClause.hpp>

namespace qbf2asp
{
	class QBF2ASP_API IQbfClauseFactory
	{
	protected:
		IQbfClauseFactory &operator=(IQbfClauseFactory &) { return *this; }

	public:
		virtual ~IQbfClauseFactory() = 0;

		virtual IQbfClause *create() const = 0;

	}; // class IQbfClauseFactory

	inline IQbfClauseFactory::~IQbfClauseFactory() { }

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_IQBFCLAUSEFACTORY_H_
