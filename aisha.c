#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Memory manager APIs 

int init_manager(size_t size);
void* alloc_block(size_t size);
int free_block(void* ptr);

// Pool
char pool[1024*1024*512]; 

size_t pool_size;

int init_manager(size_t size) {
  pool_size = size;
  return 0; 
}

void* alloc_block(size_t size) {
  
  void* block = malloc(size);
  if(block != NULL) {
    pool_size -= size;
    return block;
  }

  return NULL;

}

int free_block(void* ptr) {
  free(ptr);
  return 0;
}

// Test driver

int main() {

  init_manager(sizeof(pool));

  srand(time(0));

  void* blocks[100];

  int alloc_count = 0;
  int free_count = 0;
  int fails = 0;

  size_t max_size = 0;
  size_t min_size = sizeof(pool);
  
  for(int i=0; i<100; i++) {

    size_t size = (rand() % 1024) + 1;
    
    blocks[i] = alloc_block(size);

    if(blocks[i] != NULL) {
      alloc_count++;
      if(size > max_size) {
        max_size = size; 
      }

    } else {
      fails++;
    }

    if(rand() % 2 == 0) {
      free_block(blocks[i]);
      free_count++;
    }
  }

  // Print metrics
  printf("Memory pool:%ld\n", pool_size );
  printf("Allocs: %d\n", alloc_count);
  printf("Frees: %d\n", free_count);
  printf("Fails: %d\n", fails);
  printf("Max size: %zu\n", max_size);

  return 0;
}
