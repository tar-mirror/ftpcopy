/*
 * Copyright (C) 2002 Uwe Ohse, uwe@ohse.de
 * This is free software, licensed under the terms of the GNU General 
 * Public License Version 2, of which a copy is stored at:
 *    http://www.ohse.de/uwe/licenses/GPL-2
 * Later versions may or may not apply, see 
 *    http://www.ohse.de/uwe/licenses/
 * for information after a newer version has been published.
 */
#ifndef URLPARSE_H
#define URLPARSE_H

int urlparse (const char *url, stralloc *proto, stralloc *user, stralloc *pass,
    stralloc *hostport, stralloc *rest);

#endif
