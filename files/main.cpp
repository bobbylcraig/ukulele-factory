#include <iostream>
#include "ukulele.h"
#include <assert.h>

bool check_good();
bool check_bad();
bool check_bad2();
bool check_bad3();

int main()
{
  assert(check_good() == 1);
  assert(check_bad() == 0);
  assert(check_bad2() == 0);
  assert(check_bad3() == 0);
  std::cout << "All Tests Passed" << std::endl;
  return 0;
}

// Good params
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
  test_uk->strings->add_subpart('s', 65, 24, NULL, NULL, "nylon");
  test_uk->strings->add_subpart('s', 65, 30, NULL, NULL, "nylon");
  test_uk->strings->add_subpart('s', 65, 37, NULL, NULL, "nylon");
  test_uk->strings->add_subpart('s', 65, 26, NULL, NULL, "nylon");

  return test_uk->quality_check();
}

// Checking negative lengths
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
  test_uk->strings->add_subpart('s', 65, 24, NULL, NULL, "nylon");
  test_uk->strings->add_subpart('s', 65, 30, NULL, NULL, "nylon");
  test_uk->strings->add_subpart('s', 65, 37, NULL, NULL, "nylon");
  test_uk->strings->add_subpart('s', 65, 26, NULL, NULL, "nylon");

  return test_uk->quality_check();
}

// Checking neck longer than strings
bool check_bad2() {
  Ukulele * test_uk = new Ukulele();

  // Add headstock
  test_uk->headstock->add_subpart('r', 13, 6, NULL, NULL, "brown");

  // Add neck
  test_uk->neck->add_subpart('r', 84, 4, NULL, NULL, "brown");   // Too long of a neck

  // Add body
  test_uk->body->add_subpart('c', 15, NULL, NULL, NULL, "brown");
  test_uk->body->add_subpart('c', 20, NULL, NULL, NULL, "brown");
  test_uk->body->update_dist_bet(5);

  // Add strings
  test_uk->strings->add_subpart('s', 65, 24, NULL, NULL, "nylon");
  test_uk->strings->add_subpart('s', 65, 30, NULL, NULL, "nylon");
  test_uk->strings->add_subpart('s', 65, 37, NULL, NULL, "nylon");
  test_uk->strings->add_subpart('s', 65, 26, NULL, NULL, "nylon");

  return test_uk->quality_check();
}

// Checking two strings being the same thickness
bool check_bad3() {
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
  test_uk->strings->add_subpart('s', 65, 30, NULL, NULL, "nylon"); // same as below
  test_uk->strings->add_subpart('s', 65, 30, NULL, NULL, "nylon"); // same as above
  test_uk->strings->add_subpart('s', 65, 37, NULL, NULL, "nylon");
  test_uk->strings->add_subpart('s', 65, 26, NULL, NULL, "nylon");

  return test_uk->quality_check();
}
