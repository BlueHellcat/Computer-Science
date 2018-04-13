/*
Compile: make sequence_count
Run: ./sequence_count
make sequence_count && ./sequence_count
*/

#include "base.h"


/**
(a) Todo: Implement.
Returns number of positions at which t occurs in s.
*/
int sequence_count(String s, String t) {
  int count = 0;
    for(int i = 0; i < strlen(s); i++) {
      String u = s_sub(s,i, strlen(t)+i);
      if(s_equals(u,t)){
        count++;
      }
    }
    return count;
}

/**
(b) Todo: Fix the bug.
Returns true if (and only if) the parentheses in s match and form a
correctly parenthesized expression. The function just checks the
parentheses and ignores any other characters.
*/
bool parentheses_correct(String s) {
    int p = 0;
    for (int i = 0; i < strlen(s); i++) {
      if(s[i] == '('){
        p++;
      }
      if(s[i] == ')') {
        p--;
      }
      if(p < 0){
        return false;
      }
    }
    if(p == 0) {
      return true;
    }
    return false;
}

void test(void) {
    // (a)
    test_equal_i(sequence_count("hello world", "l"), 3);
    test_equal_i(sequence_count("hello world", "w"), 1);
    test_equal_i(sequence_count("hello worlld", "ll"), 2);
    test_equal_i(sequence_count("hello world  ", " "), 3);
    test_equal_i(sequence_count("hello world hello", "hello"), 2);
    test_equal_i(sequence_count("hello world", "not"), 0);
    test_equal_i(sequence_count("hello world", "not in there..."), 0);
    test_equal_i(sequence_count("...", "..."), 1);
    test_equal_i(sequence_count("....", "..."), 2);
    test_equal_i(sequence_count(".....", "..."), 3);

    // (b)
    test_equal_b(parentheses_correct("(3"), false);
    test_equal_b(parentheses_correct("3)"), false);
    test_equal_b(parentheses_correct(")3("), false);
    test_equal_b(parentheses_correct("(3)"), true);
    test_equal_b(parentheses_correct("((3))"), true);
    test_equal_b(parentheses_correct("((3)"), false);
    test_equal_b(parentheses_correct("((3)))"), false);
    test_equal_b(parentheses_correct("()((3))"), true);
    test_equal_b(parentheses_correct("(1)+(2)"), true);
    test_equal_b(parentheses_correct(""), true);
}

int main(void) {
    test();
    return 0;
}
