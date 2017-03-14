#include "uotime.h"
#include "fmt.h"

char *
yyyy_mm_dd(char buf[11], uo_datetime_t *dt, char dash)
{
	char *p=buf;
	p+=fmt_uint0(p,dt->year,4);
	*p++=dash;
	p+=fmt_uint0(p,dt->mon+1,2);
	*p++=dash;
	p+=fmt_uint0(p,dt->day,2);
	*p=0;
	return buf;
}
char *
yyyy_mm_dd_hh_mm_ss(char buf[20], uo_datetime_t *dt, char dash)
{
	char *p=buf;
	p+=fmt_uint0(p,dt->year,4);
	*p++=dash;
	p+=fmt_uint0(p,dt->mon+1,2);
	*p++=dash;
	p+=fmt_uint0(p,dt->day,2);
	*p++=' ';
	p+=fmt_uint0(p,dt->hour,2);
	*p++=':';
	p+=fmt_uint0(p,dt->min,2);
	*p++=':';
	p+=fmt_uint0(p,dt->sec,2);
	*p=0;
	return buf;
}
