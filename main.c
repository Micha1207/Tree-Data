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
#include "logowork.h"

// This is not a function. This just defines colors.
#include "colors.h"

// What I call 'data-getters'.
#define DATA_CMD   "uname -a"        // BASH
#define ARCH_CMD   "lscpu"            // BASH
#define OS_FILE    "/etc/os-release" // File only on GNU/Linux. (Maybe on Mac)

int main(){ // Main function.
  /* SYS_INFO */
  FILE *cmd = popen(DATA_CMD, "r"); // Read uname -a
  
  char dt[2048]; // Define buffer for data (dt).
  // Define buffers for data. u* are info not used in this case.
  char os[64], hnm[64], krn[64], u1[64], u2[64], u3[64], u4[64], u5[64], u6[64], u7[64], u8[64], u9[64], u10[64], typ[64]; 

  if (fgets(dt, sizeof(dt), cmd) == NULL) {             // If there's no data
    printf("Cannot get data out of `%s'.\n", DATA_CMD); // Print "Cannot get data out of `uname -a'.
    pclose(cmd); // close `cmd'
    return 1;
  }
  
  sscanf(dt, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s", os, hnm, krn, u1, u2, u3, u4, u5, u6, u7, u8, u9, u10, typ); // Names To Vals

  /* CPU_ARCH */
  FILE *dfa = popen(ARCH_CMD, "r");
  
  if (!dfa) {
    fprintf(stderr, "Nie udało się uruchomić polecenia lscpu.\n");
    return 1;
  }
  
  char buffer[1024];
  char arch[16];
  while (fgets(buffer, sizeof(buffer), dfa)) {
    if (strstr(buffer, "Architecture:")) {
      char *tmp = strstr(buffer, ": ") + 2;
      while (*tmp == ' ') tmp++; // pomiń spacje
      strncpy(arch, tmp, sizeof(arch) - 1);
      arch[sizeof(arch) - 1] = '\0';
      arch[strcspn(arch, "\n")] = '\0'; // usuń znak nowej linii
      break;
    }
  }
  pclose(dfa);
  
  /* OS_NAME */
  FILE *osnf = fopen(OS_FILE, "r");
  if (osnf == NULL) {
    printf("%s: No such file or directory. \n", OS_FILE);
  }
  
  char line[128];
  char osnm[64];
  char osid[32];
  while (fgets(line, sizeof(line), osnf) != NULL) {
    if (strstr(line, "PRETTY_NAME=")) {
      sscanf(line, "PRETTY_NAME=\"%[^\"]\"", osnm);
    }
    if (strstr(line, "ID=") && !strstr(line, "ID_LIKE=")) {
      sscanf(line, "ID=%63s", osid);
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
  work_with_logo(osid); // Function from "logowork.h"

  printf("\n");
  printf("%sOS Name:%s   %s\n", cyan, reset, osnm);             // Print OS Name.
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
