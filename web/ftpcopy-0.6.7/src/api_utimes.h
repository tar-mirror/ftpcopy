/*
 * reimplementation of Daniel Bernstein's XXX.
 * placed in the public domain by Uwe Ohse, uwe@ohse.de.
 */
int 
api_utimes(const char *fname,
	unsigned long at_sec, unsigned long at_usec,
	unsigned long mt_sec, unsigned long mt_usec
	);
