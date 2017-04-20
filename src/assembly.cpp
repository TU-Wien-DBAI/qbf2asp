#ifdef HAVE_CONFIG_H
	#include <config.h>
#endif

#include <qbf2asp/global>

extern "C"
{
	qbf2asp_API const char *qbf2asp_version()
	{
		return VERSION;
	}
}
