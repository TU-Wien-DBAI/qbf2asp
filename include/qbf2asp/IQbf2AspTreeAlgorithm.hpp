#ifndef QBF2ASP_QBF2ASP_IQBF2ASPTREEALGORITHM_H_
#define QBF2ASP_QBF2ASP_IQBF2ASPTREEALGORITHM_H_

#include <qbf2asp/global>
#include <qbf2asp/IDependencyOrder.hpp>

#include <sharp/main>

#include <iostream>

namespace qbf2asp
{

	class QBF2ASP_API IQbf2AspTreeAlgorithm : public sharp::ITreeAlgorithm
	{
	protected:
		IQbf2AspTreeAlgorithm &operator=(IQbf2AspTreeAlgorithm &)
		{ return *this; }

	public:
		virtual ~IQbf2AspTreeAlgorithm() = 0;

		virtual void setOutputStream(std::ostream &out) = 0;
        virtual void setDependencyOrder(qbf2asp::IDependencyOrder & order) = 0;

	}; // class IQbf2AspTreeAlgorithm

	inline IQbf2AspTreeAlgorithm::~IQbf2AspTreeAlgorithm() { }

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_IQBF2ASPTREEALGORITHM_H_
