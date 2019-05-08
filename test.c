#include <stdio.h>

int print_int(int x) {
  printf("%d\n", x);
  return 0;
}

int print_l(char x) {
  printf("%s\n", x ? "true" : "false");
  return 0;
}