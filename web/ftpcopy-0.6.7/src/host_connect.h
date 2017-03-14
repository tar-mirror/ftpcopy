/* 
 * (C) 2001 Uwe Ohse, <uwe@ohse.de>.
 * Placed in the public domain.
 */
int host_connect4(const char *hostport, unsigned short defport, 
	unsigned long timeout, stralloc *remoteaddresses);
int xhost_connect4(const char *hostport, unsigned short defport, 
	unsigned long timeout, stralloc *remoteaddresses);
int xhost_connect64(const char *host, unsigned int defaultport,
  unsigned long timeout, stralloc *remoteaddresses);;
int host_connect64(const char *host, unsigned int defaultport,
  unsigned long timeout, stralloc *remoteaddresses);;

