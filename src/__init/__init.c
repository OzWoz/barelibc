// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdlib.h>

void __init(volatile void *heap_ptr, size_t heap_size)
{
	srand(1);
	__init_alloc(heap_ptr, heap_size);
}

///
