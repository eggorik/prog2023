#include "/home/eggorik_221/prog2023/lab2/IntVector.h"
#include <stdio.h>

void printArr(int arr[], size_t size){
    if (size > 1){
        for(int i = 0;i < size-1;i++){
            printf("%d, ", arr[i]);
        }
        printf("%ld", size-1);
    }
    if (size == 1)
        printf("%d", arr[0]);
    if (size == 0)
        printf("array is empty");
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

    for (int i = 0;i < 10;i++)
    {
        int_vector_push_back(ar, i + 2);
        printf("push_back(%d)\n", i + 1);
        infoPrint(ar);
    }

    return 0;
}