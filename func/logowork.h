#include <stdio.h>
#include "os-logo.h"

void work_with_logo(char name[32]){
  if (strcmp(name, "debian") == 0){
    printf("%s\n", debian);
  } else if (strcmp(name, "manjaro") == 0){
    printf("%s\n", manjaro);
  }
}
