/*
 * main.c
 * Main code of datafetch.
 *
 * Written by Michael Ł. (Micha1207) in GNU Emacs.
 * Last edit on: 13 Apr 2025
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Include files with functions
#include "cpu.h"
#include "ram.h"
#include "cpu-temp.h"

// This is not a function. THs just defines colors.
#include "colors.h"

#define DATA_CMD "uname -a" // Define command for getting system info. This one is BASH command.
#define ARCH_CMD "arch"
#define OS_FILE  "/etc/os-release"

int main(){ // Main function.
  /* SYS_INFO */
  FILE *cmd = popen(DATA_CMD, "r"); 
  
  char dt[2048];
  char os[64], hnm[64], krn[64], u1[64], u2[64], u3[64], u4[64], u5[64], u6[64], u7[64], u8[64], u9[64], arch1[64], type[64];

  if (fgets(dt, sizeof(dt), cmd) == NULL) {
    printf("Cannot get data out of `%s'.\n", DATA_CMD);
    pclose(cmd);
    return 1;
  }
  
  sscanf(dt, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s", os, hnm, krn, u1, u2, u3, u4, u5, u6, u7, u8, u9, arch1, type);

  /* CPU_ARCH */
  FILE *afp = popen(ARCH_CMD, "r"); 
  
  char dta[2048];
  char arch[16];

  if (fgets(dta, sizeof(dta), afp) == NULL) {
    printf("Cannot get data out of `%s'.\n", ARCH_CMD);
    pclose(afp);
    return 1;
  }
  
  sscanf(dta, "%s", arch);

  /* OS NAME */
  FILE *osnf = fopen(OS_FILE, "r");
  if (osnf == NULL) {
    printf("%s: No such file or directory. \n", OS_FILE);
  }
  
  char line[128];
  char osnm[64];
  while (fgets(line, sizeof(line), osnf) != NULL) {
    if (strstr(line, "PRETTY_NAME=")) {
      sscanf(line, "PRETTY_NAME=\"%[^\"]\"", osnm);
    }
  }
  
  fclose(osnf);
  
  /* CPU */
  float cpu_usage = cpu_data();  // Run cpu_data function to get CPU usage.
  int   cpu_tempc = cpu_tempf(); // Run cpu_tempf() to get CPU Temp.
  
  /* RAM */
  float ram_total, ram_usage; // Declare RAM Variables.

  ram_data(&ram_total, &ram_usage); // Run ram_data function.

  float ram_free = ram_total - ram_usage; // Calculate free RAM.

  /* Print result */
  printf("%sOS Name:%s   %s\n", cyan, reset, os);             // Print OS Name.
  printf("%sHostname:%s  %s\n", cyan, reset, hnm);              // Print hostname.
  printf("%sKernel:%s    %s\n", cyan, reset, krn);              // Print kernel name.
  printf("%sCPU Arch:%s  %s\n", cyan, reset, arch);             // Print CPU architecture.
  printf("%sCPU Usage:%s %.2f%%\n", cyan, reset, cpu_usage);    // Print CPU usage.
  printf("%sCPU Temp:%s  %d\u00B0C\n", cyan, reset, cpu_tempc); // Print CPU temp.
  printf("%sRAM Total:%s %.2f GB\n", cyan, reset, ram_total);   // Print All RAM space.
  printf("%sRAM Usage:%s %.2f GB\n", cyan, reset, ram_usage);   // Print used RAM space.
  printf("%sRAM Free:%s  %.2f GB\n", cyan, reset, ram_free);    // Print free RAM.
  return 0;
}
