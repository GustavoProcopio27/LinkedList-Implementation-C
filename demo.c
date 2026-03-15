#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "LinkedList.h"

void print_list_float(void* v){
    float num = *(float*) v;
    printf("valor: %f\n", num);
}
void print_list_int(void *v)
{
    int num = *(int *)v;
    printf("valor alterado: %d\n", num);
}
void* parse_int_cubic(void* v){
    static int val;
    float num = *(float*) v;
    val = (int) num;
    val = val * val * val;
    return &val;
}

int main()
{
    float teste1 = 3.4f, teste2 = 6.8f;
    LinkedList* list = linkedlist_init(float); 
    // devido ao alterar os indices ao inserir na 1 posicao, os indices ficam:
    linkedlist_addFirst(list, teste1, float); //fica index:2
    linkedlist_addFirst(list, 5.5f, float);   //fica index:1
    linkedlist_addFirst(list, teste2, float); //fica index:0
    linkedlist_addLast(list, 25.29f, float); //fica index:3

    linked_list_foreach(list, print_list_float);

    bool exists = linkedlist_contains(list,25.29f, float);
    printf("\n25.29 esta na lista ? %s\n\n", exists ? "sim\n" : "não\n" );

    linkedlist_removeLast(list);
    linkedlist_setAtIndex(list, 11.0f, 1, float);
    linked_list_foreach(list, print_list_float);

    LinkedList *list1 = linkedlist_map(list, parse_int_cubic, int);
    linked_list_foreach(list1, print_list_int);

    linkedlist_free(list);
    linkedlist_free(list1);

}