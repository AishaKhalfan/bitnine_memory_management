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
int num_allocations = 0;
int num_deallocations = 0;
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

  num_allocations++;

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
    //frees++;
    num_deallocations++;
    return SUCCESS;
} else {
  return FAILURE;
}
}

int main() {

  // Initialization
  if (init_manager(2 * 1024 * 1024) != SUCCESS) {
    printf("Failed to initialize memory pool.\n");
    return 1;
  }
  // Testing allocations and deallocations

  /*for (int i = 0; i < 409; i++) {
    void* block = alloc_block(5 * 1024); // Allocate 5kb
    if (block != NULL) {
       num_allocations++;
       free_block(block);
       num_deallocations++;
    } else {
      printf("Allocation failed\n");
    }
  //}
  */
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
  printf("Pool size: %zu bytes\n", pool_size);
  printf("allocations: %d\n", num_allocations);
  printf("Deallocations: %d\n", num_deallocations);
  printf("Fails: %d\n", fails);
  printf("Max Allocation: %zu bytes\n", max);
  printf("Min Allocation: %zu bytes\n", min);
  printf("Average Allocation Time: %.6f seconds\n", avg_time / num_allocations);

  // Clean up
  //free(pool);

  return 0;
}

