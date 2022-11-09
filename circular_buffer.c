#include <stdio.h>
#include <stdlib.h>
#include "circular_buffer.h"

int circular_buffer_create(struct circular_buffer_t *a, int N) {
    if(a == NULL || N<=0) {
        return 1;
    }
    int *alloc = (int *)malloc(N * sizeof(int));
    if(alloc == NULL) {
        return 2;
    }
    a->ptr = alloc;
    a->begin = 0;
    a->end = 0;
    a->capacity = N;
    a->full = 0;
    return 0;
}

int circular_buffer_create_struct(struct circular_buffer_t **cb, int N) {
    if(cb == NULL || N<=0) {
        return 1;
    }
    *cb = malloc(sizeof(struct circular_buffer_t));
    if(*cb == NULL) {
        return 2;
    }
    int res = circular_buffer_create(*cb,N);
    if(res == 1 || res == 2) {
        free(*cb);
        return 2;
    }
    return 0;
}

void circular_buffer_destroy(struct circular_buffer_t *a) {
    if(a != NULL) {
        free(a->ptr);
    }
}

void circular_buffer_destroy_struct(struct circular_buffer_t **a) {
    if(a!= NULL) {
        circular_buffer_destroy(*a);
        free(*a);
    }
}

int circular_buffer_push_back(struct circular_buffer_t *cb, int value) {
    if(cb == NULL || cb->capacity < 1 || cb->end > cb->capacity || cb->begin < 0 || cb->begin > cb->capacity || cb->end < 0) {
        return 1;
    }
    *(cb->ptr + cb->end) = value;
    if(cb->full == 1) {
        cb->end++;
        cb->begin++;
        if(cb->end == cb->capacity){
            cb->end = 0;
            cb->begin = 0;
        }
    }
    else {
        cb->end++;
    }
    if(cb->end == cb->capacity) {
        cb->end = 0;
    }
    if(cb->end == cb->begin) {
        cb->full = 1;
    }
    return 0;
}

int circular_buffer_pop_front(struct circular_buffer_t *a, int *err_code) {
    if (a == NULL || a->capacity < 1 || a->end > a->capacity || a->begin < 0 || a->begin > a->capacity || a->end < 0) {
        if(err_code != NULL) {
            *err_code = 1;
        }
        return 1;
    }
    if(circular_buffer_empty(a) == 1) {
        if(err_code != NULL) {
            *err_code = 2;
        }
        return 2;
    }
    if(err_code != NULL) {
        *err_code = 0;
    }
    int deleted = *(a->ptr + a->begin);
    a->begin++;
    if(a->begin == a->capacity) {
        a->begin = 0;
    }
    a->full = 0;
    return deleted;
}
int circular_buffer_pop_back(struct circular_buffer_t *a, int *err_code) {
    if(a == NULL || a->capacity < 1 || a->end > a->capacity || a->begin > a->capacity || a->begin < 0 || a->end < 0) {
        if(err_code != NULL) {
            *err_code = 1;
        }
        return 1;
    }
    if(circular_buffer_empty(a) == 1) {
        if(err_code != NULL) {
            *err_code = 2;
        }
        return 2;
    }
    if(err_code != NULL) {
        *err_code = 0;
    }
    a->end--;
    if(a->end < 0) {
        a->end = a->capacity - 1;
    }
    int deleted = *(a->ptr + a->end);
    a->full = 0;
    return deleted;
}

int circular_buffer_empty(const struct circular_buffer_t *a) {
    if(a == NULL || a->capacity < 1 || a->end > a->capacity || a->begin < 0 || a->begin > a->capacity || a->end < 0) {
        return -1;
    }
    if(a->begin == a->end && a->full == 0) {
        return 1;
    }
    return 0;
}

int circular_buffer_full(const struct circular_buffer_t *a) {
    if(a == NULL || a->capacity < 1 || a->end > a->capacity || a->begin < 0 || a->begin > a->capacity || a->end < 0) {
        return -1;
    }
    if(a->begin == a->end && a->full == 1) {
        return 1;
    }
    return 0;
}

void circular_buffer_display(const struct circular_buffer_t *a) {
    if(a == NULL || a->capacity < 1 || a->end > a->capacity || a->begin < 0 || a->begin > a->capacity || a->end < 0) {
        return;
    }
    if(circular_buffer_empty(a) == 1) {
        return;
    }
    int number = a->begin;
    if(circular_buffer_full(a) == 1) {
        printf("%d ",*(a->ptr+number));
        number = (number+1) % a->capacity;
    }
    for(;number!= a->end;number = (number+1) % a->capacity) {
        printf("%d ",*(a->ptr + number));
    }
}

