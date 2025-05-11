/*
 * cpu.h
 * Get CPU Usage, Arch, Cores and Model Name
 * cpu.h is part of the Tree Monitor
 *
 * Written by Michael Ł. (Micha1207) in GNU Emacs.
 * 9 May 2025
*/

#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CPU_FILE       "/proc/stat"
#define CPU_CMD        "lscpu"
#define CPU_CORES_CMD  "nproc"
#define CPU_TEMP_FILE  "/sys/class/thermal/thermal_zone0/temp"

extern float usage;
extern float cpu_temp;

void cpu_usag(){
  FILE *cpuf;
  char label[5];
  long int user1, nice1, system1, idle1;
  long int user2, nice2, system2, idle2;

  cpuf = fopen(CPU_FILE, "r");
  if (!cpuf) {
    printf("%s: No such file or directory.\n", CPU_FILE);
    return;
  }
  fscanf(cpuf, "%s %ld %ld %ld %ld", label, &user1, &nice1, &system1, &idle1);
  fclose(cpuf);

  sleep(1);

  cpuf = fopen(CPU_FILE, "r");
  if (!cpuf) {
    printf("%s: No such file or directory.\n", CPU_FILE);
    return;
  }
  fscanf(cpuf, "%s %ld %ld %ld %ld", label, &user2, &nice2, &system2, &idle2);
  fclose(cpuf);

  int total1  = user1 + nice1 + system1 + idle1;
  int active1 = user1 + nice1 + system1;
  int total2  = user2 + nice2 + system2 + idle2;
  int active2 = user2 + nice2 + system2;

  usage = 100.0 * (active2 - active1) / (total2 - total1);
}

void cpu_tempf() {
  FILE *cputf = fopen(CPU_TEMP_FILE, "r");
  if (!cputf) {
    printf("No CPU_TEMP_FILE!\n");
    cpu_temp = 0.0;
    return;
  }

  int tempc;
  if (fscanf(cputf, "%d", &tempc) != 1) {
    printf("Failed to read temperature.\n");
    fclose(cputf);
    cpu_temp = 0.0;
    return;
  }

  fclose(cputf);
  cpu_temp = tempc / 1000.0;
}

char arch[64];
void cpu_arch() {
  FILE *dfa = popen(CPU_CMD, "r");
  if (!dfa) {
    printf("Could not run %s.\n", CPU_CMD);
    return;
  }

  char buffer[256];
  while (fgets(buffer, sizeof(buffer), dfa)) {
    if (strstr(buffer, "Architecture:")) {
      char *tmp = strstr(buffer, ": ") + 2;
      while (*tmp == ' ') tmp++;
      strncpy(arch, tmp, sizeof(arch) - 1);
      arch[sizeof(arch) - 1] = '\0';
      arch[strcspn(arch, "\n")] = '\0';
      break;
    }
  }
  pclose(dfa);
}

int cores = 0;
void cpu_cores() {
  FILE *cnp = popen(CPU_CORES_CMD, "r");
  if (!cnp) {
    printf("Could not run %s.\n", CPU_CORES_CMD);
    return;
  }
  fscanf(cnp, "%d", &cores);
  pclose(cnp);
}

char cpu_model[128];
void cpu_modelf() {
  FILE *dfm = popen(CPU_CMD, "r");
  if (!dfm) {
    printf("Could not run %s.\n", CPU_CMD);
    return;
  }

  char buffer[256];
  while (fgets(buffer, sizeof(buffer), dfm)) {
    if (strstr(buffer, "Model name:")) {
      char *tmp = strstr(buffer, ": ") + 2;
      while (*tmp == ' ') tmp++;
      strncpy(cpu_model, tmp, sizeof(cpu_model) - 1);
      cpu_model[sizeof(cpu_model) - 1] = '\0';
      cpu_model[strcspn(cpu_model, "\n")] = '\0';
      break;
    }
  }
  pclose(dfm);
}

#endif /* CPU_H */
