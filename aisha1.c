/*
* a basic memory manager that can be tested and validated
* 
*/
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

// Stats
int allocs = 0;
int frees = 0;
int fails = 0;
double avg_time = 0;
size_t max = 0, min = INT_MAX;

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

  // Init
  if (init_manager(2 * 1024 * 1024) != SUCCESS) {
    printf("Failed to initialize memory pool.\n");
    return 1;
  }

  // Test allocations
  void* block1 = alloc_block(512); // Allocate 100 bytes
  if (block1 != NULL) {
	  free_block(block1);
  } else {
    printf("Allocation failed");
  }
  void* block2 = alloc_block(1024); // Allocate 500 bytes
   if (block2 != NULL) {
          free_block(block2);
  } else {
    printf("Allocation failed");
  }

  // Test deallocations
  //free_block(block1);
  //free_block(block2);

  // Print stats
  printf("Pool size: %zu bytes\n", pool_size);
  printf("Allocations: %d\n", allocs);
  printf("Frees: %d\n", frees);
  printf("Fails: %d\n", fails);
  printf("Max Allocation: %zu bytes\n", max);
  printf("Min Allocation: %zu bytes\n", min);
  printf("Average Allocation Time: %.6f seconds\n", avg_time / allocs);

  // Clean up
  //free(pool);

  return 0;
}

