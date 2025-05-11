/*
 * ram.h
 * Get RAM memory usage
 * ram.h is part of the Tree Monitor
 *
 * Written by Michael Ł. (Micha1207) in GNU Emacs.
 * 6 Apr 2025
 * Updated: 20 Apr 2025
 */
#ifndef RAM_H
#define RAM_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define RAM_FILE "/proc/meminfo"

void ram_data(float *ram_total, float *ram_usage){
  FILE *ramf = fopen(RAM_FILE, "r");

  if (!ramf){
    printf("%s: No such file or directory.\n", RAM_FILE);
    return;
  }

  char line[1024];
  int tot_kb = 0, avail_kb = 0;

  while (fgets(line, sizeof(line), ramf)){
    if (sscanf(line, "MemTotal: %d kB", &tot_kb) == 1){
      continue;
    } else if (sscanf(line, "MemAvailable: %d kB", &avail_kb) == 1){
      continue;
    }
  }

  fclose(ramf);

  *ram_total = tot_kb / 1024.0 / 1024.0;
  *ram_usage = (tot_kb - avail_kb) / 1024.0 / 1024.0; 
}

#endif /*RAM_H*/
