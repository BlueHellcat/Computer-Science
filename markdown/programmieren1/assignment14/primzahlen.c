#include "stdio.h"

void primzahl(int num) {
  for(int i = 2; i <= num; i++) {
    int count = 0;
    for(int j = 2; j < i; j++) {
      if(i % j == 0) {
        count++;
      }
    }
    if(count == 0) {
      printf("%i\n", i);
    }
  }
}

int main(void) {
  primzahl(1000000);
  return 0;
}
