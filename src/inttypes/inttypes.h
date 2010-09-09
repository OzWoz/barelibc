// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#ifndef __INTTYPES_H
#define __INTTYPES_H

#ifndef __STDDEF_H
#include <stddef.h>
#endif

#ifndef __STDLIB_H
#include <stdlib.h>
#endif

#ifndef __STDINT_H
#include <stdint.h>
#endif

#if !defined(__cplusplus) || defined(__STDC_LIMIT_MACROS)

#define PRId8 "hhd"
#define PRId16 "hd"
#define PRId32 "d"
#define PRId64 "lld"
#define PRIdLEAST8 PRId8
#define PRIdLEAST16 PRId16
#define PRIdLEAST32 PRId32
#define PRIdLEAST64 PRId64
#define PRIdFAST8 PRId8
#define PRIdFAST16 PRId16
#define PRIdFAST32 PRId32
#define PRIdFAST64 PRId64
#define PRIdMAX PRId64
#define PRIdPTR PRId64

#define PRIi8 "hhi"
#define PRIi16 "hi"
#define PRIi32 "i"
#define PRIi64 "lli"
#define PRIiLEAST8 PRIi8
#define PRIiLEAST16 PRIi16
#define PRIiLEAST32 PRIi32
#define PRIiLEAST64 PRIi64
#define PRIiFAST8 PRIi8
#define PRIiFAST16 PRIi16
#define PRIiFAST32 PRIi32
#define PRIiFAST64 PRIi64
#define PRIiMAX PRIi64
#define PRIiPTR PRIi64

#define PRIu8 "hhu"
#define PRIu16 "hu"
#define PRIu32 "u"
#define PRIu64 "llu"
#define PRIuLEAST8 PRIu8
#define PRIuLEAST16 PRIu16
#define PRIuLEAST32 PRIu32
#define PRIuLEAST64 PRIu64
#define PRIuFAST8 PRIu8
#define PRIuFAST16 PRIu16
#define PRIuFAST32 PRIu32
#define PRIuFAST64 PRIu64
#define PRIuMAX PRIu64
#define PRIuPTR PRIu64

#define PRIo8 "hho"
#define PRIo16 "ho"
#define PRIo32 "o"
#define PRIo64 "llo"
#define PRIoLEAST8 PRIo8
#define PRIoLEAST16 PRIo16
#define PRIoLEAST32 PRIo32
#define PRIoLEAST64 PRIo64
#define PRIoFAST8 PRIo8
#define PRIoFAST16 PRIo16
#define PRIoFAST32 PRIo32
#define PRIoFAST64 PRIo64
#define PRIoMAX PRIo64
#define PRIoPTR PRIo64

#define PRIx8 "hhx"
#define PRIx16 "hx"
#define PRIx32 "x"
#define PRIx64 "llx"
#define PRIxLEAST8 PRIx8
#define PRIxLEAST16 PRIx16
#define PRIxLEAST32 PRIx32
#define PRIxLEAST64 PRIx64
#define PRIxFAST8 PRIx8
#define PRIxFAST16 PRIx16
#define PRIxFAST32 PRIx32
#define PRIxFAST64 PRIx64
#define PRIxMAX PRIx64
#define PRIxPTR PRIx64

#define PRIX8 "hhX"
#define PRIX16 "hX"
#define PRIX32 "X"
#define PRIX64 "llX"
#define PRIXLEAST8 PRIX8
#define PRIXLEAST16 PRIX16
#define PRIXLEAST32 PRIX32
#define PRIXLEAST64 PRIX64
#define PRIXFAST8 PRIX8
#define PRIXFAST16 PRIX16
#define PRIXFAST32 PRIX32
#define PRIXFAST64 PRIX64
#define PRIXMAX PRIX64
#define PRIXPTR PRIX64

