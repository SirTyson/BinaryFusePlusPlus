#include "binaryfusefilter.h"
#include <assert.h>
#include <time.h>
#include <numeric>


bool testbinaryfuse8(size_t size) {
  printf("testing binary fuse8 ");
  printf("size = %zu \n", size);

  binary_fuse_t<uint8_t> filter(size);

  // Allocate vector of contiguous values [0, 1, 2, ..., size-1]
  std::vector<uint64_t> big_set(size);
  std::iota(big_set.begin(), big_set.end(), 0);

  // we construct the filter
  bool constructed = filter.populate(big_set); // warm the cache
  if(!constructed) { return false; }
  for (size_t times = 0; times < 5; times++) {
    clock_t t;
    t = clock();
    std::ignore = filter.populate(big_set);
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

  // Allocate vector of contiguous values [0, 1, 2, ..., size-1]
  std::vector<uint64_t> big_set(size);
  std::iota(big_set.begin(), big_set.end(), 0);

  // we construct the filter
  bool constructed = filter.populate(big_set); // warm the cache
  if(!constructed) { return false; }
  for (size_t times = 0; times < 5; times++) {
    clock_t t;
    t = clock();
    std::ignore = filter.populate(big_set);
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
