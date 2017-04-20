#ifndef QBF2ASP_UTIL_DEBUG_H_
#define QBF2ASP_UTIL_DEBUG_H_

#ifdef DEBUG

#include <iostream>

namespace qbf2asp
{
	class Debug
	{
	public:
		static std::ostream &stream;

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
	Debug::stream = (x)

#define DBG(x) \
	Debug::stream << (x)

#define DBG_COLL(x) \
	Debug::printColl(Debug::stream, (x))

#define DBG_MAP(x) \
	Debug::printMap(Debug::stream, (x))

#else // !DEBUG

#define DBG_SET(...)
#define DBG(...)
#define DBG_COLL(...)
#define DBG_MAP(...)

#endif // DEBUG

#endif // QBF2ASP_UTIL_DEBUG_H_
