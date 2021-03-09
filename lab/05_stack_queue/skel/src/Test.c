#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"
#include "Stack.h"

int main() {
    struct Queue *q = malloc(sizeof(struct Queue));
    struct Stack *st = malloc(sizeof(struct Stack));
    int numbers[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int crt_val;

    printf("-------------------------------- Test stack --------------------------------\n");
    init_stack(st);
    push_stack(st, &numbers[10]);

    /* Test push & size */
    printf("#1:\nOutput: size: %d\nOutput asteptat: size: 1\n", get_size_stack(st));

    /* Test peek */
    crt_val = *(int *)peek_stack(st);
    printf("#2:\nOutput: %d\nOutput asteptat: 10\n", crt_val);

    /* Test pop */
    crt_val = *(int *)peek_stack(st);
    pop_stack(st);
    printf("#3:\nOutput: value: %d size: %d\nOutput asteptat: value: 10 size: 0\n", crt_val, get_size_stack(st));

    push_stack(st, &numbers[9]);
    push_stack(st, &numbers[8]);
    push_stack(st, &numbers[7]);

    /* Test multiple pushes */
    printf("#4:\nOutput: size: %d top elem: %d\nOutput asteptat: size: 3 top elem: 7\n", get_size_stack(st), *(int *)peek_stack(st));

    /* Test multiple pops */
    printf("#5:\nOutput: ");
    while (!is_empty_stack(st)) {
        printf("%d ", *(int *)peek_stack(st));
        pop_stack(st);
    }
    printf("size: %d", get_size_stack(st));
    printf("\nOutput asteptat: 7 8 9 size: 0\n");

    purge_stack(st);
    free(st);

    printf("\n\n-------------------------------- Test queue --------------------------------\n");
    init_q(q);
    enqueue(q, &numbers[5]);

    /* Test enqueue & size */
    printf("#1:\nOutput: size: %d\nOutput asteptat: size: 1\n", get_size_q(q));

    /* Test front */
    crt_val = *(int *)front(q);
    printf("#2:\nOutput: %d\nOutput asteptat: 5\n", crt_val);

    /* Test dequeue */
    crt_val = *(int *)front(q);
    dequeue(q);
    printf("#3:\nOutput: value: %d size: %d\nOutput asteptat: value: 5 size: 0\n", crt_val, get_size_q(q));

    enqueue(q, &numbers[2]);
    enqueue(q, &numbers[3]);
    enqueue(q, &numbers[4]);

    /* Test multiple pushes */
    printf("#4:\nOutput: size: %d top elem: %d\nOutput asteptat: size: 3 front elem: 2\n", get_size_q(q), *(int *)front(q));

    /* Test multiple pops */
    printf("#5:\nOutput: ");
    while (!is_empty_q(q)) {
        printf("%d ", *(int *)front(q));
        dequeue(q);
    }
    printf("size: %d", get_size_q(q));
    printf("\nOutput asteptat: 2 3 4 size: 0\n");

    purge_q(q);
    free(q);
    return 0;
}