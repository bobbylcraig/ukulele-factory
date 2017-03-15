#include <iostream>
#include "ukulele.h"
#include <assert.h>

bool check_good();
bool check_bad();

int main()
{
  assert(check_good() == 1);
  assert(check_bad() == 0);
  return 0;
}

bool check_good() {
  Ukulele * test_uk = new Ukulele();

  // Add headstock
  test_uk->headstock->add_subpart('r', 13, 6, NULL, NULL, "brown");

  // Add neck
  test_uk->neck->add_subpart('r', 26, 4, NULL, NULL, "brown");

  // Add body
  test_uk->body->add_subpart('c', 15, NULL, NULL, NULL, "brown");
  test_uk->body->add_subpart('c', 20, NULL, NULL, NULL, "brown");
  test_uk->body->update_dist_bet(5);

  // Add strings
  test_uk->strings->add_subpart('c', 65, NULL, NULL, NULL, "nylon");
  test_uk->strings->add_subpart('c', 65, NULL, NULL, NULL, "nylon");
  test_uk->strings->add_subpart('c', 65, NULL, NULL, NULL, "nylon");
  test_uk->strings->add_subpart('c', 65, NULL, NULL, NULL, "nylon");

  return test_uk->quality_check();
}

bool check_bad() {
  Ukulele * test_uk = new Ukulele();

  // Add headstock
  test_uk->headstock->add_subpart('r', 13, 6, NULL, NULL, "brown");

  // Add neck
  test_uk->neck->add_subpart('r', -20, 4, NULL, NULL, "brown");   // Negative length should make it wrong

  // Add body
  test_uk->body->add_subpart('c', 15, NULL, NULL, NULL, "brown");
  test_uk->body->add_subpart('c', 20, NULL, NULL, NULL, "brown");
  test_uk->body->update_dist_bet(5);

  // Add strings
  test_uk->strings->add_subpart('c', 65, NULL, NULL, NULL, "nylon");
  test_uk->strings->add_subpart('c', 65, NULL, NULL, NULL, "nylon");
  test_uk->strings->add_subpart('c', 65, NULL, NULL, NULL, "nylon");
  test_uk->strings->add_subpart('c', 65, NULL, NULL, NULL, "nylon");

  return test_uk->quality_check();
}
