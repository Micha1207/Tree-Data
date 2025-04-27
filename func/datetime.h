/*
 * datetime.h
 * Get date & time.
 * datetime.h is part of Tree Data.
 *
 * Written by Michael Ł. (Micha1207) in GNU Emacs.
 * 26 Apr 2025
*/

#ifndef DATETIME_H
#define DATETIME_H

#include <time.h>

char *dati() {
    static char buf[64];
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    strftime(buf, sizeof(buf), "%d.%m.%Y, %H:%M:%S", tm);
    return buf;
}

#endif
