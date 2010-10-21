// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

//#define MEMORY_SIMPLE

#ifdef MEMORY_SIMPLE
	#include "memory_simple.c"
#else
	#include "memory_adv.c"
#endif

///
