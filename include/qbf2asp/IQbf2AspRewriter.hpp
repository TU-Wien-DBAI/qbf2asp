#ifndef QBF2ASP_QBF2ASP_IQBF2ASPREWRITER_H_
#define QBF2ASP_QBF2ASP_IQBF2ASPREWRITER_H_

#include <qbf2asp/global>

#include <logic/parsers>

#include <iostream>

namespace qbf2asp
{

	class QBF2ASP_API IQbf2AspRewriter
	{
	protected:
		IQbf2AspRewriter &operator=(IQbf2AspRewriter &) { return *this; }

	public:
		virtual ~IQbf2AspRewriter() = 0;

		virtual void rewrite(const logic::IQbfInstance &instance) const = 0;
		virtual void rewrite(
				const logic::IQbfInstance &instance,
				std::ostream &out) const = 0;

	}; // class IQbf2AspRewriter

	inline IQbf2AspRewriter::~IQbf2AspRewriter() { }

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_IQBF2ASPREWRITER_H_
