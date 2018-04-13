/*
Compile: make palindrome
Run: ./palindrome
make palindrome && ./palindrome
*/

#include "base.h"

/**
(a) Todo: Implement.
Return whether a character is in the alphabet
*/
bool is_in_alphabet(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

/**
(b) Todo: Implement.
Return whether a String is a palindrome
*/
bool is_palindrome(char* s) {
  int len = strlen(s);
  int j=0;
  int count = 0;
  int number = 0;
  for(int m = 0; m < len; m++){
    if(is_in_alphabet(s[m])) {
      number++;
    }
  }
  char* str = xmalloc(number + 1);
  for (int i=0; i<len; i++)
    if (is_in_alphabet(s[i]))
      str[j++] = s[i];
  printf("%s\n",str);
  for (int i = 0; i < j / 2; i++)
    if (str[i] == str[(j-1)-i])
      count++;
    else
      return false;

  free(str);
  return count > 0;
}

/**
(c) Todo: Implement.
Return whether a String contains at least one palindrome of minimum size minimum_palindrome_size
*/
bool contains_palindrome(char* s, int minimum_palindrome_size) {
  int len = strlen(s);
  char* str = xmalloc(len +1 );

  int j = 0;
  for (int i=0; i<len; i++)
    if (is_in_alphabet(i))
      str[j++] = s[i];

  for (int i=0; i< (j-1)-minimum_palindrome_size; i++) {
    char* x = malloc(minimum_palindrome_size+1);
    memcpy(x, str +i, minimum_palindrome_size);
    x[minimum_palindrome_size] = '\0';
    bool b = is_palindrome(x);
    free(x);
    if (b) return true;
  }

  return false;
}




void test(void) {
    // (a)
    test_equal_b(is_in_alphabet('a'), true);
    test_equal_b(is_in_alphabet('y'), true);
    test_equal_b(is_in_alphabet('B'), true);
    test_equal_b(is_in_alphabet('X'), true);
    test_equal_b(is_in_alphabet(' '), false);
    test_equal_b(is_in_alphabet('.'), false);
    test_equal_b(is_in_alphabet('{'), false);

    // (b)
    test_equal_b(is_palindrome("hello world"), false);
    test_equal_b(is_palindrome("anna"), true);
    test_equal_b(is_palindrome(""), false);
    test_equal_b(is_palindrome("shower."), false);
    test_equal_b(is_palindrome("madam ?"), true);
    test_equal_b(is_palindrome("nurses run"), true);

    // (c)
    test_equal_b(contains_palindrome("hello world", 5), false);
    test_equal_b(contains_palindrome("hello world", 3), true);
    test_equal_b(contains_palindrome("anna", 3), true);
    test_equal_b(contains_palindrome("", 0), false);
    test_equal_b(contains_palindrome("shower thoughts by madam anna", 4), true);
    test_equal_b(contains_palindrome("madam anna is a nurse", 3), true);
    test_equal_b(contains_palindrome("nurses run", 4), true);

}

int main(void) {
    test();
    return 0;
}
