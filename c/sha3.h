/**
 * sha3sum – SHA-3 (Keccak) checksum calculator
 * 
 * Copyright © 2013, 2014  Mattias Andrée (maandree@member.fsf.org)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef __SHA3_H__
#define __SHA3_H__

#include <stdlib.h>


#ifdef WITH_C99
  #include <inttypes.h>
  #define restrict_ restrict
  #define byte int_fast8_t
  #define boolean int_fast8_t
  #define llong int_fast64_t
  #define ullong uint_fast64_t
#else
  #define restrict_ /* introduced in C99 */
  #define byte char
  #define boolean char
  #if __x86_64__ || __ppc64__
    #define llong long int
  #else
    #define llong long long int
  #endif
  #define ullong unsigned llong
#endif


/**
 * Suffix the message when calculating the Keccak hash sum
 */
#define KECCAK_SUFFIX  ""

/**
 * Suffix the message when calculating the SHA-3 hash sum
 */
#define SHA3_SUFFIX  "01"
  
/**
 * Suffix the message when calculating the RawSHAKE hash sum
 */
#define RawSHAKE_SUFFIX  "11"
  
/**
 * Suffix the message when calculating the SHAKE hash sum
 */
#define SHAKE_SUFFIX  "1111"


/**
 * Initialise Keccak sponge
 * 
 * @param  bitrate   The bitrate
 * @param  capacity  The capacity
 * @param  output    The output size
 */
void sha3_initialise(long bitrate, long capacity, long output);


/**
 * Dispose of the Keccak sponge
 */
void sha3_dispose(void);


/**
 * Absorb the more of the message to the Keccak sponge
 * 
 * @param  msg     The partial message
 * @param  msglen  The length of the partial message
 */
void sha3_update(byte* restrict_ msg, long msglen);


/**
 * Absorb the last part of the message and squeeze the Keccak sponge
 * 
 * @param   msg         The rest of the message, may be {@code null}
 * @param   msglen      The length of the partial message
 * @param   bits        The number of bits at the end of the message not covered by `msglen`
 * @param   suffix      The suffix concatenate to the message
 * @param   withReturn  Whether to return the hash instead of just do a quick squeeze phrase and return {@code null}
 * @return              The hash sum, or {@code null} if <tt>withReturn</tt> is {@code false}
 */
byte* sha3_digest(byte* restrict_ msg, long msglen, long bits, char* restrict_ suffix, boolean withReturn);


/**
 * Force some rounds of Keccak-f
 * 
 * @param  times  The number of rounds
 */
void sha3_simpleSqueeze(long times);


/**
 * Squeeze as much as is needed to get a digest a number of times
 * 
 * @param  times  The number of digests
 */
void sha3_fastSqueeze(long times);


/**
 * Squeeze out another digest
 * 
 * @return  The hash sum
 */
byte* sha3_squeeze(void);


/**
 * Retrieve the state of the Keccak sponge
 * 
 * @return  A 25-element array with the state, changes will be applied to the sponge
 */
llong* sha3_state(void);


#endif

