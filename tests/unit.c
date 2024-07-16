#include "binaryfusefilter.h"
#include <assert.h>
#include <climits>
#include <numeric>


bool testbinaryfuse8(size_t size) {
  printf("testing binary fuse8 with size %zu\n", size);
  binary_fuse8_t filter(size);

  // Allocate vector of contiguous values [0, 1, 2, ..., size-1]
  std::vector<uint64_t> big_set(size);
  std::iota(big_set.begin(), big_set.end(), 0);

  // we construct the filter
  if(!filter.populate(big_set)) { printf("failure to populate\n"); return false; }

  for (size_t i = 0; i < size; i++) {
    if (!filter.contain(big_set[i])) {
      printf("bug!\n");
      return false;
    }
  }

  size_t random_matches = 0;
  size_t trials = 10000000;
  for (size_t i = 0; i < trials; i++) {
    uint64_t random_key = ((uint64_t)rand() << 32) + rand();
    if (filter.contain(random_key)) {
      if (random_key >= size) {
        random_matches++;
      }
    }
  }

  double fpp = random_matches * 1.0 / trials;
  printf(" fpp %3.5f (estimated) \n", fpp);
  double bpe = filter.size_in_bytes() * 8.0 / size;
  printf(" bits per entry %3.2f\n", bpe);
  printf(" bits per entry %3.2f (theoretical lower bound)\n", - log(fpp)/log(2));
  printf(" efficiency ratio %3.3f \n", bpe /(- log(fpp)/log(2)));
  return true;
}



bool testbinaryfuse16(size_t size) {
  printf("testing binary fuse16\n");
  binary_fuse16_t filter(size);

  // Allocate vector of contiguous values [0, 1, 2, ..., size-1]
  std::vector<uint64_t> big_set(size);
  std::iota(big_set.begin(), big_set.end(), 0);

  // we construct the filter
  if(!filter.populate(big_set)) { printf("failure to populate\n"); return false; }

  for (size_t i = 0; i < size; i++) {
    if (!filter.contain(big_set[i])) {
      printf("bug!\n");
      return false;
    }
  }

  size_t random_matches = 0;
  size_t trials = 10000000;
  for (size_t i = 0; i < trials; i++) {
    uint64_t random_key = ((uint64_t)rand() << 32) + rand();
    if (filter.contain(random_key)) {
      if (random_key >= size) {
        random_matches++;
      }
    }
  }
  double fpp = random_matches * 1.0 / trials;
  printf(" fpp %3.5f (estimated) \n", fpp);
  double bpe = filter.size_in_bytes() * 8.0 / size;
  printf(" bits per entry %3.2f\n", bpe);
  printf(" bits per entry %3.2f (theoretical lower bound)\n", - log(fpp)/log(2));
  printf(" efficiency ratio %3.3f \n", bpe /(- log(fpp)/log(2)));
  return true;
}



bool testbinaryfuse32(size_t size) {
  printf("testing binary fuse32\n");
  binary_fuse32_t filter(size);

  // Allocate vector of contiguous values [0, 1, 2, ..., size-1]
  std::vector<uint64_t> big_set(size);
  std::iota(big_set.begin(), big_set.end(), 0);

  // we construct the filter
  if(!filter.populate(big_set)) { printf("failure to populate\n"); return false; }

  for (size_t i = 0; i < size; i++) {
    if (!filter.contain(big_set[i])) {
      printf("bug!\n");
      return false;
    }
  }

  size_t random_matches = 0;
  size_t trials = 100000000;
  for (size_t i = 0; i < trials; i++) {
    uint64_t random_key = ((uint64_t)rand() << 32) + rand();
    if (filter.contain(random_key)) {
      if (random_key >= size) {
        random_matches++;
      }
    }
  }
  double fpp = random_matches * 1.0 / trials;
  printf(" fpp %3.5f (estimated) \n", fpp);
  double bpe = filter.size_in_bytes() * 8.0 / size;
  printf(" bits per entry %3.2f\n", bpe);
  printf(" bits per entry %3.2f (theoretical lower bound)\n", - log(fpp)/log(2));
  printf(" efficiency ratio %3.3f \n", bpe /(- log(fpp)/log(2)));
  return true;
}



bool testbinaryfuse8_dup(size_t size) {
  printf("testing binary fuse8 with duplicates\n");
  binary_fuse8_t filter(size);

  std::vector<uint64_t> big_set;
  big_set.reserve(size);

  size_t repeated_size = 10;
  for (size_t i = 0; i < size - repeated_size; ++i) {
    big_set.push_back(i); // we use contiguous values
  }
  for (size_t i = 0; i < repeated_size; i++) {
    big_set.push_back(i); // Repeat first repeated_size values
  }

  // we construct the filter
  if(!filter.populate(big_set)) { return false; }

  for (size_t i = 0; i < size; i++) {
    if (!filter.contain(big_set[i])) {
      printf("bug!\n");
      return false;
    }
  }

  size_t random_matches = 0;
  size_t trials = 10000000;
  for (size_t i = 0; i < trials; i++) {
    uint64_t random_key = ((uint64_t)rand() << 32) + rand();
    if (filter.contain(random_key)) {
      if (random_key >= size) {
        random_matches++;
      }
    }
  }
  double fpp = random_matches * 1.0 / trials;
  printf(" fpp %3.5f (estimated) \n", fpp);
  double bpe = filter.size_in_bytes() * 8.0 / size;
  printf(" bits per entry %3.2f\n", bpe);
  printf(" bits per entry %3.2f (theoretical lower bound)\n", - log(fpp)/log(2));
  printf(" efficiency ratio %3.3f \n", bpe /(- log(fpp)/log(2)));
  return true;
}