#define SCNd8 PRId8
#define SCNd16 PRId16
#define SCNd32 PRId32
#define SCNd64 PRId64
#define SCNdLEAST8 PRIdLEAST8
#define SCNdLEAST16 PRIdLEAST16
#define SCNdLEAST32 PRIdLEAST32
#define SCNdLEAST64 PRIdLEAST64
#define SCNdFAST8 PRIdFAST8
#define SCNdFAST16 PRIdFAST16
#define SCNdFAST32 PRIdFAST32
#define SCNdFAST64 PRIdFAST64
#define SCNdMAX PRIdMAX
#define SCNdPTR PRIdPTR

#define SCNi8 PRIi8
#define SCNi16 PRIi16
#define SCNi32 PRIi32
#define SCNi64 PRIi64
#define SCNiLEAST8 PRIiLEAST8
#define SCNiLEAST16 PRIiLEAST16
#define SCNiLEAST32 PRIiLEAST32
#define SCNiLEAST64 PRIiLEAST64
#define SCNiFAST8 PRIiFAST8
#define SCNiFAST16 PRIiFAST16
#define SCNiFAST32 PRIiFAST32
#define SCNiFAST64 PRIiFAST64
#define SCNiMAX PRIiMAX
#define SCNiPTR PRIiPTR

#define SCNu8 PRIu8
#define SCNu16 PRIu16
#define SCNu32 PRIu32
#define SCNu64 PRIu64
#define SCNuLEAST8 PRIuLEAST8
#define SCNuLEAST16 PRIuLEAST16
#define SCNuLEAST32 PRIuLEAST32
#define SCNuLEAST64 PRIuLEAST64
#define SCNuFAST8 PRIuFAST8
#define SCNuFAST16 PRIuFAST16
#define SCNuFAST32 PRIuFAST32
#define SCNuFAST64 PRIuFAST64
#define SCNuMAX PRIuMAX
#define SCNuPTR PRIuPTR

#define SCNo8 PRIo8
#define SCNo16 PRIo16
#define SCNo32 PRIo32
#define SCNo64 PRIo64
#define SCNoLEAST8 PRIoLEAST8
#define SCNoLEAST16 PRIoLEAST16
#define SCNoLEAST32 PRIoLEAST32
#define SCNoLEAST64 PRIoLEAST64
#define SCNoFAST8 PRIoFAST8
#define SCNoFAST16 PRIoFAST16
#define SCNoFAST32 PRIoFAST32
#define SCNoFAST64 PRIoFAST64
#define SCNoMAX PRIoMAX
#define SCNoPTR PRIoPTR

#define SCNx8 PRIx8
#define SCNx16 PRIx16
#define SCNx32 PRIx32
#define SCNx64 PRIx64
#define SCNxLEAST8 PRIxLEAST8
#define SCNxLEAST16 PRIxLEAST16
#define SCNxLEAST32 PRIxLEAST32
#define SCNxLEAST64 PRIxLEAST64
#define SCNxFAST8 PRIxFAST8
#define SCNxFAST16 PRIxFAST16
#define SCNxFAST32 PRIxFAST32
#define SCNxFAST64 PRIxFAST64
#define SCNxMAX PRIxMAX
#define SCNxPTR PRIxPTR

#define SCNX8 PRIX8
#define SCNX16 PRIX16
#define SCNX32 PRIX32
#define SCNX64 PRIX64
#define SCNXLEAST8 PRIXLEAST8
#define SCNXLEAST16 PRIXLEAST16
#define SCNXLEAST32 PRIXLEAST32
#define SCNXLEAST64 PRIXLEAST64
#define SCNXFAST8 PRIXFAST8
#define SCNXFAST16 PRIXFAST16
#define SCNXFAST32 PRIXFAST32
#define SCNXFAST64 PRIXFAST64
#define SCNXMAX PRIXMAX
#define SCNXPTR PRIXPTR

#endif

typedef struct {
	intmax_t quot;
	intmax_t rem;
} intdiv_t;

#ifdef __cplusplus
extern "C" {
#endif

intmax_t imaxabs(intmax_t val);
intdiv_t imaxdiv(intmax_t numer, intmax_t denom);

#ifdef __cplusplus
}
#endif

#define strtoimax strtoll
#define strtoumax strtoull
#define wcstoimax wcstoll
#define wcstoumax wcstoull

#endif //__INTTYPES_H

///
