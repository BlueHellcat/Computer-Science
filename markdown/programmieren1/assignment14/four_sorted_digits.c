/*
Compile: make four_sorted_digits
Run: ./four_sorted_digits
Compile and run:
make four_sorted_digits && ./four_sorted_digits
*/

#include "base.h"

/*
Returns true if s contains at least 4 incrementing digits right behind one another. Else it returns false.
*/
bool four_sorted_digits(String s) {
  int count = 0;
  if(s_length(s) < 4){
    return false;
  }
  for(int i = 0; i<s_length(s);i++) {
    if(s[i] >= '0' && s[i] <= '9' && s[i+1] <= '0' && s[i+1] >= '9') {
      count -= 1;
      return false;
    }
    if(s[i] >='0' && s[i] <= '9'){
      if(s[i+1] >= '0' && s[i+1] <= '9') {
        if(s[i] <= s[i+1]) {
          count += 1;
        }
      }
    }
  }
  
  //printf("%i\n", count);
  if(count < 3) {
    return false;
  }
    return true; // todo: implement
}

void four_sorted_digits_test(void) {
    test_equal_b(four_sorted_digits(""), false);
    test_equal_b(four_sorted_digits("123"), false);
    test_equal_b(four_sorted_digits("abcd"), false);
    test_equal_b(four_sorted_digits("1234"), true);
    test_equal_b(four_sorted_digits("2479"), true);
    test_equal_b(four_sorted_digits("1111"), true);
    test_equal_b(four_sorted_digits("a123"), false);
    test_equal_b(four_sorted_digits("123a"), false);
    test_equal_b(four_sorted_digits("1234a"), true);
    test_equal_b(four_sorted_digits("xx1234y"), true);
    test_equal_b(four_sorted_digits("abc12345"), true);
    test_equal_b(four_sorted_digits("a 1 2 3 4 c"), false);
    test_equal_b(four_sorted_digits("a 3333 c"), true);
    test_equal_b(four_sorted_digits("123abc456"),false);
}

int main(void) {
    base_init();
    base_set_memory_check(true);
    four_sorted_digits_test();
    return 0;
}
