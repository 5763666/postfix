#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100

typedef char element;

typedef struct {
    element stack[MAX_STACK_SIZE];
    int top;
} StackType;

void init_stack(StackType* s) {
    s->top = -1;
}

int is_full(StackType* s) {
    return s->top == MAX_STACK_SIZE - 1;
}

int is_empty(StackType* s) {
    return s->top == -1;
}

void push(StackType* s, element item) {
    if (is_full(s)) {
        return;
    }
    else s->stack[++(s->top)] = item;
}

element pop(StackType* s) {
    if (is_empty(s)) {
        exit(1);
    }
    else return s->stack[(s->top)--];
}

int eval(char exp[]) {
    int op1, op2, value, i = 0;
    int len = strlen(exp);
    char ch;
    StackType s;
    init_stack(&s);

    for (i = 0; i < len; i++) {
        if (is_empty(&s)) {
            fprintf(stderr, "Error: Invalid character\n");
            return 0;
        }

        ch = exp[i];
        if (ch >= '0' && ch <= '9') { // 숫자일 경우
            value = ch - '0';
            push(&s, value);
        }
        else { // 연산자일 경우
            op2 = pop(&s);
            op1 = pop(&s);
            switch (ch) {
            case '+': push(&s, op1 + op2); break;
            case '-': push(&s, op1 - op2); break;
            case '*': push(&s, op1 * op2); break;
            case '/': push(&s, op1 / op2); break;
            }
        }
    }
    return pop(&s);
}

int main(void) {
    int result;
    char exp[MAX_STACK_SIZE];
    printf("Enter an postfix expression: ");
    scanf_s("%s", exp);
    result = eval(exp);
    printf("Result: \n", result);
    return 0;
}
