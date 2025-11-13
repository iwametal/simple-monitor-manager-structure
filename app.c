#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "monitor.h"


int
main(int argc, char *argv[])
{
    Monitors *monitors = NULL;
    monitors = register_monitor(monitors, 1, "iwa monitor", "dash:a215385a-7055-4bf3-aff1-f82b99e7254a", "iwa@192.168.169.1");
    monitors = register_monitor(monitors, 2, "coffee monitor", "bash:12a9db0b-715f-4282-9876-7561848d03ce", "coffee@192.168.169.3");
    monitors = register_monitor(monitors, 3, "cappuccino monitor", "bash:a09eef9e-e810-4892-b2d1-3a20b0618881", "cappuccino@192.168.169.2");
    monitors = register_monitor(monitors, 4, "adm monitor", "sh:e3a83dd7-1f39-4e58-814c-467cc33372c9", "adm@192.168.168.12");

    fprintf(stdout, "Sorting monitors by shell id\n");
    sort_monitors(monitors, sort_by_shell_id);

    list_monitors(monitors, -1, 5);

    fprintf(stdout, "Sorting monitors by lambda conn\n");
    sort_monitors(monitors, sort_by_lambda_conn);

    list_monitors(monitors, -1, 5);

    fprintf(stdout, "Sorting monitors by id\n");
    sort_monitors(monitors, sort_by_id);

    list_monitors(monitors, -1, 5);

    fprintf(stdout, "Sorting monitors by monitor name\n");
    sort_monitors(monitors, sort_by_monitor_name);

    list_monitors(monitors, -1, 5);

    free_monitors(monitors);
    return 0;
}
