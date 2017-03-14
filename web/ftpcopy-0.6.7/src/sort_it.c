/*
 * Copyright (C) 2002 Uwe Ohse, uwe@ohse.de
 * This is free software, licensed under the terms of the GNU General 
 * Public License Version 2, of which a copy is stored at:
 *    http://www.ohse.de/uwe/licenses/GPL-2
 * Later versions may or may not apply, see 
 *    http://www.ohse.de/uwe/licenses/
 * for information after a newer version has been published.
 */
#include <time.h>
#include "ssort.h"
#include "ftpparse.h"
#include "sort_it.h"
#include "byte.h"

unsigned long sortmode=SM_NEW;


static int cmp_them(const void *a, const void *b)
{
	const struct ftpparse *fa=a;
	const struct ftpparse *fb=b;
	if (sortmode==SM_NEW) return tai_less(&fb->mtime,&fa->mtime);
	if (sortmode==SM_OLD) return tai_less(&fa->mtime,&fb->mtime);
	if (sortmode==SM_LONG) return fb->size-fa->size;
	if (sortmode==SM_SHORT) return fa->size-fb->size;
	if (fa->namelen==fb->namelen)	
		return byte_diff(fa->name,fa->namelen,fb->name)
			* (sortmode==SM_ALPHA? 1 : -1);
	else {
		int x;
		x = byte_diff (fa->name, fa->namelen < fb->namelen ?
				fa->namelen : fb->namelen, fb->name);
		if (x) return x * (sortmode==SM_ALPHA? 1 : -1);
		if (fa->namelen<fb->namelen) return 1 * (sortmode==SM_ALPHA? 1 :-1);
		if (fa->namelen==fb->namelen) return 0;
		return -1 * (sortmode==SM_ALPHA? 1 :-1);
	}
}

void
sort_it(struct ftpparse *fp, int count)
{
    mssort((void *)fp,count,sizeof(*fp),cmp_them);
}

