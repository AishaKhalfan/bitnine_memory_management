#include <stdio.h>
#include <stdlib.h>

#define POOL_SIZE 1000 // Memory pool size 

// Block struct to track allocated blocks
struct block {
  size_t size; // Size of block
  int free; // 0 if allocated, 1 if free
  struct block *next;
};

// Global vars
struct block *head = NULL; 
size_t pool_size = POOL_SIZE;

// Initialize memory pool
void init_pool() {
  head = malloc(pool_size);
  head->size = pool_size; 
  head->free = 1;
  head->next = NULL;
}

// First-fit allocation
struct block* alloc_block(size_t size) {
  
  struct block* current = head;
  
  // Find first free block that fits
  while (current != NULL) {
    if (current->free && current->size >= size) {  
      current->free = 0;
      return current;
    }
    current = current->next;
  }
  
  return NULL; // No block found
}

// Free a block 
void free_block(struct block* ptr) {
  ptr->free = 1; 
}

int main() {
  
  // Initialize pool
  init_pool();
  
  // Allocate blocks
  struct block *b1 = alloc_block(500);
  struct block *b2 = alloc_block(300);
  
  /* Print allocated sizes */
  printf("Allocated %zu, %zu bytes\n", b1->size, b2->size); 
  
  // Free blocks
  free_block(b1);
  free_block(b2);

  return 0;
}
