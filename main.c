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
#include "func/cpu.h"
#include "func/ram.h"
#include "func/cpu-temp.h"
#include "func/logowork.h"
#include "func/uptime.h"
#include "func/datetime.h"
#include "func/driveio.h"

// This is not a function. This just defines colors.
#include "colors.h"
#define  color red // Define info_names color. Make sure color is in the 'colors.h' file.

// What I call 'data-getters'.
#define DATA_CMD      "uname -a"        // BASH
#define CPU_CMD       "lscpu"           // BASH
#define OS_FILE       "/etc/os-release" // File only on GNU/Linux. (Maybe on Mac)
#define CPU_CORES_CMD "nproc"           // BASH
#define DRV_CMD       "df -h /"         // BASH

// If you don't want flags (--<option>), change 1 to 0.
#define ENABLE_FLAGS 1

int main(int argc, char *argv[]){ // Main function.  
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
  FILE *dfa = popen(CPU_CMD, "r");
  
  if (!dfa) {
    fprintf(stderr, "Could not run `lscpu'.\n");
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

  /* CPU_NCORES */
  FILE *cnp = popen(CPU_CORES_CMD, "r");

  if (cnp == NULL) {
    printf("Cannot run %s.\n", CPU_CORES_CMD);
    return -1;
  }

  int cores = 0;
  fscanf(cnp, "%d", &cores);
  pclose(cnp);
  
  /* CPU_MODEL */
  FILE *dfm = popen(CPU_CMD, "r");
  
  if (!dfm) {
    fprintf(stderr, "Could not run `lscpu'.\n");
    return 1;
  }
  
  char bufferm[1024];
  char cpu_model[128];
  while (fgets(bufferm, sizeof(bufferm), dfm)) {
    if (strstr(bufferm, "Model name:")) {
      char *tmp1 = strstr(bufferm, ": ") + 2;
      while (*tmp1 == ' ') tmp1++; // pomiń spacje
      strncpy(cpu_model, tmp1, sizeof(cpu_model) - 1);
      cpu_model[sizeof(cpu_model) - 1] = '\0';
      cpu_model[strcspn(cpu_model, "\n")] = '\0'; // usuń znak nowej linii
      break;
    }
  }
  pclose(dfm);
  
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

  /* UPTIME */
  int timeup = uptime() / 60;

  /* LOCAL_DATETIME */
  char *datetime = dati();

  /* DISK_SPACE */
  char d_size[256], d_used[256], d_free[256];
  driveiof(DRV_CMD, d_size, d_used, d_free);

  /* GET_SHELL */
  const char *shell = getenv("SHELL");
  
  /* PRINT_DATA_AND_OPERATE_ON_FLAGS */
  if (argc > 1 && strcmp(argv[1], "--no-logo") == 0){
    printf("");
  } else {
    work_with_logo(osid);
  }

  const char *pcolor;
  if (argc > 1 && strcmp(argv[1], "--no-color") == 0){
    pcolor = reset;
  } else {
    pcolor = color;
  }
    
  printf("%sOS Name:%s       %s\n", pcolor, reset, osnm);             // Print OS Name.
  printf("%sHostname:%s      %s\n", pcolor, reset, hnm);              // Print hostname.
  printf("%sKernel:%s        %s\n", pcolor, reset, krn);              // Print kernel name.
  printf("%sUptime:%s        %dh\n", pcolor, reset, timeup);          // Print system uptime.
  printf("%sDate & Time:%s   %s\n", pcolor, reset, datetime);         // Print system date & time.
  printf("%sSystem Shell:%s  %s\n", pcolor, reset, shell);            // Print system SHELL.
  printf("%sCPU Model:%s     %s\n", pcolor, reset, cpu_model);        // Print CPU Model.
  printf("%sCPU Cores:%s     %d\n", pcolor, reset, cores);            // Print CPU Core number.
  printf("%sCPU Arch:%s      %s\n", pcolor, reset, arch);             // Print CPU architecture.
  printf("%sCPU Usage:%s     %.2f%%\n", pcolor, reset, cpu_usage);    // Print CPU usage.
  printf("%sCPU Temp:%s      %d\u00B0C\n", pcolor, reset, cpu_tempc); // Print CPU temp.
  printf("%sRAM Total:%s     %.2f GB\n", pcolor, reset, ram_total);   // Print All RAM space.
  printf("%sRAM Usage:%s     %.2f GB\n", pcolor, reset, ram_usage);   // Print used RAM space.
  printf("%sRAM Free:%s      %.2f GB\n", pcolor, reset, ram_free);    // Print free RAM.
  printf("%sDISC '/' size:%s %sB\n", pcolor, reset, d_size);
  printf("%sDISC '/' used:%s %sB\n", pcolor, reset, d_used);
  printf("%sDISC '/' free:%s %sB\n", pcolor, reset, d_free);
  return 0;
}
