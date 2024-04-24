#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

//LISTA, pilha e fila
//Torre de Hanoi com pilha
//Lista circular: o ultimo elemento aponta para o primeiro
//Lista duplamente encadeada: todo nó aponta para o anterior e para o próximo (buble sort)

//LISTA DUPLAMENTE ENCADEADA:

typedef struct Node
{
    int iPayload;
    Node* ptrNext;
    Node* ptrPrev;
} Node;

Node* createNode(int);
void insertFront(Node**, int);
void insertEnd(Node**, int);
void insertAfter(Node*, int);
void deleteNode(Node**, Node*);
void displayList(Node*);

// Exercício 1. Elaborar o método de void insertBefore(Node*, int)
void insertBefore(Node*, int);
// Exercício 2. Elaborar o método de void deleteNodebyValue(Node**, int)
void deleteNodebyValue(Node**, int);
// Exercício 3. Elaborar o método de Node* searchNodebyValue(Node**, int)
Node* searchNodebyValue(Node**, int);

int main()
{
    Node* head = nullptr;
    displayList(head);
    cout << "====================================" << endl;
    insertEnd(&head,0);
    insertEnd(&head,1);
    insertEnd(&head,3);
    insertEnd(&head,7);
    insertEnd(&head,10);
    insertEnd(&head,13);
    displayList(head);
    cout << "====================================" << endl;

    // Testando insertBefore
    Node* nodeToInsertBefore = searchNodebyValue(&head, 7); // Pega o nó que possui 7
    insertBefore(nodeToInsertBefore, 5); // Insere "5" antes do nó com valor 7
    displayList(head);
    cout << "====================================" << endl;

    // Testando deleteNodebyValue
    deleteNodebyValue(&head, 9); // Tentará apagar o nó de valor 9, mas não encontrará
    deleteNodebyValue(&head, 7); // Apaga o nó de valor 7
    displayList(head);
    cout << "====================================" << endl;

    // Testando searchNodebyValue
    Node* searchedNode = searchNodebyValue(&head, 5); // Procura um nó com valor 5
    Node* searchedNode2 = searchNodebyValue(&head, 24); // Procura um nó com valor 24
    
    return 0;
}


Node* createNode(int iPayload)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->iPayload = iPayload;
    temp->ptrNext = nullptr;
    temp->ptrPrev = nullptr;
    
    return temp;
}


void displayList(Node* node)
{
    if (node == nullptr)
    {
        cout << "Lista vazia: Não é possível realizar displayList" << endl;
        return; //Usa return pra sair da função, o resto do código não será executado
    }
    
    if  (node -> ptrPrev != nullptr)
    {
        cout << "Meio ou Fim da Lista: Não é possível realizar displayList" << endl;
        return;
       
    }
    
    Node* temp = node;
     
    cout << "Payload: ";
    
    while(temp != nullptr)
    {
        cout << temp->iPayload<< " ";
        temp = temp->ptrNext;
    }
    
    cout << endl;
}

void insertFront(Node** head, int iPayload)
{
    Node* newNode = createNode(iPayload);
    // newNode->ptrNext = nullptr;
    
    if (*head != nullptr)
    {
        (*head)->ptrPrev = newNode;
        newNode->ptrNext = (*head);
        (*head) = newNode;
        
        return;
    }
}

void insertEnd(Node** head, int iPayload)
{
  Node* newNode = createNode(iPayload);
  //newNode -> ptrNext = nullptr;
  
  if (*head == nullptr)
  {
      //newNode -> ptrNext = nullptr; Essa linha não é obrigatória pois já definimos anteriormente
      (*head) = newNode;
      return;
      
  }
  
  Node* temp = (*head);
  
  //Percorremos a lista até seu fim(ptrNext do ultimo nó é NULL)
  while(temp->ptrNext != nullptr) temp = temp->ptrNext;
  
  newNode->ptrPrev = temp; //newNode aponta para o fim da lista
  temp->ptrNext = newNode; //Antigo último elemento aponta para o novo nó
}

void insertAfter(Node* ptrLocation, int iPayload)
{
    if(ptrLocation == nullptr)
    {
        cout << "Location é NULL" << endl;
        return;
    }
    
    Node* newNode = createNode(iPayload);
    
    // Corrigir nó a ser inserido
    newNode->ptrNext = ptrLocation->ptrNext;
    newNode->ptrPrev = ptrLocation;
    
    // Corrigir outros nós
    if (ptrLocation->ptrNext != nullptr) // Checa se a location não for a última
    {
        ptrLocation->ptrNext->ptrPrev = newNode;
    }
    ptrLocation->ptrNext = newNode;
}

void deleteNode(Node** head, Node* ptrDelete)
{
    if(*head == nullptr || ptrDelete == nullptr)
    {
        cout << "Não foi possível remover." << endl;
        return;
    }
    
    // Se o ptrDelete for o primeiro
    if (*head == ptrDelete) (*head) = ptrDelete->ptrNext;
    
    // Se o ptrDelete não é o último nó
    if (ptrDelete->ptrNext != nullptr) ptrDelete->ptrNext->ptrPrev = ptrDelete->ptrPrev;
    
    // Se o ptrDelete não for o primeiro
    if (ptrDelete->ptrPrev != nullptr) ptrDelete->ptrPrev->ptrNext = ptrDelete->ptrNext;
    
    free(ptrDelete);
}

// Exercício 1. Elaborar o método de void insertBefore(Node*, int)
void insertBefore(Node* ptrLocation, int iPayload)
{
    if(ptrLocation == nullptr)
    {
        cout << "Location é NULL" << endl;
        return;
    }
    
    Node* newNode = createNode(iPayload);
    
    // Corrigir nó a ser inserido
    newNode->ptrNext = ptrLocation;
    newNode->ptrPrev = ptrLocation->ptrPrev;
    
    // Corrigir outros nós
    if (ptrLocation->ptrPrev != nullptr) // Checa se a location não for a primeira
    {
        ptrLocation->ptrPrev->ptrNext = newNode;
    }
    ptrLocation->ptrPrev = newNode;
}

// Exercício 2. Elaborar o método de void deleteNodebyValue(Node**, int)
void deleteNodebyValue(Node** head, int iPayload)
{
    if(*head == nullptr)
    {
        cout << "Não foi possível remover." << endl;
        return;
    }
    
    Node* temp = *head;
    
    // Procurar o nó com o valor especificado
    while(temp != nullptr && temp->iPayload != iPayload)
    {
        temp = temp->ptrNext;
    }
    
    // Se o nó não foi encontrado
    if(temp == nullptr)
    {
        cout << "Nó com valor " << iPayload << " não encontrado." << endl;
        return;
    }
    
    // Se o nó foi encontrado, deletar
    cout << "Nó com valor " << iPayload << " deletado." << endl;
    deleteNode(head, temp);
}

// Exercício 3. Elaborar o método de Node* searchNodebyValue(Node**, int)
Node* searchNodebyValue(Node** head, int iPayload)
{
    if(*head == nullptr)
    {
        cout << "Lista vazia." << endl;
        return nullptr;
    }
    
    Node* temp = *head;
    
    // Procurar o nó com o valor especificado
    while(temp != nullptr)
    {
        if(temp->iPayload == iPayload)
        {
            cout << "Nó com valor " << iPayload << " encontrado." << endl;
            return temp;
        }
        temp = temp->ptrNext;
    }
    
    // Se o nó não foi encontrado
    cout << "Nó com valor " << iPayload << " não encontrado." << endl;
    return nullptr;
}
