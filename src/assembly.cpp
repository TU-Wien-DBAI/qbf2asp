#include "preamble.h"

extern "C"
{
	QBF2ASP_API const char *qbf2asp_version()
	{
		return VERSION;
	}

// export additional symbols if tree decompositions are enabled
#ifdef ENABLE_DECOMPOSITION
	QBF2ASP_API const char *qbf2asp_decomposition_enabled()
	{
		return VERSION;
	}
#endif // ENABLE_DECOMPOSITION
}
