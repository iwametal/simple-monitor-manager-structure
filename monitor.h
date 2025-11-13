#ifndef __MONITOR_H__
#define __MONITOR_H__


#include <limits.h>

#define list_monitors(MON, LSIZE, LPAG) ((LSIZE < 0 || LSIZE > USHRT_MAX) ? __list_monitors(MON, USHRT_MAX, LPAG) : __list_monitors(MON, LSIZE, LPAG))

typedef struct Monitor Monitor;
typedef struct Monitors Monitors;
typedef struct Shell Shell;

typedef int (*MonitorComparator)(const Monitor *, const Monitor *);


Monitors *
register_monitor(Monitors *monitors, unsigned short id, const char *shell_id, const char *monitor_name, const char *lambda_conn);

Monitors *
delete_monitor(unsigned short id);

Monitor*
get_monitor(unsigned short id);

void
__list_monitors(Monitors *monitors, unsigned short list_size, unsigned short items_per_page);

int
sort_by_id(const Monitor *a, const Monitor *b);

int
sort_by_shell_id(const Monitor *a, const Monitor *b);

int
sort_by_monitor_name(const Monitor *a, const Monitor *b);

int
sort_by_lambda_conn(const Monitor *a, const Monitor *b);

void
sort_monitors(Monitors *monitors, MonitorComparator comp_mon);

Shell*
connect(Monitor *monitor);

void
free_monitors(Monitors *monitors);


#endif