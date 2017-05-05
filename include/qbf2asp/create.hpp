#ifndef QBF2ASP_QBF2ASP_CREATE_H_
#define QBF2ASP_QBF2ASP_CREATE_H_

#include <qbf2asp/global>

#include <qbf2asp/IQbf2AspAlgorithmFactory.hpp>
#include <qbf2asp/IQbf2AspAlgorithm.hpp>

// tree decomposition-based conditional includes
#ifdef ENABLE_DECOMPOSITION

#  include <qbf2asp/IQbfToHypergraphConverterFactory.hpp>
#  include <qbf2asp/IQbfToHypergraphConverter.hpp>

#  include <htd/main.hpp>

#endif // ENABLE_DECOMPOSITION


namespace qbf2asp
{
	class QBF2ASP_API create
	{
	public:

		static void set(IQbf2AspAlgorithmFactory *factory);

		static IQbf2AspAlgorithm *algorithm();

// tree decomposition-based conditional methods
#ifdef ENABLE_DECOMPOSITION
		static void set(IQbfToHypergraphConverterFactory *factory);
		static void set(htd::LibraryInstance *htdlib);

		static IQbfToHypergraphConverter *hypergraphConverter();
		static const htd::LibraryInstance &htdlib();
#endif // ENABLE_DECOMPOSITION
		
	private:
		create();

	}; // class create

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_CREATE_H_
