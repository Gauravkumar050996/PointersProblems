#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    // malloc: allocates uninitialized memory
    // Returns pointer to allocated memory, NULL if failed
    int* ptr1 = (int*)malloc(5 * sizeof(int));
    printf("malloc: allocated uninitialized memory\n");
    
    // calloc: allocates zero-initialized memory
    // Takes (num_elements, size_per_element)
    // Slower than malloc due to initialization
    int* ptr2 = (int*)calloc(5, sizeof(int));
    //int* ptr3 = (int*)calloc(10, sizeof(int));
    printf("calloc: allocated zero-initialized memory\n");
    
    // realloc: resizes previously allocated memory
    // Can move memory to new location, returns new pointer
    // Preserves existing data up to new size
    int* temp = (int*)realloc(ptr1, 10 * sizeof(int));
    if (temp != NULL) {
        ptr1 = temp; // Update pointer if realloc succeeded
    } else {
        printf("realloc failed\n");
        free(ptr1); // Free original memory if realloc failed
        return 1;
    }
    printf("realloc: resized memory from 5 to 10 elements\n");
    
    // free: deallocates memory
    // Should only be called once per pointer
    // Always set pointer to NULL after freeing to avoid dangling pointer
    free(ptr1);
    ptr1 = NULL;
    
    free(ptr2);
    ptr2 = NULL;
    
    printf("\nKey Differences:\n");
    printf("malloc    - uninitialized, fast, single size parameter\n");
    printf("calloc    - zero-initialized, slower, two size parameters\n");
    printf("realloc   - resizes existing block, may move data, preserves content\n");
    printf("free      - deallocates, must be called for each allocation\n");

    // malloc vs new (in C++, new is preferred)
    // malloc: C-style memory allocation, returns void*, no constructor call
    // new: C++ operator, calls constructors, throws exception on failure, type-safe
    
    // Using malloc (returns void pointer, requires cast)
    int* mallocPtr = (int*)malloc(sizeof(int));
    *mallocPtr = 42;
    printf("\nmalloc allocated int: %d\n", *mallocPtr);
    free(mallocPtr);
    
    // Using new (type-safe, no cast needed, calls constructor)
    int* newPtr = new int(100);
    printf("new allocated int: %d\n", *newPtr);
    delete newPtr;
    
    printf("\nKey Differences (malloc vs new):\n");
    printf("malloc    - C-style, returns void*, no constructor\n");
    printf("new       - C++ operator, type-safe, calls constructor, throws exception\n");
    printf("free      - C-style deallocation for malloc\n");
    printf("delete    - C++ operator deallocation for new\n");
    
    return 0;
}
