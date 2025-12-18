#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef struct Node{
    int data;
    struct Node *next,*prev;
}Node;

typedef struct Queue{
    Node *front,*rear;
}Queue;

void push(Queue *q,int x){
    Node *newNode = new Node();
    newNode->data = x;
    if(q->front == NULL){
        newNode->next = newNode->prev = NULL;
        q->front = newNode;
        q->rear = newNode;
    }
    else{
        newNode->prev = NULL;
        newNode->next = q->rear;
        q->rear->prev = newNode;
        q->rear = newNode;
    } 
}
int pop(Queue *q){
    Node *temp = q->front;
    q->front = q->front->prev;
    int x = temp->data;
    delete temp;
    return x;
}

bool isEmpty(Queue *q){
    return q->front == NULL;
}


void solve_case(){
    
}

int main(){
    freopen("testcase6.txt","r",stdin);
    freopen("output6.txt","w",stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t--){
        solve_case();
    }
    return 0;
}