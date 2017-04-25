#ifndef QBF2ASP_QBF2ASP_IQBF2ASPTREEALGORITHM_H_
#define QBF2ASP_QBF2ASP_IQBF2ASPTREEALGORITHM_H_

#include <qbf2asp/global>

#include <qbf2asp/IQbf2AspAlgorithm.hpp>

#include <sharp/main>

#include <cstdlib>

namespace qbf2asp
{

	class QBF2ASP_API IQbf2AspTreeAlgorithm 
		:	public IQbf2AspAlgorithm, 
			public sharp::ITreeAlgorithm
	{
	protected:
		IQbf2AspTreeAlgorithm &operator=(IQbf2AspTreeAlgorithm &)
		{ return *this; }

	public:
		virtual ~IQbf2AspTreeAlgorithm() override = 0;

		virtual std::size_t decompose(const IQbfInstance &instance) const = 0;

	}; // class IQbf2AspTreeAlgorithm

	inline IQbf2AspTreeAlgorithm::~IQbf2AspTreeAlgorithm() { }

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_IQBF2ASPTREEALGORITHM_H_