bool testbinaryfuse16_dup(size_t size) {
  printf("testing binary fuse16 with duplicates\n");
  binary_fuse16_t filter(size);

  std::vector<uint64_t> big_set;
  big_set.reserve(size);

  size_t repeated_size = 10;
  for (size_t i = 0; i < size - repeated_size; ++i) {
    big_set.push_back(i); // we use contiguous values
  }
  for (size_t i = 0; i < repeated_size; i++) {
    big_set.push_back(i); // Repeat first repeated_size values
  }

  // we construct the filter
  if(!filter.populate(big_set)) { return false; }

  for (size_t i = 0; i < size; i++) {
    if (!filter.contain(big_set[i])) {
      printf("bug!\n");
      return false;
    }
  }

  size_t random_matches = 0;
  size_t trials = 10000000;
  for (size_t i = 0; i < trials; i++) {
    uint64_t random_key = ((uint64_t)rand() << 32) + rand();
    if (filter.contain(random_key)) {
      if (random_key >= size) {
        random_matches++;
      }
    }
  }
  double fpp = random_matches * 1.0 / trials;
  printf(" fpp %3.5f (estimated) \n", fpp);
  double bpe = filter.size_in_bytes() * 8.0 / size;
  printf(" bits per entry %3.2f\n", bpe);
  printf(" bits per entry %3.2f (theoretical lower bound)\n", - log(fpp)/log(2));
  printf(" efficiency ratio %3.3f \n", bpe /(- log(fpp)/log(2)));
  return true;
}



bool testbinaryfuse32_dup(size_t size) {
  printf("testing binary fuse32 with duplicates\n");
  binary_fuse32_t filter(size);

  std::vector<uint64_t> big_set;
  big_set.reserve(size);

  size_t repeated_size = 10;
  for (size_t i = 0; i < size - repeated_size; ++i) {
    big_set.push_back(i); // we use contiguous values
  }
  for (size_t i = 0; i < repeated_size; i++) {
    big_set.push_back(i); // Repeat first repeated_size values
  }

  // we construct the filter
  if(!filter.populate(big_set)) { return false; }

  for (size_t i = 0; i < size; i++) {
    if (!filter.contain(big_set[i])) {
      printf("bug!\n");
      return false;
    }
  }

  size_t random_matches = 0;
  size_t trials = 100000000;
  for (size_t i = 0; i < trials; i++) {
    uint64_t random_key = ((uint64_t)rand() << 32) + rand();
    if (filter.contain(random_key)) {
      if (random_key >= size) {
        random_matches++;
      }
    }
  }
  double fpp = random_matches * 1.0 / trials;
  printf(" fpp %3.5f (estimated) \n", fpp);
  double bpe = filter.size_in_bytes() * 8.0 / size;
  printf(" bits per entry %3.2f\n", bpe);
  printf(" bits per entry %3.2f (theoretical lower bound)\n", - log(fpp)/log(2));
  printf(" efficiency ratio %3.3f \n", bpe /(- log(fpp)/log(2)));
  return true;
}



void failure_rate_binary_fuse16() {
  printf("testing binary fuse16 for failure rate\n");
  // we construct many 5000-long input cases and check the probability of failure.
  size_t size = 5000;
  std::vector<uint64_t> big_set;
  big_set.reserve(size);

  binary_fuse16_t filter(size);
  size_t failure = 0;
  size_t total_trials = 1000000;

  for(size_t trial = 0; trial <= 1000; trial++) {
    for (size_t i = 0; i < size; i++) {
      big_set.push_back(rand() + (((uint64_t) rand()) << 32));
    }
    if(!filter.populate(big_set)) {
      failure++;
    }

    big_set.clear();
  }

  printf("failures %zu out of %zu\n\n", failure, total_trials);
}

int main() {
  failure_rate_binary_fuse16();
  for(size_t size = 1000; size <= 1000000; size *= 300) {
    printf("== size = %zu \n", size);
    if(!testbinaryfuse8(size)) { abort(); }
    printf("\n");
    if(!testbinaryfuse16(size)) { abort(); }
    printf("\n");
    if(!testbinaryfuse32(size)) { abort(); }
    printf("\n");
    if(!testbinaryfuse8_dup(size)) { abort(); }
    printf("\n");
    if(!testbinaryfuse16_dup(size)) { abort(); }
    printf("\n");
    if(!testbinaryfuse32_dup(size)) { abort(); }
    printf("\n");
    printf("======\n");
  }
}