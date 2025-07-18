#ifndef _GIF_LIB_PRIVATE_H
#define _GIF_LIB_PRIVATE_H

#include "gif_lib.h"
#include "gif_hash.h"

#define PROGRAM_NAME "GIFLIB"

#ifdef SYSV
#define VersionStr "Gif library module,\t\tEric S. Raymond\n\
                    (C) Copyright 1997 Eric S. Raymond\n"
#else
#define VersionStr PROGRAM_NAME "    IBMPC " GIF_LIB_VERSION \
                    "    Eric S. Raymond,    " __DATE__ ",   " \
                    __TIME__ "\n" "(C) Copyright 1997 Eric S. Raymond\n"
#endif /* SYSV */

#define LZ_MAX_CODE         4095    /* Biggest code possible in 12 bits. */
#define LZ_BITS             12
#define LZ_SAFETY_MARGIN    4096    /* Oli Fix 08.06.2025 */

#define FLUSH_OUTPUT        4096    /* Impossible code, to signal flush. */
#define FIRST_CODE          4097    /* Impossible code, to signal first. */
#define NO_SUCH_CODE        4098    /* Impossible code, to signal empty. */

#define FILE_STATE_WRITE    0x01
#define FILE_STATE_SCREEN   0x02
#define FILE_STATE_IMAGE    0x04
#define FILE_STATE_READ     0x08

#define IS_READABLE(Private)    (Private->FileState & FILE_STATE_READ)
#define IS_WRITEABLE(Private)   (Private->FileState & FILE_STATE_WRITE)

typedef struct GifFilePrivateType {
    int FileState, FileHandle,  /* Where all this data goes to! */
      BitsPerPixel,     /* Bits per pixel (Codes uses at least this + 1). */
      ClearCode,   /* The CLEAR LZ code. */
      EOFCode,     /* The EOF LZ code. */
      RunningCode, /* The next code algorithm can generate. */
      RunningBits, /* The number of bits required to represent RunningCode. */
      MaxCode1,    /* 1 bigger than max. possible code, in RunningBits bits. */
      LastCode,    /* The code before the current code. */
      CrntCode,    /* Current algorithm code. */
      StackPtr,    /* For character stack (see below). */
      CrntShiftState;    /* Number of bits in CrntShiftDWord. */
    unsigned long CrntShiftDWord;   /* For bytes decomposition into codes. */
    unsigned long PixelCount;   /* Number of pixels in image. */
    FILE *File;    /* File as stream. */
    InputFunc Read;     /* function to read gif input (TVT) */
    OutputFunc Write;   /* function to write gif output (MRB) */
    GifByteType Buf[256];   /* Compressed input is buffered here. */
    GifByteType Stack[LZ_MAX_CODE]; /* Decoded pixels are stacked here. */
    GifByteType Suffix[LZ_MAX_CODE + 1 + LZ_SAFETY_MARGIN];    /* So we can trace the codes. */ /* Oli Fix 08.06.2025 */
    unsigned int Prefix[LZ_MAX_CODE + 1 + LZ_SAFETY_MARGIN];   /* Oli Fix 08.06.2025 */
    GifHashTableType *HashTable;
} GifFilePrivateType;

extern int _GifError;

#endif /* _GIF_LIB_PRIVATE_H */
