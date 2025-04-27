/*
 * cpu.h
 * Get CPU Usage
 * cpu.h is part of the Tree Monitor
 *
 * Written by Michael Ł. (Micha1207) in GNU Emacs.
 * 5 Apr 2025
*/
#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CPU_FILE "/proc/stat" // This is CPU Usage file on GNU/Linux OSes (distros). If you use other OS, you need to modify this code.

extern float cpu_usage; 

float cpu_data(){ // Function to get CPU Usage data.
  FILE *cpuf;                             // Make cpuf's type FILE *.
  char label[4];                          // Make label buffer.
  long int user1, nice1, system1, idle1;  // Integers for 1st read.
  long int user2, nice2, system2, idle2;  // Integers for 2nd read.

  cpuf = fopen(CPU_FILE, "r");       // Open CPU_FILE for 1st read of it.

  if (!cpuf) {                                          // If CPU_FILE does not exist
    printf("%s: No such file or directory.", CPU_FILE); // print <CPU_FILE>: No such file or directory message. This should not happen.
    return 1;
  }
  
  fscanf(cpuf, "%s %d %d %d %d", label, &user1, &nice1, &system1, &idle1); // Get CPU usage data and name them.
  fclose(cpuf); // Close CPU Data file (CPU_FILE).

  sleep(1); // Wait 1 second to make 2nd read of CPU_FILE

  cpuf = fopen(CPU_FILE, "r"); // Open 2nd time.

  if (!cpuf) {                                          // If CPU_FILE does not exist
    printf("%s: No such file or directory.", CPU_FILE); // print <CPU_FILE>: No such file or directory message. This should not happen.
    return 1;
  }
  
  fscanf(cpuf, "%s %d %d %d %d", label, &user2, &nice2, &system2, &idle2); // Get CPU usage data and name them.
  fclose(cpuf); // Close CPU Data file (CPU_FILE).

  int total1  = user1 + nice1 + system1 + idle1; // Summarize 1st total of read
  int active1 = user1 + nice1 + system1;         // Summarize 1st active

  int total2  = user2 + nice2 + system2 + idle2; // Summarize 2nd total of read
  int active2 = user2 + nice2 + system2;         // Summarize 2nd active

  float cpu_usage = 100.0 * (active2 - active1) / (total2 - total1); // Calculate CPU usage. 

  //printf("CPU: %.2f%%\n", cpu_usage); // Print it.

  return cpu_usage;
}

#endif /*CPU_H*/
