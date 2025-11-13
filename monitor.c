#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "monitor.h"

#define UTF_INVALID 0xFFFD
#define UTF_SIZ     4
#define BETWEEN(X, A, B) ((A) <= (X) && (X) <= (B))

static const unsigned char utfbyte[UTF_SIZ + 1] = {0x80,    0, 0xC0, 0xE0, 0xF0};
static const unsigned char utfmask[UTF_SIZ + 1] = {0xC0, 0x80, 0xE0, 0xF0, 0xF8};
static const long utfmin[UTF_SIZ + 1] = {       0,    0,  0x80,  0x800,  0x10000};
static const long utfmax[UTF_SIZ + 1] = {0x10FFFF, 0x7F, 0x7FF, 0xFFFF, 0x10FFFF};


struct Monitor {
    unsigned short id;
    char *monitor_name;
    char *shell_id;
    char *lambda_conn;
};

struct Monitors {
    struct Monitor monitor;
    struct Monitors *next;
};

struct Shell {
    char *shell_;
    /*
     * data shell
     */
};


Monitors *
register_monitor(Monitors *monitors, unsigned short id, const char *monitor_name, const char *shell_id, const char *lambda_conn)
{
    Monitors *mon = malloc(sizeof(Monitors));
    if (!mon) {
        fprintf(stderr, "Não foi possível criar um novo monitor. Memória insuficiente.");
        return NULL;
    }

    mon->monitor.id = id;

    mon->monitor.shell_id = strdup(shell_id);
    mon->monitor.monitor_name = strdup(monitor_name);
    mon->monitor.lambda_conn = strdup(lambda_conn);

    mon->next = NULL;

    if (monitors == NULL) return mon;

    Monitors *head;
    for (head = monitors; head->next != NULL; head = head->next)
        ;
    head->next = mon;
    return monitors;
}


void
__list_monitors(Monitors *monitors, unsigned short list_size, unsigned short items_per_page)
{
    unsigned short counter = 0;
    Monitors *head = monitors;
    for (Monitors *i = monitors; i != NULL && counter++ < list_size; i = i->next) {
        fprintf(stdout, "%u) %s [%u] : %s : %s\n", counter, i->monitor.monitor_name, i->monitor.id, i->monitor.shell_id, i->monitor.lambda_conn);
        if (!(counter % items_per_page) && (counter < list_size)) {
            fprintf(stdout, "\n[Press enter to list next page...]\n");
            getchar();
        }
    }
}


int
sort_by_id(const Monitor *a, const Monitor *b)
{
    return (int)a->id - (int)b->id;
}


int
sort_by_shell_id(const Monitor *a, const Monitor *b)
{
    return strcmp(a->shell_id, b->shell_id);
}


int
sort_by_monitor_name(const Monitor *a, const Monitor *b)
{
    return strcmp(a->monitor_name, b->monitor_name);
}


int
sort_by_lambda_conn(const Monitor *a, const Monitor *b)
{
    return strcmp(a->lambda_conn, b->lambda_conn);
}


void
swap_monitor_data(Monitor *a, Monitor *b) {
    Monitor temp = *a;
    *a = *b;
    *b = temp;
}


void
sort_monitors(Monitors *monitors, MonitorComparator sort_field) {
    for (Monitors *i = monitors; i != NULL; i = i->next) {
        Monitors *min = i;
        for (Monitors *j = i->next; j != NULL; j = j->next)
            if (sort_field(&j->monitor, &min->monitor) < 0)
                min = j;

        if (min != i) swap_monitor_data(&i->monitor, &min->monitor);
    }
}


void
free_monitors(Monitors *monitors)
{
    while (monitors) {
        Monitors *next = monitors->next;
        free(monitors->monitor.shell_id);
        free(monitors->monitor.monitor_name);
        free(monitors->monitor.lambda_conn);
        free(monitors);
        monitors = next;
    }
}


static long
utf8decodebyte(const char c, size_t *i)
{
    for (*i = 0; *i < (UTF_SIZ + 1); ++(*i))
        if (((unsigned char)c & utfmask[*i]) == utfbyte[*i])
            return (unsigned char)c & ~utfmask[*i];
    return 0;
}


static size_t
utf8validate(long *u, size_t i)
{
    if (!BETWEEN(*u, utfmin[i], utfmax[i]) || BETWEEN(*u, 0xD800, 0xDFFF))
        *u = UTF_INVALID;
    for (i = 1; *u > utfmax[i]; ++i)
      ;
    return i;
}
