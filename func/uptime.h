#include <stdio.h>

#define UPTIME_FILE "/proc/uptime"

int uptime(int *hrs, int *min, int *sec) {
  FILE *timev = fopen(UPTIME_FILE, "r");

  if (timev == NULL) {
    printf("Cannot open %s.\n", UPTIME_FILE);
    return -1;
  }

  double uptime_val;
  if (fscanf(timev, "%lf", &uptime_val) != 1) {
    printf("Error reading %s.\n", UPTIME_FILE);
    fclose(timev);
    return -1;
  }

  fclose(timev);

  int total_sec = (int)uptime_val;
  *hrs = total_sec / 3600;
  *min = (total_sec % 3600) / 60;
  *sec = total_sec % 60;

  return 0;
}
