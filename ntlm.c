/*
 ntlm - Calculate NTLM hash for given string.
 Copyright (C) 2023 Robert <modrobert@gmail.com>

 Permission to use, copy, modify, and/or distribute this software for any
 purpose with or without fee is hereby granted.

 THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 PERFORMANCE OF THIS SOFTWARE.

 Compile: gcc -O3 -Wpedantic ntlm.c -o ntlm -lcrypto
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md4.h>
#include <iconv.h>

/* md4 is old and deprecated */
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

const char *PROGTITLE = "ntlm v0.10 by modrobert in 2023";

void hash_to_hex(unsigned char *hash, char *str)
{
 for (int i = 0; i < MD4_DIGEST_LENGTH; i++)
 {
  sprintf(str + i * 2, "%02X", hash[i]);
 }
}

int main(int argc, char *argv[])
{
 unsigned char hash[MD4_DIGEST_LENGTH];
 char hash_string[MD4_DIGEST_LENGTH * 2];

 if (argc < 2)
 {
  fprintf(stderr, "%s\n", PROGTITLE);
  fprintf(stderr, "Syntax: %s <string>\n", argv[0]);
  exit(1);
 }

 size_t instring_length = strlen(argv[1]);
 /* making sure output string is long enough for UTF-16LE */
 size_t outstring_length = (instring_length * 2);
 size_t instring_counter = instring_length;
 size_t outstring_counter = outstring_length;
 char outbuf[outstring_length];
 char *outptr = outbuf;
 char *inptr = argv[1];

 /* note; iconv_open("to format", "from format") */
 iconv_t cd = iconv_open("UTF-16LE", "UTF-8");
 if (cd == (iconv_t) -1)
 {
  fprintf(stderr, "string conversion init error\n");
  exit(2);
 }

 size_t result = iconv(cd, &inptr, &instring_counter, &outptr, &outstring_counter);
 if (result == (size_t) -1)
 {
  fprintf(stderr, "string conversion error\n");
  iconv_close(cd);
  exit(2);
 }
 iconv_close(cd);

 /* calculating correct length in case we get multibyte UTF-8 chars */
 MD4((const unsigned char *) outbuf, (outstring_length - outstring_counter), hash);

 hash_to_hex(hash, hash_string);
 printf("%s\n", hash_string);

 return 0;
}

/* vim:ts=1:sw=1:ft=c:et:ai:
*/
