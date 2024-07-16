#include "binaryfusefilter.h"
#include <assert.h>
#include <time.h>


bool testbinaryfuse8(size_t size) {
  printf("testing binary fuse8 ");
  printf("size = %zu \n", size);

  binary_fuse_t<uint8_t> filter(size);

  // we need some set of values
  uint64_t *big_set = (uint64_t *)malloc(sizeof(uint64_t) * size);
  for (size_t i = 0; i < size; i++) {
    big_set[i] = i; // we use contiguous values
  }
  // we construct the filter
  bool constructed = filter.populate(big_set, size); // warm the cache
  if(!constructed) { return false; }
  for (size_t times = 0; times < 5; times++) {
    clock_t t;
    t = clock();
    std::ignore = filter.populate(big_set, size);
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("It took %f seconds to build an index over %zu values. \n",
           time_taken, size);
  }
  return true;
}

bool testbinaryfuse16(size_t size) {
  printf("testing binary fuse16 ");
  printf("size = %zu \n", size);

  binary_fuse16_t filter(size);

  // we need some set of values
  uint64_t *big_set = (uint64_t *)malloc(sizeof(uint64_t) * size);
  for (size_t i = 0; i < size; i++) {
    big_set[i] = i; // we use contiguous values
  }
  // we construct the filter
  bool constructed = filter.populate(big_set, size); // warm the cache
  if(!constructed) { return false; }
  for (size_t times = 0; times < 5; times++) {
    clock_t t;
    t = clock();
    std::ignore = filter.populate(big_set, size);
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("It took %f seconds to build an index over %zu values. \n",
           time_taken, size);
  }
  return true;
}

int main() {
  for (size_t s = 10000000; s <= 10000000; s *= 10) {
    if (!testbinaryfuse8(s)) { abort(); }
    if (!testbinaryfuse16(s)) { abort(); }

    printf("\n");
  }
}
