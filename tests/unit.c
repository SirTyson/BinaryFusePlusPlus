#include "binaryfusefilter.h"
#include <assert.h>
#include <climits>



bool testbinaryfuse8(size_t size) {
  printf("testing binary fuse8 with size %zu\n", size);
  binary_fuse8_t filter;
  binary_fuse8_allocate(size, &filter);
  binary_fuse_t<uint8_t> filter2(size);

  // we need some set of values
  uint64_t *big_set = (uint64_t *)malloc(sizeof(uint64_t) * size);
  uint64_t *big_set2 = (uint64_t *)malloc(sizeof(uint64_t) * size);
  for (size_t i = 0; i < size; i++) {
    big_set[i] = i; // we use contiguous values
    big_set2[i] = i; // we use contiguous values
  }

  // we construct the filter
  if(!binary_fuse8_populate(big_set, size, &filter)) { printf("failure to populate\n"); return false; }
  if(!filter2.populate(big_set2, size)) { printf("failure to populate filter 2\n"); return false; }

  for (size_t i = 0; i < size; i++) {
    if (!binary_fuse8_contain(big_set[i], &filter)) {
      printf("bug!\n");
      return false;
    }

    if (!filter2.contain(big_set2[i])) {
      printf("bug!\n");
      return false;
    }
  }

  size_t buffer_size = binary_fuse8_serialization_bytes(&filter);
  char *buffer = (char*)malloc(buffer_size);
  binary_fuse8_serialize(&filter, buffer);
  binary_fuse8_free(&filter);
  binary_fuse8_deserialize(&filter, buffer);
  free(buffer);
  for (size_t i = 0; i < size; i++) {
    if (!binary_fuse8_contain(big_set[i], &filter)) {
      printf("bug!\n");
      return false;
    }
  }

  size_t random_matches = 0;
  size_t trials = 10000000;
  for (size_t i = 0; i < trials; i++) {
    uint64_t random_key = ((uint64_t)rand() << 32) + rand();
    if (binary_fuse8_contain(random_key, &filter)) {

      // Filters should have identical false positives
      if (!filter2.contain(random_key))
      {
        printf("bug!\n");
        return false;
      }
      if (random_key >= size) {
        random_matches++;
      }
    }
  }

  double fpp = random_matches * 1.0 / trials;
  printf(" fpp %3.5f (estimated) \n", fpp);
  double bpe = binary_fuse8_size_in_bytes(&filter) * 8.0 / size;
  printf(" bits per entry %3.2f\n", bpe);
  printf(" bits per entry %3.2f (theoretical lower bound)\n", - log(fpp)/log(2));
  printf(" efficiency ratio %3.3f \n", bpe /(- log(fpp)/log(2)));
  binary_fuse8_free(&filter);
  free(big_set);
  return true;
}



bool testbinaryfuse16(size_t size) {
  printf("testing binary fuse16\n");
  binary_fuse16_t filter;
  binary_fuse16_allocate(size, &filter);
  binary_fuse_t<uint16_t> filter2(size);

  // we need some set of values
  uint64_t *big_set = (uint64_t *)malloc(sizeof(uint64_t) * size);
  uint64_t *big_set2 = (uint64_t *)malloc(sizeof(uint64_t) * size);
  for (size_t i = 0; i < size; i++) {
    big_set[i] = i; // we use contiguous values
    big_set2[i] = i;
  }
  // we construct the filter
  if(!binary_fuse16_populate(big_set, size, &filter)) {  printf("failure to populate\n"); return false; }
  if(!filter2.populate(big_set2, size)) { printf("failure to populate filter 2\n"); return false; }

  for (size_t i = 0; i < size; i++) {
    if (!binary_fuse16_contain(big_set[i], &filter)) {
      printf("bug!\n");
      return false;
    }

    if (!filter2.contain(big_set2[i])) {
      printf("bug!\n");
      return false;
    }
  }

  size_t buffer_size = binary_fuse16_serialization_bytes(&filter);
  char *buffer = (char*)malloc(buffer_size);
  binary_fuse16_serialize(&filter, buffer);
  binary_fuse16_free(&filter);
  binary_fuse16_deserialize(&filter, buffer);
  free(buffer);
  for (size_t i = 0; i < size; i++) {
    if (!binary_fuse16_contain(big_set[i], &filter)) {
      printf("bug!\n");
      return false;
    }
  }

  size_t random_matches = 0;
  size_t trials = 10000000;
  for (size_t i = 0; i < trials; i++) {
    uint64_t random_key = ((uint64_t)rand() << 32) + rand();
    if (binary_fuse16_contain(random_key, &filter)) {

      // Filters should have identical false positives
      if (!filter2.contain(random_key))
      {
        printf("bug!\n");
        return false;
      }

      if (random_key >= size) {
        random_matches++;
      }
    }
  }
  double fpp = random_matches * 1.0 / trials;
  printf(" fpp %3.5f (estimated) \n", fpp);
  double bpe = binary_fuse16_size_in_bytes(&filter) * 8.0 / size;
  printf(" bits per entry %3.2f\n", bpe);
  printf(" bits per entry %3.2f (theoretical lower bound)\n", - log(fpp)/log(2));
  printf(" efficiency ratio %3.3f \n", bpe /(- log(fpp)/log(2)));
  binary_fuse16_free(&filter);
  free(big_set);
  return true;
}



