#include <stdio.h>
#include <stdlib.h>

int main() {

  // Allocating memory
  int *ptr = malloc(10 * sizeof(int));

  // Checking for failure
  if(!ptr) {
    printf("Allocation failed\n");
    return 1;
  }

  // Using allocated memory
  for(int i = 0; i < 10; i++) {
    ptr[i] = i; 
  }

  // Printing the values
  for(int i = 0; i < 10; i++) {
    printf("Value at ptr[%d]: %d\n", i, ptr[i]); 
  }

  // Reallocating to a smaller block
  ptr = realloc(ptr, 5 * sizeof(int));

  // Free the  memory 
  free(ptr);

  return 0;
}
