/*
 * cpu-temp.h
 * Measure CPU Temperature
 * cpu-temp.h in part of the Tree Monitor
 *
 * Written by Michael Ł. (Micha1207) in GNU Emacs.
 * 8 Apr 2025
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CPU_TEMP_FILE "/sys/class/thermal/thermal_zone0/temp"

int cpu_tempf(){
  FILE *cputf = fopen(CPU_TEMP_FILE, "r"); // Open file containing CPU Temperature.

  if (!cputf){                       // If cputf does not exist
    printf("No CPU_TEMP_FILE!!!\n"); // Print what you see on left in quotes.
  }
  
  int tempc;                    // Create vriable for temperature
  fscanf(cputf, "%d", &tempc);  // Read temperature
  fclose(cputf);                // Close file
  
  return tempc / 1000; // Return temp in C. For F.: change.
}

