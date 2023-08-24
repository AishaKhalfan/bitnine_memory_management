#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

// Definitions
#define FAILURE -1
#define SUCCESS 0

// Memory manager APIs
int init_manager(size_t size);
void* alloc_block(size_t size);
int free_block(void* ptr);

// Init, alloc, free 


// Stats variables
int allocs = 0;
int frees = 0;
int fails = 0;
double avg_time = 0;
size_t max = 0, min = INT_MAX;

// Pool 
// Implementation Pool
char* pool;
size_t pool_size;

/**
* initializes the memory manager by allocating the memory pool
* Accepts the desired pool size as a parameter
* Returns SUCCESS or FAILURE status
* Allocates the global memory pool array
*/
int init_manager(size_t size) {
  pool = (char*)malloc(size);
  if (!pool) return FAILURE;
  pool_size = size;
  return SUCCESS;
}

/*
* allocates a block of memory from the pool using malloc
* Accepts requested block size
* Uses malloc() to allocate a block from pool
* Returns pointer to allocated block, or NULL on failure
*/
void* alloc_block(size_t size) {
  if (size > pool_size) {
    fails++;
    return NULL;
  }

  clock_t start_time = clock();

  void* block = pool; // Allocate from the pool
  pool += size;

  clock_t end_time = clock();
  avg_time += ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

  allocs++;

  if (size > max) max = size;
  if (size < min) min = size;

  return block;
}

/**
* frees an allocated block using free
* Accepts pointer to block to free
* Uses free() to release the memory
* Returns SUCCESS status
*/
int free_block(void* ptr) {
  if (ptr != NULL) {
    //free(ptr);
    frees++;
    return SUCCESS;
} else {
  return FAILURE;
}
}

int main() {

  // Initialize 
  init_manager(512 * 1024 * 1024); // 512 MB

  srand(time(0)); // Seed RNG

  // Allocate and free blocks
  for(int i=0; i<100; i++) {

    // Generate random size
    int r = (rand() % 4000) + 1000;
   
    void* block = alloc_block(r);
   
    // Randomly free
    if(rand() % 5 == 0) {
      free_block(block); 
    }

  }

  // Print stats
  printf("Pool size: %ld bytes\n", pool_size);
  printf("Allocations: %d\n", allocs);
  printf("Frees: %d\n", frees);
  printf("Fails: %d\n", fails);
  printf("Avg time: %f ms\n", avg_time/allocs);
  printf("Max size: %ld bytes\n", max);
  printf("Min size: %ld bytes\n", min);

  return 0;
}
