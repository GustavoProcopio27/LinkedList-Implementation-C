#include "LinkedList.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

LinkedList* _linkedlist_init(size_t element_size)
{
    LinkedList *ptr = (LinkedList *)malloc(sizeof(LinkedList));
    if (ptr == NULL) exit(1);

    ptr->element_size = element_size;
    ptr->head = NULL;
    ptr->length = 0;

    return ptr;
}



void _linkedlist_addFirst(LinkedList *linked_list, void *value)
{
    if (linked_list == NULL) exit(1);

    Node *current = linked_list->head;

    while (current != NULL) // percorre tudo aumentando o index
    {
        current->index += 1;
        current = current->next;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) exit(1);

    new_node->value = malloc(linked_list->element_size);
    memcpy(new_node->value, value, linked_list->element_size);
    new_node->index=0;
    new_node->next = linked_list->head;

    linked_list->head = new_node;
    linked_list->length += 1;
}

void _linkedlist_addLast(LinkedList *linked_list, void *value)
{
    if (linked_list == NULL) exit(1);
    Node* current = linked_list->head;
    Node* prev = NULL;
    while (current != NULL)
    {
        prev = current;

        current = current->next;
    }

    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) exit(1);

    new_node->index = linked_list->length;
    new_node->value = malloc(linked_list->element_size);
    new_node->next = current;



    memcpy(new_node->value, value, linked_list->element_size);
    if(prev==NULL) 
        linked_list->head = new_node;
    else
        prev->next = new_node;

    linked_list->length+=1;
    
}

void _linkedlist_addAtIndex(LinkedList* linked_list, void *value, size_t index)
{
    if(linked_list==NULL) exit(1);

    Node *current = linked_list->head;
    Node *prev = NULL;
    bool new_node_was_added = false;
    if (index == 0)
    {
        _linkedlist_addFirst(linked_list, value);
        return;
    }

    while (current != NULL)
    {
        if (current->index == index)
        {
            Node* new_node = malloc(sizeof(Node));
            new_node->index=index;
            new_node->value=malloc(linked_list->element_size);
            memcpy(new_node->value,value,linked_list->element_size);
            new_node->next=current;


            prev->next=new_node;

            new_node_was_added=true;
        }
        if(current->index>index){
            current->index+=1;
        }

        current = current->next;
        prev=current;
    }

    // aqui current é NULL e logo o ultimo elemento

    if(!new_node_was_added){
        current->value = malloc(linked_list->element_size);
        if (current->value == NULL) exit(1);

        memcpy(current->value, value, linked_list->element_size);

        current->next = NULL;

        current->index = linked_list->length;
    }
    linked_list->length+=1;

}

void _linkedlist_setAtIndex(LinkedList* linked_list, void *value, size_t index)
{
    if(linked_list==NULL) exit(1);

    Node *current = linked_list->head;
    while (current != NULL)
    {
        if (current->index == index)
        {
            memcpy(current->value, value, linked_list->element_size);
            break;
        }
        current = current->next;
    }
}

void* _linkedlist_getFirst(LinkedList* linked_list)
{
    if(linked_list==NULL) exit(1);

    return linked_list->head->value;
}
void* _linkedlist_getAtIndex(LinkedList* linked_list, size_t index)
{
    if(linked_list==NULL) exit(1);

    Node* current = linked_list->head;
    while(current!=NULL){
        if(current->index==index){
            return current->value;
        }
        current=current->next;
    }
    return NULL;

}
void* _linkedlist_getLast(LinkedList* linked_list)
{
    if(linked_list==NULL) exit(1);
    Node *current = linked_list->head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    return current->value;
}

void linkedlist_removeFirst(LinkedList *linked_list)
{
    if(linked_list==NULL) exit(1);
    free(linked_list->head->value);
    linked_list->head=linked_list->head->next;
    Node* current=linked_list->head;
    while(current!=NULL)
    {
        current->index-=1;
        current=current->next;
    }
}

void linkedlist_removeLast(LinkedList *linked_list)
{
    if(linked_list==NULL) exit(1);
    Node* current = linked_list->head;
    Node* prev = NULL;
    while (current->next != NULL)
    {
        prev=current;
        current = current->next;
    }
    //Aqui current é o ultimo com valor presente antes do NULL e prev o penultimo antes do NULL
    prev->next = current->next; // prev->next vai ser NULL
    free(current->value);
    free(current);

}

void linkedlist_removeAtIndex(LinkedList *linked_list, size_t index)
{
    if(linked_list==NULL) exit(1);
    Node *current = linked_list->head;
    Node *prev = NULL;
    Node* removed_position = NULL;
    while (current!= NULL)
    {
        if(current->index==index)
        {
            prev->next = current->next;
            free(current->value);
            removed_position=current;
        }
        if(current->index>index)
        {
            current->index-=1; //Muda os indices dos elementos apos o index
        }
        prev = current;
        current = current->next;
    }
    free(removed_position);
}

bool _linkedlist_contains(LinkedList* linked_list,void* value)
{
    if(linked_list==NULL) exit(1);
    Node *current = linked_list->head;
    while (current != NULL)
    {
        if(memcmp(current->value,value,linked_list->element_size)==0)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

void linkedlist_clear(LinkedList* linked_list)
{
    if(linked_list==NULL) exit(1);
    Node* current = linked_list->head;
    while(current!=NULL)
    {
        Node* next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
    linked_list->head=NULL;
}

void linkedlist_free(LinkedList* linked_list)
{
    linkedlist_clear(linked_list);
    free(linked_list);
}