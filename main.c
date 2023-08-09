#include <stdio.h>
#include "circular_buffer.h"

int main() {
    int size = 0;
    printf("Podaj rozmiar bufora:");
    /* getting input from user and incorrect input handling */
    if (scanf("%d", &size) == 0) {
        printf("Incorrect input");
        return 1;
    }
    if (size <= 0) {
        printf("Incorrect input data");
        return 2;
    }
    struct circular_buffer_t *pointer;
    struct circular_buffer_t **double_pointer = &pointer;
    int kod;
    int *error_code = &kod;
    /* handling failed memory allocation */
    if(circular_buffer_create_struct(double_pointer, size) == 2) {
        printf("Failed to allocate memory");
        return 8;
    }
    int decision,number;
    do {
        printf("Co chcesz zrobic?");
        /* getting input from user and incorrect input handling */
        if (scanf("%d",&decision) == 0) {
            printf("Incorrect input");
            circular_buffer_destroy_struct(double_pointer);
            return 1;
        }
        if (decision < 0 || decision > 6) {
            printf("Incorrect input data\n");
            continue;
        }
        /* pushing back value to buffer */
        if (decision == 1) {
            printf("Podaj liczbe");
            /* getting input from user and incorrect input handling */
            if (scanf("%d",&number) == 0) {
                printf("Incorrect input");
                circular_buffer_destroy_struct(double_pointer);
                return 1;
            }
            circular_buffer_push_back(pointer,number);
        }
        /* poping back value of buffer */
        if (decision == 2) {
            /* communicating user, that there is nothing to pop */
            if (circular_buffer_empty(pointer) == 1) {
                printf("Buffer is empty\n");
                continue;
            }
            int res_1 = circular_buffer_pop_back(pointer,error_code);
            printf("%d\n",res_1);
        }
        /* poping front value of buffer */
        if (decision == 3) {
            /* communicating user, that there is nothing to pop */
            if (circular_buffer_empty(pointer) == 1) {
                printf("Buffer is empty\n");
                continue;
            }
            int res_2 = circular_buffer_pop_front(pointer,error_code);
            printf("%d\n",res_2);
        }
        /* displaying buffer contents */
        if (decision == 4) {
            /* communicating user, that there is nothing to display */
            if (circular_buffer_empty(pointer) == 1) {
                printf("Buffer is empty\n");
                continue;
            }
            circular_buffer_display(pointer);
            printf("\n");
        }
        /* checking if buffer is empty*/
        if (decision == 5) {
            int res_3 = circular_buffer_empty(pointer);
            if (res_3 == 1) {
                printf("1\n");
            }
            else {
                printf("0\n");
            }
        }
        /* checking if buffer is full*/
        if (decision == 6) {
            int res_4 = circular_buffer_full(pointer);
            if (res_4 == 1) {
                printf("1\n");
            }
            else {
                printf("0\n");
            }
        }
    } while (decision != 0);
    /* memory deallocation */
    circular_buffer_destroy_struct(double_pointer);
    return 0;
}
