#include "tests/add.h"
#include "tests/helpers.h"

int main(void) {
  SRunner *sr;
  int number_failed = 0;
  sr = srunner_create(suite_create(""));
  srunner_add_suite(sr, testHelpers());
  srunner_add_suite(sr, testAdd());
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? 0 : 1;
}