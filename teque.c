#include <stdio.h>
#include <stdlib.h>

struct teque {
    int size;
    int* teq;
    int front;
    int back;
    int size_f;
    int size_b;
};

int check_balance(struct teque* t) {
    // Checks if the midpoint of the teque is in the correct spot,
    // and corrects it if not.

    if (t->size_f > t->size_b + 1) {
        // Teque is front-heavy

        t->teq[t->back - (t->size_b + 1)] = t->teq[t->front + t->size_f];
        t->size_f -= 1;
        t->size_b += 1;

    } else if (t->size_b > t->size_f) {
        // Teque is back-heavy

        t->teq[t->front + t->size_f + 1] = t->teq[t->back - t->size_b];
        t->size_b -= 1;
        t->size_f += 1;
    }

    return 0;
}

int get(struct teque* t, int i) {
    // Fetches and prints the element at index i in the teque

    int output;

    if (i < t->size_f) {
        output = t->teq[t->front + i + 1];
    } else {
        output = t->teq[(t->back - t->size_b) + (i - t->size_f)];
    }

    printf("%d\n", output);

    return 0;
}

int push_front(struct teque* t, int x) {
    // Pushes the element 'x' to the start of the teque

    t->teq[t->front] = x;
    t->size_f += 1;
    t->front -= 1;

    check_balance(t);

    return 0;
}

int push_back(struct teque* t, int x) {
    // Pushes the element 'x' to the back of the teque

    if (t->size_f == 0) {
        push_front(t, x);

    } else {
        t->teq[t->back] = x;
        t->size_b += 1;
        t->back += 1;

        check_balance(t);
    }

    return 0;
}

int push_middle(struct teque* t, int x) {
    // Pushes the element 'x' to the middle of the teque

    if (t->size_f == 0) {
        push_front(t, x);

    } else if (t->size_b == 0) {
        push_back(t, x);

    } else if (t->size_f == t->size_b) {
        // Pushes the element 'x' to the back of the front of the teque
        t->teq[t->front + t->size_f + 1] = x;
        t->size_f += 1;

    } else{
        // Pushes the element 'x' to the front of the back of the teque
        t->teq[t->back - (t->size_b + 1)] = x;
        t->size_b += 1;
    }

    check_balance(t);

    return 0;
}

int main() {

    // Fetching teque size from stdin:
    char* line = NULL;
    size_t lLen = 0;
    ssize_t lSize = 0;
    lSize = getline(&line, &lLen, stdin);


    // Initializing the teque:
    struct teque queue;
    queue.size = atoi(line);
    queue.teq = (int*)malloc(queue.size * 3 * sizeof(int));
    queue.front = queue.size;
    queue.back = queue.size * 2;
    queue.size_f = 0;
    queue.size_b = 0;

    // Fetching operations from stdin:
    for (int i = 0; i < queue.size; i++) {
        lSize = getline(&line, &lLen, stdin);

        if (line[3] == ' ') {
            get(&queue, atoi(line + 4));
            continue;
        } else if (line[5] == 'f') {
            push_front(&queue, atoi(line + 11));
        } else if (line[5] == 'b') {
            push_back(&queue, atoi(line + 10));
        } else if (line[5] == 'm') {
            push_middle(&queue, atoi(line + 12));
        }
    }

    free(line);
    free(queue.teq);

    return 0;
}