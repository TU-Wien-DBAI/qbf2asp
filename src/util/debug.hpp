#ifndef QBF2ASP_UTIL_DEBUG_H_
#define QBF2ASP_UTIL_DEBUG_H_

#ifdef DEBUG

#include <qbf2asp/global>

#include <iostream>

namespace qbf2asp
{
	class Debug
	{
	public:
		static QBF2ASP_API std::ostream *stream;

		template<typename T>
		static void printColl(std::ostream &out, const T &coll)
		{
			out << "[";
			const char *sep = "";
			for(const auto o : coll)
			{
				out << sep << o;
				sep = ",";
			}
			out << "]";
		}

		template<typename T>
		static void printMap(std::ostream &out, const T &coll)
		{
			out << "[";
			const char *sep = "";
			for(const auto o : coll)
			{
				out << sep << o.first << ":" << o.second;
				sep = ",";
			}
			out << "]";
		}

	private:
		Debug();
	};

} // namespace qbf2asp

#define DBG_SET(x) \
	qbf2asp::Debug::stream = (x)

#define DBG(x) \
	*qbf2asp::Debug::stream << (x)

#define DBG_COLL(x) \
	qbf2asp::Debug::printColl(*qbf2asp::Debug::stream, (x))

#define DBG_MAP(x) \
	qbf2asp::Debug::printMap(*qbf2asp::Debug::stream, (x))

#else // !DEBUG

#define DBG_SET(...)
#define DBG(...)
#define DBG_COLL(...)
#define DBG_MAP(...)

#endif // DEBUG

#endif // QBF2ASP_UTIL_DEBUG_H_
