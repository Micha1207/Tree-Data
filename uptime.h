#include <stdio.h>

#define UPTIME_FILE "/proc/uptime"

int uptime() {
  FILE *timef = fopen(UPTIME_FILE, "r");

  if (timef == NULL) {
    printf("Cannot open %s.", UPTIME_FILE);
    return -1;
  }
  
  double uptime_val;
  fscanf(timef, "%lf", &uptime_val);
  fclose(timef);
    
  int sec = (int)uptime_val;
  int min = sec / 60;
  return min;
}
