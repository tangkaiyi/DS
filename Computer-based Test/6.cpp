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

void addEdge(Node** adj,int data1,int data2){
    Node *newNode = new Node();
    newNode->data = data1;
    newNode->next = adj[data2];
    adj[data2] = newNode;

    newNode = new Node();
    newNode->data = data2;
    newNode->next = adj[data1];
    adj[data1] = newNode;
}

int bfs(Node** adj,int n,int startnode,vector<int> hubs){
    vector<int>dist(n+1,-1);
    dist[startnode] = 0;
    Queue *q = new Queue();
    push(q,startnode);

    while(!isEmpty(q)){
        int x = pop(q);
        Node *temp = adj[x];
        while(temp != NULL){
            int y = temp->data;
            if(dist[y] == -1){
                push(q,y);
                dist[y] = dist[x]+1;
            }
            temp = temp->next;
        }
    }
    int total_dist = 0;
    for(int hub:hubs){
        if(dist[hub] != -1) total_dist+=dist[hub];
    }
    return total_dist;
}

void solve_case(){
    int n,s;
    cin >> n >> s;
    Node** adj = new Node*[n+1];
    for(int i=0;i<=n;i++) adj[i] = NULL;
    vector<int> count(n+1,0);
    for(int i=0;i<s;i++){
        int data,prev;
        bool first = true;
        while(cin >> data && data != 0){
            count[data]++;
            if(!first){
                addEdge(adj,data,prev);
            }
            first = false;
            prev = data;
        }
    }
    vector<int>hubs;
    for(int i=1;i<=n;i++){
        if(count[i]>1) hubs.push_back(i);
    }
    int min_dist = -1;
    int best_hub = -1;
    for(int hub:hubs){
        int dist = bfs(adj,n,hub,hubs);
        if(min_dist == -1 || dist < min_dist){
            min_dist = dist;
            best_hub = hub;
        } 
        else if(min_dist == dist){
            if(hub<best_hub){
                best_hub = hub;
            }
        }
    }
    cout << best_hub << endl;
    
    for(int i=0;i<n+1;i++){
        Node *current = adj[i];
        while(current != NULL){
            Node *temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] adj;
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