#include "trace.h"

char *__trace_file = "C:\\temp\\trace.log";
int __trace = 1;

void trace(const LPWSTR format, ...)
{
	if (!__trace) return;

	FILE *f = stderr;

	if (__trace_file != NULL)
	{
		if (fopen_s(&f, __trace_file, "a") != 0)
		{
			fprintf(stderr, "WARNING: Failed to open trace file '%s' for writing!\n", __trace_file);
			return;
		}
	}

	va_list ap;
	va_start(ap, format);
	vfwprintf(f, format, ap);
	va_end(ap);

	fprintf(f, "\n");

	if (__trace_file != NULL) fclose(f);
}
