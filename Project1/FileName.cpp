#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define _CRT_SECURE_NO_WARNINGS
   
typedef char element;

typedef struct StackType { element stack;    struct StackType* link; } StackType;

StackType* top;

int is_empty() { if (top == NULL) return 1;   else return 0; }

void topMakeNull() {
    StackType* tmp;
    while (top != NULL) { tmp = top;  top = top->link;     free(tmp); }
}

void push(element item) {
    StackType* tmp = (StackType*)malloc(sizeof(StackType));
    tmp->stack = item;     tmp->link = top;  top = tmp;
}

element pop() {
    element item;     StackType* tmp = top;
    if (top == NULL) { return 0; }
    else { item = tmp->stack;   top = tmp->link;    free(tmp);  return item; }
}


//error for invalid char  문자열 -> 에러
int errorchar(char* exp) {
    char input_str[100];
    char fchar, lchar;

    fchar = input_str[0];
    lchar = input_str[strlen(input_str) - 1];

    if (fchar == '+' || fchar == '-' || fchar == '*' || fchar == '/' || lchar == '+' || lchar == '-' || lchar == '*' || lchar == '/')
        return 1;
    else return 0;
};

//error for invalid expression  연산자가 끝이나 마지막일 경우 에러
int errorexprs(char* exp) {
    char inputs = 0;
    if (!isalpha(inputs))
        return 1;
    else return 0;
};


//error message for 괄호
int errorparen(char* exp) {
    topMakeNull();    char symbol, open_pair;
    int i, length = strlen(exp);    top = NULL;

    for (i = 0; i < length; i++) {
        symbol = exp[i];
        switch (symbol) {
        case '(':
        case '[':
        case '{':
            push(symbol); break;

        case ')':
        case ']':
        case '}':
            if (top == NULL) return 0;
            else {
                open_pair = pop();
                if ((open_pair == '(' && symbol != ')') ||
                    (open_pair == '[' && symbol != ']') ||
                    (open_pair == '{' && symbol != '}'))
                    return 0;
                else break;
            }
        }
    }
    if (top == NULL) return 1;
    else return 0;
}

// infix to postfix
char* postfix(char* exp) {
    topMakeNull();  char symbol;    int length = strlen(exp), count = 0;
    char* changeValue = (char*)malloc(sizeof(char) * length);
    memset(changeValue, '\0', length);

    for (int i = 0; i < length; i++) {
        symbol = exp[i];
        if ('0' <= symbol && symbol <= '9') { changeValue[count++] = symbol;    continue; }
        switch (symbol) {
        case '+':
        case '-':
        case '*':
        case '/':
            push(symbol); break;
        case ')':
        case '}':
        case ']':
            changeValue[count++] = pop();
            break;
        }
    }
    return changeValue;
}


//postfix cal
element cal(char* exp) {
    topMakeNull();    int opr1, opr2, value, i = 0;

    int length = strlen(exp);    char symbol;    top = NULL;

    for (i = 0; i < length; i++) {
        symbol = exp[i];
        if (symbol >= '0' && symbol <= '9') { value = symbol - '0';       push(value); }
        else {
            opr2 = pop();
            opr1 = pop();

            switch (symbol) {
            case '+': push(opr1 + opr2); break;
            case '-': push(opr1 - opr2); break;
            case '*': push(opr1 * opr2); break;
            case '/': push(opr1 / opr2); break;
            }
        }
    }
    return pop();
}


int main(void) {
    char* exp;
    char express[100];
    int result;

    printf("Enter an infix expression: ");
    gets_s(express, 100); //수식 입력 받음

    //error for invalid char
    if (errorchar(express) == 1)
        printf("\nError: Invalid character");

    //error for invalid expression
    if (errorexprs(express) == 1)
        printf("\nError: Invalid expression");

    //error for paren
    if (errorparen(express) == 1)
        printf("\nError: Mismatched parentheses");
   

    // infix to postfix
    exp = postfix(express);
    printf("\nPostfix expression: %s", exp);


    // postfix cal
    result = cal(exp);
    printf("\nResult: %d", result);

    return 0;
}