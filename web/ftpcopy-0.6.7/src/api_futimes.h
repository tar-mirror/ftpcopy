/*
 * placed in the public domain by Uwe Ohse, uwe@ohse.de.
 */
int 
api_futimes_1(int fd, 
	unsigned long at_sec, unsigned long at_usec,
	unsigned long mt_sec, unsigned long mt_usec
	);
int 
api_futimes_2(const char *fname, 
	unsigned long at_sec, unsigned long at_usec,
	unsigned long mt_sec, unsigned long mt_usec
	);
