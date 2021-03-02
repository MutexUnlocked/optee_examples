
#ifndef _UTIME_H
#define _UTIME_H

#include "time.h"

//typedef long time_t;

#ifdef __cplusplus
extern "C" {
#endif

struct utimbuf {
	time_t actime;
	time_t modtime;
};

int utime(const char *, const struct utimbuf *);

#ifdef __cplusplus
}
#endif

#endif	  // _UTIME_H
