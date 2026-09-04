#include <stdio.h>
#include <mecab.h>
#include <stdlib.h>
#include <string.h>

#define strnull(x) (x == NULL || x[0] == '\0')
#define countof(x) sizeof(x) / sizeof(x[0])

int main(void) {
  char name[512], *ptr;
  char *argv_a[] = {(char *)"mecab", (char *)"-Owakati"};
  char *argv_b[] = {(char *)"mecab", (char *)"-Ochasen"};
  mecab_t *mecab;

  sprintf(name, "すもももももももものうち");

  if ((mecab = mecab_new(countof(argv_a), argv_a)) != NULL) {
    fprintf(stdout, "mecab_new ok\n");
    if ((ptr = (char *)mecab_sparse_tostr(mecab, name)) != NULL) {
      fprintf(stdout, "mecab_sparse_tostr ok string is:\n%s\n", ptr);
    }
    mecab_destroy(mecab);
  }

  if ((mecab = mecab_new(countof(argv_b), argv_b)) != NULL) {
    fprintf(stdout, "mecab_new ok\n");
    if ((ptr = (char *)mecab_sparse_tostr(mecab, name)) != NULL) {
      fprintf(stdout, "mecab_sparse_tostr ok string is:\n%s\n", ptr);
    }
    mecab_destroy(mecab);
  }

  return 0;
}