bool testbinaryfuse8_dup(size_t size) {
  printf("testing binary fuse8 with duplicates\n");
  binary_fuse8_t filter;
  binary_fuse8_allocate(size, &filter);
  binary_fuse_t<uint8_t> filter2(size);

  // we need some set of values
  uint64_t *big_set = (uint64_t *)malloc(sizeof(uint64_t) * size);
  uint64_t *big_set2 = (uint64_t *)malloc(sizeof(uint64_t) * size);

  size_t repeated_size = 10;
  for (size_t i = 0; i < size - repeated_size; i++) {
    big_set[i] = i; // we use contiguous values
    big_set2[i] = i;
  }
  for (size_t i = 0; i < repeated_size; i++) {
    big_set[size - i - 1] = i; // we use contiguous values
    big_set2[size - i - 1] = i;
  }

  // we construct the filter
  if(!binary_fuse8_populate(big_set, size, &filter)) { return false; }
  if(!filter2.populate(big_set2, size)) { return false; }

  for (size_t i = 0; i < size; i++) {
    if (!binary_fuse8_contain(big_set[i], &filter)) {
      printf("bug!\n");
      return false;
    }

    if (!filter2.contain(big_set2[i])) {
      printf("bug!\n");
      return false;
    }
  }

  size_t random_matches = 0;
  size_t trials = 10000000;
  for (size_t i = 0; i < trials; i++) {
    uint64_t random_key = ((uint64_t)rand() << 32) + rand();
    if (binary_fuse8_contain(random_key, &filter)) {
      if (!filter2.contain(random_key))
      {
        printf("bug!\n");
        return false;
      }

      if (random_key >= size) {
        random_matches++;
      }
    }
  }
  double fpp = random_matches * 1.0 / trials;
  printf(" fpp %3.5f (estimated) \n", fpp);
  double bpe = binary_fuse8_size_in_bytes(&filter) * 8.0 / size;
  printf(" bits per entry %3.2f\n", bpe);
  printf(" bits per entry %3.2f (theoretical lower bound)\n", - log(fpp)/log(2));
  printf(" efficiency ratio %3.3f \n", bpe /(- log(fpp)/log(2)));
  binary_fuse8_free(&filter);
  free(big_set);
  return true;
}



bool testbinaryfuse16_dup(size_t size) {
  printf("testing binary fuse16 with duplicates\n");
  binary_fuse16_t filter;
  binary_fuse16_allocate(size, &filter);
  binary_fuse_t<uint16_t> filter2(size);

  // we need some set of values
  uint64_t *big_set = (uint64_t *)malloc(sizeof(uint64_t) * size);
  uint64_t *big_set2 = (uint64_t *)malloc(sizeof(uint64_t) * size);

  size_t repeated_size = 10;
  for (size_t i = 0; i < size - repeated_size; i++) {
    big_set[i] = i; // we use contiguous values
    big_set2[i] = i;
  }
  for (size_t i = 0; i < repeated_size; i++) {
    big_set[size - i - 1] = i; // we use contiguous values
    big_set2[size - i - 1] = i;
  }
  // we construct the filter
  if(!binary_fuse16_populate(big_set, size, &filter)) { return false; }
  if(!filter2.populate(big_set2, size)) { return false; }

  for (size_t i = 0; i < size; i++) {
    if (!binary_fuse16_contain(big_set[i], &filter)) {
      printf("bug!\n");
      return false;
    }

    if (!filter2.contain(big_set2[i])) {
      printf("bug!\n");
      return false;
    }
  }

  size_t random_matches = 0;
  size_t trials = 10000000;
  for (size_t i = 0; i < trials; i++) {
    uint64_t random_key = ((uint64_t)rand() << 32) + rand();
    if (binary_fuse16_contain(random_key, &filter)) {
      if (!filter2.contain(random_key))
      {
        printf("bug!\n");
        return false;
      }

      if (random_key >= size) {
        random_matches++;
      }
    }
  }
  double fpp = random_matches * 1.0 / trials;
  printf(" fpp %3.5f (estimated) \n", fpp);
  double bpe = binary_fuse16_size_in_bytes(&filter) * 8.0 / size;
  printf(" bits per entry %3.2f\n", bpe);
  printf(" bits per entry %3.2f (theoretical lower bound)\n", - log(fpp)/log(2));
  printf(" efficiency ratio %3.3f \n", bpe /(- log(fpp)/log(2)));
  binary_fuse16_free(&filter);
  free(big_set);
  return true;
}

void failure_rate_binary_fuse16() {
  printf("testing binary fuse16 for failure rate\n");
  // we construct many 5000-long input cases and check the probability of failure.
  size_t size = 5000;
  uint64_t *big_set = (uint64_t *)malloc(sizeof(uint64_t) * size);
  binary_fuse16_t filter;
  binary_fuse16_allocate(size, &filter);
  size_t failure = 0;
  size_t total_trials = 1000000;

  for(size_t trial = 0; trial <= 1000; trial++) {
    for (size_t i = 0; i < size; i++) {
      big_set[i] = rand() + (((uint64_t) rand()) << 32);
    }
    if(!binary_fuse16_populate(big_set, size, &filter)) {
      failure++;
    }
  }
  printf("failures %zu out of %zu\n\n", failure, total_trials);
  free(big_set);
}

int main() {
  failure_rate_binary_fuse16();
  for(size_t size = 1000; size <= 1000000; size *= 300) {
    printf("== size = %zu \n", size);
    if(!testbinaryfuse8(size)) { abort(); }
    printf("\n");
    if(!testbinaryfuse16(size)) { abort(); }
    printf("\n");
    if(!testbinaryfuse8_dup(size)) { abort(); }
    printf("\n");
    if(!testbinaryfuse16_dup(size)) { abort(); }
    printf("\n");
    printf("======\n");
  }
}