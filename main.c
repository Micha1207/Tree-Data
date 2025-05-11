/*
 * main.c
 * Main code of Tree Data
 *
 * Written by Michael Ł. (Micha1207) in GNU Emacs.
 * 10 May 2025
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "func/cpu.h"
#include "func/ram.h"
#include "func/driveio.h"
#include "func/uptime.h"
#include "func/os.h"
#include "func/logowork.h"

#include "colors.h"
#define color red

#define ENABLE_FLAGS 1

// Name variables used in main()
char os[64], hostname[64], kernel[64], osnm[64], osid[32];
int hrs, min, sec;
float usage = 0.0, cpu_temp = 0.0, ram_total, ram_usage;
char d_size[256], d_used[256], d_free[256];

int main() {  
  /* OS_DATA */
  os_data(os, hostname, kernel, osid, osnm);
 
  /* CPU_DATA */
  cpu_usag();
  cpu_arch();
  cpu_cores();
  cpu_modelf();
  cpu_tempf();
  
  /* RAM_DATA */
  float ram_total, ram_usage;             // Declare RAM Variables.
  ram_data(&ram_total, &ram_usage);       // Run ram_data function.
  float ram_free = ram_total - ram_usage; // Calculate free RAM.
  
  /* ROOT_DRIVE_SPACES */
  char d_size[256], d_used[256], d_free[256];
  driveiof(d_size, d_used, d_free);
  
  /* UPTIME */
  uptime(&hrs, &min, &sec);
  
  /* PRINT_DATA */
  work_with_logo(osid);                                                                        // Print logo
  printf("\n");                                                                                // Space between logo and data
  printf("%sOS:%s        %s\n", color, reset, osnm);                                           // Print OS name
  printf("%sHostname:%s  %s\n", color, reset, hostname);                                       // Print hostname
  printf("%sKernel:%s    %s\n", color, reset, kernel);                                         // Print Kernel
  printf("%sUptime:%s    %d hours, %d minutes and %d seconds\n", color, reset, hrs, min, sec); // Print uptime
  printf("%sCPU Arch:%s  %s\n", color, reset, arch);                                           // Print CPU architecture
  printf("%sCPU Cores:%s %d\n", color, reset, cores);                                          // Print CPU cores, or actually threads
  printf("%sCPU Model:%s %s\n", color, reset, cpu_model);                                      // Print CPU model
  printf("%sCPU Usage:%s %.2f%%\n", color, reset, usage);                                      // Print CPU usage
  printf("%sCPU Temp:%s  %.2f°C\n", color, reset, cpu_temp);                                   // Print CPU Temp
  printf("%sRAM:%s       %.2fGB / %.2fGB\n", color, reset, ram_usage, ram_total);              // Print RAM memory data
  printf("%sDISK:%s      %sB / %sB\n", color, reset, d_used, d_size);                          // Print '/' size data
  
  return 0;
}
