#ifndef DRIVEIO_H
#define DRIVEIO_H

#include <stdio.h>
#include <stdlib.h>

#define DRIVE_CMD "df -h /"

void driveiof(char *size, char *used, char *free){
  FILE *drc = popen(DRIVE_CMD, "r");

  char bufrx[256];
  fgets(bufrx, sizeof(bufrx), drc);
  fgets(bufrx, sizeof(bufrx), drc);

  sscanf(bufrx, "%*s %s %s %s %*s %*s", size, used, free);

  fclose(drc);
}

#endif 
