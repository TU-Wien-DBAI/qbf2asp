#ifndef QBF2ASP_QBF2ASP_IQBF2ASPALGORITHMFACTORY_H_
#define QBF2ASP_QBF2ASP_IQBF2ASPALGORITHMFACTORY_H_

#include <qbf2asp/global>

#include <qbf2asp/IQbf2AspAlgorithm.hpp>

namespace qbf2asp
{
	class QBF2ASP_API IQbf2AspAlgorithmFactory
	{
	protected:
		IQbf2AspAlgorithmFactory &operator=(IQbf2AspAlgorithmFactory &)
		{ return *this; }

	public:
		virtual ~IQbf2AspAlgorithmFactory() = 0;

		virtual IQbf2AspAlgorithm *create() const = 0;

	}; // class IQbf2AspAlgorithmFactory

	inline IQbf2AspAlgorithmFactory::~IQbf2AspAlgorithmFactory() { }

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_IQBF2ASPALGORITHMFACTORY_H_
