#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  int bytes, in_quot = 0;
  char c, buf[2048], *p1, *p2, *p3, *p4;
  size_t psize;

  while (1) {
    bytes = fread(buf, 1, sizeof(buf) - 1, stdin);
    if (bytes <= 0) {
      break;
    }
    buf[bytes] = '\0';
    /* クオート内外問わず\r\n->\n,\r->\nと変換 */
    for (p1 = buf; (p2 = strchr(p1, '\r')) != NULL; p1 = p2 + 1) {
      *p2 = '\n';
      if (*(p2 + 1) == '\n') {
        p2++; /* \r\n->\n */
      } else if (*(p2 + 1) == '\0') {
        *p2 = '\0'; /* バッファの区切りで来てしまった場合消去 */
        break;
      }
    }
    for (p1 = buf;
         (p2 = strchr(p1, '\'')) != NULL || (p2 = strchr(p1, '\0')) != NULL;
         p1 = p2 + 1) {
      c = *p2;
      *p2 = '\0';
      if (in_quot) /* ここで\nを消去する */
      {
        for (p3 = p1; (p4 = strchr(p3, '\n')) != NULL; p3 = p4 + 1) {
          psize = (size_t)p4 - (size_t)p3;
          fwrite(p3, psize, 1, stdout);
        }
        fwrite(p3, strlen(p3), 1, stdout);
      } else {
        fwrite(p1, strlen(p1), 1, stdout);
      }
      *p2 = c;
      if (c == '\0') {
        break;
      } else {
        putchar(c);
        in_quot = in_quot ? 0 : 1;
      }
    }
  }
  return 0;
}
