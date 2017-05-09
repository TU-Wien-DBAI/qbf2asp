#ifdef HAVE_CONFIG_H
	#include <config.h>
#endif
#include "debug.hpp"

#ifdef DEBUG
std::ostream *qbf2asp::Debug::stream = &std::cerr;
#endif // DEBUG
