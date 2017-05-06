#ifndef QBF2ASP_QBF2ASP_CREATE_H_
#define QBF2ASP_QBF2ASP_CREATE_H_

#include <qbf2asp/global>

#include <qbf2asp/IQbf2AspRewriterFactory.hpp>
#include <qbf2asp/IQbf2AspRewriter.hpp>

// tree decomposition-based conditional includes
#ifdef ENABLE_DECOMPOSITION

#  include <qbf2asp/IQbf2AspTreeRewriterFactory.hpp>
#  include <qbf2asp/IQbf2AspTreeRewriter.hpp>
#  include <qbf2asp/IQbf2AspTreeAlgorithmFactory.hpp>
#  include <qbf2asp/IQbf2AspTreeAlgorithm.hpp>
#  include <qbf2asp/IQbfToHypergraphConverterFactory.hpp>
#  include <qbf2asp/IQbfToHypergraphConverter.hpp>

#  include <htd/main.hpp>

#endif // ENABLE_DECOMPOSITION


namespace qbf2asp
{
	class QBF2ASP_API create
	{
	public:
		enum Rewriter
		{
			SATURATION = 0,
			LARGE_RULE_ICLP2016,
			LARGE_RULE_ARITHMETICS,
#ifdef ENABLE_DECOMPOSITION
			DATALOG_VIA_DECOMPOSITION,
#endif // ENABLE_DECOMPOSITION
			INVALID_MAXIMUM
		};

	public:
		static void set(IQbf2AspRewriterFactory *factory);

		static IQbf2AspRewriter *rewriter();
		static IQbf2AspRewriter *rewriter(Rewriter type);

// tree decomposition-based conditional methods
#ifdef ENABLE_DECOMPOSITION
		static void set(IQbf2AspTreeRewriterFactory *factory);
		static void set(IQbf2AspTreeAlgorithmFactory *factory);
		static void set(IQbfToHypergraphConverterFactory *factory);
		static void set(htd::LibraryInstance *htdlib);

		static IQbf2AspTreeRewriter *treeRewriter();
		static IQbf2AspTreeAlgorithm *treeAlgorithm();
		static IQbfToHypergraphConverter *hypergraphConverter();
		static const htd::LibraryInstance &htdlib();
#endif // ENABLE_DECOMPOSITION
		
	private:
		create();

	}; // class create

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_CREATE_H_
