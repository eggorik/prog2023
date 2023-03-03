#include "IntVector.h"
#include <stdio.h>
#include <stdlib.h>

IntVector *int_vector_new(size_t initial_capacity){
	IntVector *p = NULL;
	p = malloc(sizeof(IntVector));
	if (!p)
		return NULL;
	p -> data = malloc(initial_capacity * sizeof(int));
	if (!(p->data)){
		return NULL;
	}
	p -> size = 0;
	p -> capacity = initial_capacity;
	
	return p;
}

IntVector *int_vector_copy(const IntVector *v){
	if (v == NULL)
		return NULL;
	IntVector *copied = NULL;
	copied = int_vector_new(v->capacity);
	for (int i = 0; i < v -> size; i++)
		(copied -> data)[i] = (v -> data)[i];
	copied -> capacity = v -> capacity;
	copied -> size = v ->  size;
	
	return copied;
}

void int_vector_free(IntVector *v){
	free(v->data);
	free(v);
}

int int_vector_get_item(const IntVector *v, size_t index){
	if (index >= v -> size){
		printf("Error");
		exit(1);
	}
	return v -> data[index];
}

void int_vector_set_item(IntVector *v, size_t index, int item){
	if (index >= v -> size){
		printf("Error");
		exit(1);
	}
	v->data[index] = item;
}

size_t int_vector_get_capacity(const IntVector *v){
	return v -> capacity;
}

size_t int_vector_get_size(const IntVector *v){
	return v -> size;
}

int int_vector_push_back(IntVector *v, int item){
	if (v -> size == v -> capacity){
		int *a = NULL;
		a = realloc(v -> data, sizeof(int) * (v -> capacity *2 ));
		if (v -> data == NULL)
			return -1;
		v -> data = a;
		v -> capacity *= 2;
	}
	v->data[++(v->size)] = item;
	return 0;
}

void int_vector_pop_back(IntVector *v){
	if (v -> size != 0)
		v -> size--;
}

int int_vector_shrink_to_fit(IntVector *v){
	int *a = realloc(v -> data, sizeof(int) * (v-> size));
	if (a == NULL)
		return -1;
	v -> capacity = v -> size;
	v -> data = a;
	return 0;
}

int int_vector_resize(IntVector *v, size_t new_size){
	if (new_size > v -> size){
		if (new_size > v-> capacity){
			int *a = realloc(v -> data, sizeof(int) * (new_size));
			if (a == NULL)
				return -1;
			v -> data = a;
			for (int i = v -> size; i < new_size; i++)
				v -> data[i] = 0;
			v -> size = new_size;
			v -> capacity = new_size;
		}
		else {
			for (int i = v -> size; i < new_size; i++)
					v -> data[i] = 0;
		}
	}
	else {
		v -> size = new_size;
	}		
	return 0;
}

int int_vector_reserve(IntVector *v, size_t new_capacity){
	if (new_capacity > v-> capacity){
		int *a = realloc(v -> data, sizeof(int) * (new_capacity));
		if (a == NULL)
			return -1;
		v -> data = a;
		v -> capacity = new_capacity;
	}
	return 0;
}
