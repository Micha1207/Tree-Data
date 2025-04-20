/*
 * ram.h
 * Get RAM memory usage
 * ram.h is part of the Tree Monitor
 *
 * Written by Michael Ł. (Micha1207) in GNU Emacs.
 * 6 Apr 2025
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
    printf("%s: No such file or directory.", RAM_FILE);
    return;
  }

  char line[1024];
  int totu, freu, useu;
  while (fgets(line, sizeof(line), ramf)){
    if (sscanf(line, "MemTotal: %d kB", &totu) == 1){
      // Total space: done.
    } else if (sscanf(line, "Active: %d kB", &useu) == 1){
      // Total used space: done.
    }
  }

  *ram_total = totu / 1048576.0;
  *ram_usage = useu / 1048576.0;
    
  fclose(ramf);
}

#endif /*RAM_H*/
