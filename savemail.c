#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  unsigned char buf[8192];
  int len;

  fprintf(stdout, "---BEGIN DATA CONTENTS---\n");

  while (1) {
    len = fread(buf, 1, sizeof(buf), stdin);
    if (len <= 0) {
      break;
    }

    fwrite(buf, len, 1, stdout);
  }

  fprintf(stdout, "---END DATA CONTENTS---\n");

  return 0;
}
