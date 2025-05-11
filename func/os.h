int os_data(char *os, char *hostname, char *kernel, char *osid, char *osnm) {
  FILE *osnf = fopen("/etc/os-release", "r");
  if (osnf == NULL) {
    printf("No OS file.\n");
    return 1;
  }

  char line[128];
  while (fgets(line, sizeof(line), osnf) != NULL) {
    if (strstr(line, "PRETTY_NAME=")) {
      sscanf(line, "PRETTY_NAME=\"%[^\"]\"", osnm);
    }
    if (strstr(line, "ID=") && !strstr(line, "ID_LIKE=")) {
      sscanf(line, "ID=%31s", osid);
    }
  }
  fclose(osnf);

  FILE *cmd  = popen("uname -a", "r");
  if (!cmd) {
    printf("Can't run uname.\n");
    return 1;
  }

  char dt[2048];
  char u1[64], u2[64], u3[64], u4[64], u5[64];
  char u6[64], u7[64], u8[64], u9[64], u10[64], u11[64];

  if (fgets(dt, sizeof(dt), cmd) == NULL) {
    printf("Couldn't get data out of uname -a.\n");
    pclose(cmd);
    return 1;
  }

  pclose(cmd);

  sscanf(dt, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s", os, hostname, kernel,
         u1, u2, u3, u4, u5, u6, u7, u8, u9, u10, u11);

  return 0;
}
