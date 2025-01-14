/* inffast_chunk.h -- header to use inffast_chunk.c
 *
 * (C) 1995-2013 Jean-loup Gailly and Mark Adler
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * Jean-loup Gailly        Mark Adler
 * jloup@gzip.org          madler@alumni.caltech.edu
 *
 * Copyright (C) 1995-2003, 2010 Mark Adler
 * Copyright (C) 2017 ARM, Inc.
 * For conditions of distribution and use, see copyright notice in zlib.h
 */

/* WARNING: this file should *not* be used by applications. It is
   part of the implementation of the compression library and is
   subject to change. Applications should only use zlib.h.
 */

#include "inffast.h"

/* INFLATE_FAST_MIN_INPUT: the minimum number of input bytes needed so that
   we can safely call inflate_fast() with only one up-front bounds check. One
   length/distance code pair (15 bits for the length code, 5 bits for length
   extra, 15 bits for the distance code, 13 bits for distance extra) requires
   reading up to 48 input bits (6 bytes).

   For chunked decoding use a hopefully-pesimistic bound of two worst-case
   advances: 7 + 7, plus one 8-byte refill.
*/
#ifdef INFLATE_CHUNK_READ_64LE
#undef INFLATE_FAST_MIN_INPUT
#define INFLATE_FAST_MIN_INPUT 22
#endif

/* INFLATE_FAST_MIN_OUTPUT is usually 258, but we can copy two fast-path bytes
   as well */
#undef INFLATE_FAST_MIN_OUTPUT
#define INFLATE_FAST_MIN_OUTPUT 260

void ZLIB_INTERNAL inflate_fast_chunk_ OF((z_streamp strm, unsigned start));
