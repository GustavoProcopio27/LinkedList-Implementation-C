# LinkedList (C)

Uma pequena biblioteca em C puro que implementa uma lista ligada genérica (Linked List) capaz de armazenar qualquer tipo de dado.



## ✨ Características

* Estrutura dinâmica baseada em lista encadeada

* Armazena qualquer tipo de dado

* Interface simples usando macros tipadas

* Suporte a operações comuns de lista

* Suporte a foreach

* Suporte a map funcional

* Apenas dependência da stdlib do C

## 🚀 Como compilar
```sh
gcc demo.c linkedlist.c -o demo
./demo
```

Ou inclua no seu projeto:
```sh
linkedlist.c
linkedlist.h
```


## 📦 Estrutura da LinkedList

```C
typedef struct Node{
    void* value;
    struct Node* next;
    size_t index;
} Node;
```

|       Campo        |              Descrição                 |
| ------------------ | -------------------------------------- |
|     ```value```    | ponteiro para o valor armazenado no nó |
|     ```next```     |      ponteiro para o proximo nó        |
|     ```index```    | indice da posição atual do valor nó    |

```C

typedef struct LinkedList{
    Node* head;
    size_t length;
    size_t element_size;
} LinkedList;
```
|         Campo	     |          Descrição         |
| ------------------ | -------------------------- | 
|    ```head```	     |    primeiro nó da lista    |
|   ```length```	 |    número de elementos     |
| ```element_size``` | tamanho do tipo armazenado |

## </> API

A biblioteca usa macros para tipagem e funções internas que trabalham com void*.

### Inicialização
```LinkedList* linkedlist_init(type);```
Cria uma nova LinkedList capaz de armazenar elementos do tipo especificado.
Exemplo:
```C
LinkedList* list = linkedlist_init(int);
```
Internamente chama:
```C
_linkedlist_init(sizeof(type))
```

---


### Adicionar Elementos
* Adicionar no início
  
```void linkedlist_addFirst(list, value, type);```

Exemplo:

```C
linkedlist_addFirst(list, 10, int);
```

Funcionamento:

1. A macro cria uma variável temporária do tipo especificado

2. Passa o endereço dessa variável para _linkedlist_addFirst

3. O valor é copiado para um novo nó
   
---

* Adicionar no final
  
```void linkedlist_addLast(list, value, type);```

Adiciona um elemento ao final da lista.

Exemplo:
```C
linkedlist_addLast(list, 30, int);
```
---

* Inserir em índice especifico
  

```void linkedlist_addAtIndex(list, value, index, type);```
Insere um elemento na posição especificada da lista.

Os elementos posteriores são deslocados.

Exemplo:
```C
linkedlist_addAtIndex(list, 50, 2, int);
```

---


### Obter elementos
* Primeiro elemento
  
```type linkedlist_getFirst(list, type);```

Retorna o valor armazenado no primeiro nó da lista.

Exemplo:
```C
int value = linkedlist_getFirst(list, int);
```

---

* Último elemento

```type linkedlist_getLast(list, type);```

Retorna o valor armazenado no último nó da lista.
Exemplo:

```C
int value = linkedlist_getLast(list, int);
```




---
* Elemento por índice


```type linkedlist_getAtIndex(list, index, type); ```
Retorna um elemento na posição especificada
Exemplo:
```C
int value = linkedlist_getAtIndex(list, 3, int);
```


---

### Modificar elemento

```void linkedlist_setAtIndex(list, value, index, type);```


Exemplo:
```C
linkedlist_setAtIndex(list, 50, 1, int);
```

---

### Remover elementos
* Remover primeiro
  
```void linkedlist_removeFirst(list);```
Remove o primeiro elemento da lista.
Exemplo:
```C
linkedlist_removeFirst(list);
``` 
---
* Remover último
  
```void linkedlist_removeLast(list);```
Remove o ultimo elemento da lista.
Exemplo:
```C
linkedlist_removeLast(list);
```
* Remover índice específico

```void linkedlist_removeAtIndex(list, index);```
Remove o elemento presente no índice especificado.
Exemplo:
```C
linkedlist_removeAtIndex(list, 2);
```
---

### Verificar se elemento existe
```bool linkedlist_contains(list, value, type);```
Verifica se um valor está presente na lista, retornando ```true```*(stdbool.h)* se ele existir.
Exemplo:
```C
bool exists = linkedlist_contains(list, 10, int);
```

---


### Iterar sobre a lista
```linked_list_foreach(list, print_function);```
Executa uma função para cada elemento da lista.
Exemplo:
```C
void print_int(void* value)
{
    printf("%d\n", *(int*)value);
}

linked_list_foreach(list, print_int);
```

---

### Map

Aplica uma função a todos os elementos e retorna uma nova lista.

```LinkedList* new_list = linkedlist_map(list, func, type);```

Exemplo:
```C
void* double_value(void* v)
{
    static int result;
    result = (*(int*)v) * 2;
    return &result;
}
LinkedList* doubled = linkedlist_map(list, double_value, int);
```

### Limpar lista
```linkedlist_clear(list);```

Remove todos os nós da lista, reiniciando sua estrutura *(linkedlist->head = NULL).*

### Liberar memória
```linkedlist_free(list);```


Libera:

1. Todos os nós
2. Os valores armazenados
2. A estrutura da lista