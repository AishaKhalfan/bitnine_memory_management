#include <stdio.h>
#include <stdlib.h>

int main() {

  // Allocate memory for an integer 
  int *ptr = malloc(sizeof(int));

  // Check for allocation failure
  if(!ptr) {
    printf("Error allocating memory\n");
    return 1;
  }

  // Store value at allocated address
  *ptr = 100; 

  printf("Value at allocated address: %d\n", *ptr);

  // Deallocate memory
  free(ptr);

  return 0;
}
