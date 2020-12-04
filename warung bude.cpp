#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct Dish {// struct untuk dish 
    char name[255];
    int price, quantity;
    Dish *prev, *next;
}*headDish, *tailDish, *currDish, *newDish, *delDish;

struct Order {//untuk order
    char name[255];
    int quantity, price;
    Order *prev, *next;
}*newOrder, *currOrder, *delOrder;

struct Customer {//cus
    char name[255];
    Order *headOrder, *tailOrder;
    Customer *prev, *next;    
}*headCustomer[26], *tailCustomer[26], *currCustomer, *newCustomer, *delCustomer;
struct Node {
  int value;
  Node *next, *prev;
} *head, *tail, *curr;
Node *createNode(int value) {
  Node *temp = (Node*)malloc(sizeof(Node));
  temp->value = value;
  temp->next = temp->prev = NULL;
  return temp;
}
void pushHead(int value) {
  Node *temp = createNode(value);

  if(!head) { // 0 node
    head = tail = temp; // Linked List: temp (head dan tail)
  } else { // Linked List: A (head dan tail), mau insert B
    head->prev = temp; // B <- A (head dan tail)
    temp->next = head; // B -><- A (head dan tail)
    head = temp; // B (temp) -><- A (tail)
  }
}
void pushTail(int value) {
  Node *temp = createNode(value);

  if(!head) { // 0 node
    head = tail = temp; // Linked List: temp (head dan tail)
  } else { // Linked List: A (head dan tail), mau insert B
    tail->next = temp; // A (head dan tail) -> B
    temp->prev = tail; // A (head dan tail) -><- B
    tail = temp;  // A (head) -><- B (tail)
  }
}
void pushMid(int value) {
  if(!head) { // tidak ada node
    Node *temp = createNode(value);
    head = tail = temp;
  } else if(value < head->value) { // nilai kurang dari head
    pushHead(value);
  } else if(value > tail->value) { // nilai lebih dari tail
    pushTail(value);
  } else { // nilai di antara head dan tail
    // 1 (curr) -> 8 -> 12 -> 15, mau insert 9
    Node *temp = createNode(value);
    curr = head;

    // selama nilainya kurang dari value
    while(curr->value < value) {
      curr = curr->next;
    }
    // 1 -><- 8 -><- 12 (curr) -><- 15, mau insert 9
    // 1 -><- 8 -><- 9 -><- 12 (curr) -><- 15

    temp->prev = curr->prev; // temp->prev = 8
    temp->next = curr; // temp->next = 12
    // Hasilnya: 1 -><- 8 ->      <- 12 (curr) -><- 15
    //                   \(prev)   /(next)
    //                         temp

    curr->prev->next = temp; // 8->next = temp
    curr->prev = temp; // 12->prev = temp
    // Hasilnya: 1 -><- 8                           12 (curr) -><- 15
    //                   \(prev)\(next)     /(next)/(prev)
    //                                 temp
  }
}
void popHead() {
  if(head && head == tail) { // jika hanya 1 node
    head = tail = NULL;
    free(head);
  } else { // jika > 1 node // A (head) -><- B -><- C
    Node *newHead = head->next; // A (head) -><- B (newHead) -><- C
    head->next = newHead->prev = NULL; // A (head) B (newHead) -><- C
    free(head); // B (newHead) -><- C
    head = newHead; // B (head) -><- C
  }
}
void popTail() {
  if(head && head == tail) { // jika hanya 1 node
    head = tail = NULL;
    free(head);
  } else { // jika > 1 node // A -><- B -><- C (tail)
    Node *newTail = tail->prev; // A -><- B (newTail) -><- C (tail)
    tail->prev = newTail->next = NULL; // A -><- B (newTail) C (tail)
    free(tail); // A -><- B (newTail)
    tail = newTail; // A -><- B (tail)
  }
}
void popMid(int value) {
  if(!head) {
    return;
  } else if(head->value == value) {
    popHead(); // jika nilai head adalah yang mau kita hapus
  } else if(tail->value == value) {
    popTail(); // jika nilai tail adalah yang mau kita hapus
  } else { // jika nilai yang mau kita hapus ada di tengah2
    curr = head; // 10 (curr) 20 30 40 50, mau hapus 30

    while(curr && curr->value != value) {
      curr = curr->next;
    }
    // 10 -><- 20 -><- 30 (curr) -><- 40 -><- 50, mau hapus 30

    curr->prev->next = curr->next; // 20->next = 40
    curr->next->prev = curr->prev; // 40->prev = 20
    // 10 -><- 20      -><-     40 -><- 50, mau hapus 30
    //          \<- 30 (curr) ->/ 

    curr->prev = curr->next = NULL; // putusin link si curr
    free(curr);
    // 10 -><- 20 -><- 40 -><- 50
  }
}
void time(){
#ifdef __ANDROID__
  printf("system:android\n");
 #elif __linux__
  printf("system:linux\n");
 #elif _WIN32
  printf("system:windows\n");
 #else 
  printf("unidentified OS\n\n");
 #endif
 time_t currentClock;
 time(&currentClock);
 printf("%s",ctime(&currentClock));
}

int main(){

}
