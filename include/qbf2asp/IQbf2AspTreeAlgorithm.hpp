#ifndef QBF2ASP_QBF2ASP_QBF2ASPTREEALGORITHM_H_
#define QBF2ASP_QBF2ASP_QBF2ASPTREEALGORITHM_H_

#include <qbf2asp/global>

#include <qbf2asp/IQbf2AspAlgorithm.hpp>

#include <sharp/main>

#include <htd/main.hpp>

namespace qbf2asp
{

	class QBF2ASP_API IQbf2AspTreeAlgorithm 
		:	public IQbf2AspAlgorithm, 
			public sharp::ITreeAlgorithm,
	{
	protected:
		IQbf2AspTreeAlgorithm &operator=(IQbf2AspTreeAlgorithm &)
		{ return *this; }

	public:
		virtual ~IQbf2AspTreeAlgorithm() override = 0;

	}; // class IQbf2AspTreeAlgorithm

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_QBF2ASPTREEALGORITHM_H_
