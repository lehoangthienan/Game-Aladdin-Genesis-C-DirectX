#ifndef _TRACE_H
#define _TRACE_H

#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

void trace(const LPWSTR format, ...);

#endif
