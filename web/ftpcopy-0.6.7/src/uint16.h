/* Reimplementation of Daniel J. Bernsteins uint library.
 * (C) 2001 Uwe Ohse, <uwe@ohse.de>.
 *   Report any bugs to <uwe@ohse.de>.
 * Placed in the public domain.
 */
#ifndef UINT16_H
#define UINT16_H

#include "typesize.h"
typedef uo_uint16_t uint16;

void uint16_pack(char *target,uint16);
void uint16_pack_big(char *target,uint16);
void uint16_unpack(const char *source,uint16 *);
void uint16_unpack_big(const char *source,uint16 *);

#endif
