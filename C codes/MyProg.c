
#include <stdlib.h>
#include <stdio.h>

typedef struct _doubleNode {
 double value;
 struct _doubleNode* link;
} doubleNode;

void printList(doubleNode *node) {

 if (node != NULL) {
 printf("%f ", node->value);
 printList(node->link);
 }
}

void freeAll(doubleNode *node) {

 if (node != NULL) {
 freeAll(node->link);
 printf("Freeing up %f \n", node->value);
 free(node);
 }
}

int main(void) {

 setvbuf(stdout, NULL, _IONBF, 0);

 doubleNode *first = NULL;
 doubleNode *prev = NULL;

 do {
 printf("Enter in a double:");
 double x;
 scanf("%lf", &x);

 if (x < 0.0) {
 break;
 }

 doubleNode *newNode = malloc(sizeof(doubleNode));

 newNode->value = x;
 newNode->link = NULL;

 if (first == NULL) {
 first = newNode;
 } else {
 prev->link = newNode;
 }

 prev = newNode;

 } while (1);

 printList(first);

 printf("Done.");

 freeAll(first);

 return 0;
}


