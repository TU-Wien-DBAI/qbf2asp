#ifndef QBF2ASP_QBF2ASP_IQBF2ASPTREEREWRITER_H_
#define QBF2ASP_QBF2ASP_IQBF2ASPTREEREWRITER_H_

#include <qbf2asp/global>

#include <qbf2asp/IQbf2AspRewriter.hpp>

#include <sharp/main>

namespace qbf2asp
{

	class QBF2ASP_API IQbf2AspTreeRewriter 
		:	public IQbf2AspRewriter, 
			public sharp::ITreeSolver
	{
	protected:
		IQbf2AspTreeRewriter &operator=(IQbf2AspTreeRewriter &)
		{ return *this; }

	public:
		virtual ~IQbf2AspTreeRewriter() override = 0;

	}; // class IQbf2AspTreeRewriter

	inline IQbf2AspTreeRewriter::~IQbf2AspTreeRewriter() { }

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_IQBF2ASPTREEREWRITER_H_
