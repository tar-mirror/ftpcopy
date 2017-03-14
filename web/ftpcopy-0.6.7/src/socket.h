/*
 * reimplementation of Daniel Bernstein's unix library.
 * placed in the public domain by Uwe Ohse, uwe@ohse.de.
 */
#ifndef SOCKET_H
#define SOCKET_H

#include "uint16.h"
#include "uint32.h"
#include "auto-have_ipv6.h"

int socket_tcp(void);
int socket_udp(void);

int socket_connect4 (int fd, const char *ip, uo_uint16_t port);
int socket_connected (int fd);
int socket_bind4 (int fd, const char *ip, uo_uint16_t port);
int socket_bind4_reuse (int fd, const char *ip, uo_uint16_t port);
int socket_listen (int fd, int backlog);
int socket_accept4 (int fd, char *ip, uo_uint16_t * port);
int socket_recv4 (int fd, char *buf, int len, char *ip, uo_uint16_t * port);
int socket_peek4 (int fd, char *buf, int len, char *ip, uo_uint16_t * port);
int socket_send4 (int fd, char *buf, int len, char *ip, uo_uint16_t port);
int socket_local4 (int fd, char *ip, uo_uint16_t * port);
int socket_remote4 (int fd, char *ip, uo_uint16_t * port);
void socket_htons (uo_uint16_t hport, uo_uint16_t *nport);
void socket_ntohs (uo_uint16_t nport, uo_uint16_t *hport);
int socket_tcpnodelay(int fd);
int socket_tcpdelay(int fd);
int socket_ipoptionskill(int fd);

void socket_tryreservein(int fd,int size);

int socket_family(int fd); /* returns -1, 4 or 6 */

extern int socket_flag_noipv6;
extern int socket_flag_noipv4;

/* raw ipv6 functions */
int socket_tcp6(void);
int socket_udp6(void);
int socket_connect6(int s,const char ip[16],uint16 port,uint32 scope_id);
int socket_bind6(int s,const char *ip,uint16 port,uint32 scope_id);
int socket_bind6_reuse(int s,const char *ip,uint16 port,uint32 scope_id);
int socket_accept6(int s,char *ip,uint16 *port,uint32 *scope_id);
int socket_recv6(int s,char *buf,unsigned int len,char *ip,uint16 *port,uint32 *scope_id);
int socket_send6(int s,const char *buf,unsigned int len,const char *ip,uint16 port,uint32 scope_id);
int socket_local6(int s,char *ip,uint16 *port,uint32 *scope_id);
int socket_remote6(int s,char *ip,uint16 *port,uint32 *scope_id);

/* functions falling back to ipv4, if v6 doesn't work */
int socket_tcp64(void);
int socket_udp64(void);
int socket_connect64(int s,const char ip[16],uint16 port,uint32 scope_id);
int socket_bind64(int s,const char *ip,uint16 port,uint32 scope_id);
int socket_bind64_reuse(int s,const char *ip,uint16 port,uint32 scope_id);
int socket_accept64(int s,char *ip,uint16 *port,uint32 *scope_id);
int socket_recv64(int s,char *buf,unsigned int len,char *ip,uint16 *port,uint32 *scope_id);
int socket_send64(int s,const char *buf,unsigned int len,const char *ip,uint16 port,uint32 scope_id);
int socket_local64(int s,char *ip,uint16 *port,uint32 *scope_id);
int socket_remote64(int s,char *ip,uint16 *port,uint32 *scope_id);

#endif
