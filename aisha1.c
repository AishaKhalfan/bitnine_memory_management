#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SUCCESS 0
#define FAILURE 1

// APIs

int init_manager(size_t size);
void* alloc_block(size_t size); 
int free_block(void* ptr);

// Global pool
char* pool;

// Track stats
int allocs = 0;
int frees = 0; 
int fails = 0;
double avg_time = 0;
size_t max = 0;
size_t min = INT_MAX;

// Implement APIs

int init_manager(size_t size) {
  pool = malloc(size);
  if(!pool) return FAILURE;
  return SUCCESS;
}

void* alloc_block(size_t size) {
  
  if(size > max) max = size;
  if(size < min) min = size;
  
  void* block = malloc(size);
  if(!block) {
    fails++;
    return NULL;
  }

  allocs++;
  return block;

}

int free_block(void* ptr) {
  free(ptr);
  frees++;
  return SUCCESS;
}


// Test driver

int main() {

  size_t pool_size = 1024 * 1024 * 512; // 512 MB

  if(init_manager(pool_size) == FAILURE) {
    return -1;
  }

  // Allocate and free random blocks

  // ...

  // Print stats
  printf("Pool size: %zu bytes\n", pool_size);
  printf("Allocs: %d\n", allocs);
  printf("Frees: %d\n", frees);
  printf("Fails: %d\n", fails);
  printf("Avg time: %f\n", avg_time/allocs);
  printf("Max size: %zu\n", max);
  printf("Min size: %zu\n", min);

  return 0;
}
