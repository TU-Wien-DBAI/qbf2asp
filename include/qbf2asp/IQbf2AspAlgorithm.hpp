#ifndef QBF2ASP_QBF2ASP_QBF2ASPALGORITHM_H_
#define QBF2ASP_QBF2ASP_QBF2ASPALGORITHM_H_

#include <qbf2asp/global>

#include <qbf2asp/IQbfInstance.hpp>

namespace qbf2asp
{

	class QBF2ASP_API IQbf2AspAlgorithm
	{
	protected:
		IQbf2AspAlgorithm &operator=(IQbf2AspAlgorithm &) { return *this; }

	public:
		virtual ~IQbf2AspAlgorithm() = 0;

		virtual void rewrite(const IQbfInstance &instance) const = 0;

	}; // class IQbf2AspAlgorithm

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_QBF2ASPALGORITHM_H_
