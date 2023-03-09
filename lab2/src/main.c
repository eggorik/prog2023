#include "IntVector.h"
#include <stdio.h>

void printArr(int array[], size_t size) {
  if (size == 0) {
    printf("Array is empty");
    return;
  }
  if (size == 1) {
    printf("%d\n", array[0]);
    return;
  }
  printf("%d, ", array[0]);
  for (int i = 1; i < size - 1; i++) {
    printf("%d, ", array[i]);
  }
  printf("%d\n", array[size - 1]);
}

void infoPrint(IntVector* v){
    size_t capacity = int_vector_get_capacity(v);
    size_t size = int_vector_get_size(v);
    printf("capacity = %ld, size = %ld\n", capacity, size);
    printf("array: ");
    printArr(v->data, v->size);
    printf("\n");
}

int main()
{
    IntVector* ar = int_vector_new(5);

    for (int i = 0; i < 11; i++) {
        int_vector_push_back(ar, i + 1);
        printf("push_back(%d)\n", i + 1);
        infoPrint(ar);
        printf("\n");
    }
    printf("\n");
    int_vector_set_item(ar, 7, 121);
    printf("After set_item(item = 121)\n");
    infoPrint(ar);
    printf("\n");

    int res = int_vector_get_item(ar, 7);
    printf("After get_item(item = 7)\nar[7] = %d\n", res);
    printf("\n");

    int_vector_pop_back(ar);
    printf("After pop_back\n");
    infoPrint(ar);
    printf("\n");

    int_vector_shrink_to_fit(ar);
    printf("After shrink_to_fit\n");
    infoPrint(ar);
    printf("\n");

    int_vector_resize(ar, 3);
    printf("After resize(new_size = 3)\n");
    infoPrint(ar);
    printf("\n");

    int_vector_resize(ar, 8);
    printf("After resize(new_size = 8)\n");
    infoPrint(ar);
    printf("\n");

    int_vector_reserve(ar, 6);
    printf("After reverse(new_capacity = 6)\n");
    infoPrint(ar);
    printf("\n");

    int_vector_reserve(ar, 12);
    printf("After reverse(new_capacity = 12)\n");
    infoPrint(ar);
    printf("\n");

    IntVector* copy = int_vector_copy(ar);
    infoPrint(copy);
    printf("\n");

    printf("After resize (new_size = 0)\n");
    int_vector_resize(ar, 0);
    infoPrint(ar);
    printf("\n");

    int_vector_free(ar);
    int_vector_free(copy);
    return 0;
}