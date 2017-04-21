#ifndef QBF2ASP_QBF2ASP_CREATE_H_
#define QBF2ASP_QBF2ASP_CREATE_H_

#include <qbf2asp/global>

#include <qbf2asp/IQDIMACSParserFactory.hpp>
#include <qbf2asp/IQDIMACSParser.hpp>
#include <qbf2asp/IQbfToHypergraphConverterFactory.hpp>
#include <qbf2asp/IQbfToHypergraphConverter.hpp>
#include <qbf2asp/IQbfInstanceFactory.hpp>
#include <qbf2asp/IQbfInstance.hpp>
#include <qbf2asp/IQbfClauseFactory.hpp>
#include <qbf2asp/IQbfClause.hpp>
#include <qbf2asp/IQbf2AspAlgorithmFactory.hpp>
#include <qbf2asp/IQbf2AspAlgorithm.hpp>

namespace qbf2asp
{
	class QBF2ASP_API create
	{
	public:

		static void set(IQDIMACSParserFactory *factory);
		static void set(IQbfToHypergraphConverterFactory *factory);
		static void set(IQbfInstanceFactory *factory);
		static void set(IQbfClauseFactory *factory);
		static void set(IQbf2AspAlgorithmFactory *factory);

		static IQDIMACSParser *parser();

		static IQbfToHypergraphConverter *hypergraphConverter();

		static IQbfInstance *instance();
		
		static IQbfClause *clause(const IQbfInstance &instance);
		
		static IQbf2AspAlgorithm *algorithm();
		
	private:
		create();

	}; // class create

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_CREATE_H_
