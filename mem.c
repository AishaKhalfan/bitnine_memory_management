#include <stdio.h>
#include <stdlib.h>

// Config params
size_t pool_size;
size_t block_size; 

// APIs
int init_manager(size_t size);
void* alloc_block(size_t size);
int free_block(void* ptr);

// Track remaining space  
size_t total_space;

// Pool pointer
char* pool;

int init_manager(size_t size) {
  total_space = size;
  pool = malloc(size);
  return 0;
}

void* alloc_block(size_t size) {
  if(size <= total_space) {
    total_space -= size;
    return malloc(size); 
  } 
  return NULL;
}

int free_block(void* ptr) {
  free(ptr); 
  return 0;
}

int main() {

  // Init with size
  init_manager(1024);
  
  // Allocate blocks
  void* b1 = alloc_block(500);
  void* b2 = alloc_block(200);

  return 0;
}
