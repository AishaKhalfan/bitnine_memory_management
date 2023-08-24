/*
* a basic memory manager that can be tested and validated
* 
**/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SUCCESS 0
#define FAILURE 1

// Memory manager APIs  
//
int init_manager(size_t size);

void* alloc_block(size_t size);

int free_block(void* ptr);

// Implementation

char pool[1024*1024*2]; // 2 MB
//char pool[1024*1024*1024]; // 1024 MB
//char pool[1024*1024*1024]; // variable 1024 MB
//char pool[1024*1024*512]; // 512 MB
size_t pool_size;

/**
* initializes the memory manager by allocating the memory pool
* Accepts the desired pool size as a parameter
* Returns SUCCESS or FAILURE status
* Allocates the global memory pool array
*/
int init_manager(size_t size) {
  if(size < sizeof(pool)) {
    pool_size = size;
    return SUCCESS;
  }
  return FAILURE;
}

/*
* allocates a block of memory from the pool using malloc
* Accepts requested block size
* Uses malloc() to allocate a block from pool
* Returns pointer to allocated block, or NULL on failure
*/
void* alloc_block(size_t size) {
  if(size <= pool_size) {
    //void* allocated_block = &pool[sizeof(pool) - pool_size]; // Allocate from the end of the pool
    pool_size -= size; 
    return malloc(size);
    //return allocated_block;
  }
  return NULL; 
}

/**
* frees an allocated block using free
* Accepts pointer to block to free
* Uses free() to release the memory
* Returns SUCCESS status
*/
int free_block(void* ptr) {
  free(ptr);
  return SUCCESS;
}

// Test driver

int main() {

  // Init manager
  init_manager(sizeof(pool));
  
  srand(time(0));

  const int MAX_BLOCKS = 100;
  void* blocks[MAX_BLOCKS];

  int alloc_count = 0;
  int free_count = 0;
  int fails = 0;

  size_t max_size = 0;
  size_t min_size = sizeof(pool);
  double avg_time = 0;

  // Run test 
  for(int i=0; i<MAX_BLOCKS; i++) {

    // Random size 
    size_t size = (rand() % 1024) + 1;

    // Time alloc
    clock_t start = clock();
    blocks[i] = alloc_block(size);
    clock_t end = clock();

    double duration = (double)(end - start) / CLOCKS_PER_SEC; 
    avg_time += duration;

    if(blocks[i] != NULL) {
      alloc_count++;

      // Update stats
      if(size > max_size) max_size = size;
      if(size < min_size) min_size = size;

    } else {
      fails++; 
    }

    // Randomly free some blocks
    if(rand() % 2 == 0) {
      free_block(blocks[i]);
      free_count++;
    }

  }

  // Print stats
  printf("Memory pool size: %zu bytes\n", sizeof(pool));
  printf("Allocations: %d\n", alloc_count);
  printf("Frees: %d\n", free_count);
  printf("Avg alloc time: %.5f sec\n", avg_time/alloc_count); 
  printf("Max size: %zu\n", max_size);
  printf("Min size: %zu\n", min_size);
  printf("Fails: %d\n", fails);

  return 0;
}
