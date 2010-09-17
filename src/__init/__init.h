// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#ifndef ____INIT_H
#define ____INIT_H

#ifndef __STDDEF_H
#include <stddef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

void __init(volatile void *heap_ptr, size_t heap_size);
int main(int argc, char *argv[], char *envp[]);

#ifdef __cplusplus
}
#endif

#endif //____INIT_H

///
