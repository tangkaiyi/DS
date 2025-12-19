#include <iostream>
#include <vector>

using namespace std;

typedef struct Node{
    int data;
    struct Node *next,*prev;
}Node;

typedef struct Queue{
    Node *front,*rear;
}Queue;

void enqueue(Queue *q,int x){
    Node *node = new Node();
    node->data=x;
    if(q->front == NULL){
        q->front=q->rear = node;
        node->next = NULL;
    }
    else{
        q->rear->next=node;
        q->rear = node;
        node->next = NULL;
    }
}

int dequeue(Queue *q){
    Node *temp = q->front;
    q->front=q->front->next;
    int val = temp->data;
    delete temp;
    return val;
}

bool isEmpty(Queue *q){
    return q->front == NULL;
}

void addEdge(Node **adj,int data1,int data2){
    Node *newNode = new Node();
    newNode->data = data1;
    newNode->next = adj[data2];
    adj[data2] = newNode;

    newNode = new Node();
    newNode->data = data2;
    newNode->next = adj[data1];
    adj[data1] = newNode;
}

int bfs(Node **adj,int n,int startnode,vector<int> hubs){
    vector<int>dist(n+1,-1);
    Queue *q = new Queue();
    q->front = NULL;
    enqueue(q,startnode);
    dist[startnode] = 0;

    while(!isEmpty(q)){
        int x=dequeue(q);
        Node *ptr = adj[x];
        while(ptr){
            int y = ptr->data;
            if(dist[y] == -1){
                enqueue(q,y);
                dist[y] = dist[x]+1;
            }
            ptr=ptr->next;
        }
    }
    int total = 0;
    for(int hub:hubs){
        if(dist[hub] != -1) total+=dist[hub];
    };
    return total;
}

void solve_case(){
    int n,s;
    cin >> n >> s;
    Node** adj = new Node*[n+1];
    for(int i=0;i<=n;i++){
        adj[i] = NULL;
    }
    vector<int> count(n+1,0);
    vector<int>hubs;
    for(int i=0;i<s;i++){
        int data,prev;
        bool first = true;
        while(cin >> data && data != 0){
            count[data]++;
            if(!first){
                addEdge(adj,data,prev);
            }
            prev = data;
            first = false;
        }
    }
    for(int i=0;i<=n;i++){
        if(count[i]>1) hubs.push_back(i);
    }
    int min_dist = -1;
    int best_hub = -1;
    for(int h:hubs){
        int dist = bfs(adj,n,h,hubs);
        if(min_dist == -1 || dist < min_dist){
            min_dist = dist;
            best_hub = h;
        }
        else if(dist == min_dist){
            if(h<best_hub) best_hub = h;
        }
    }
    cout << best_hub << endl;
    for(int i=0;i<=n;i++){
        while(adj[i]){
            Node *temp = adj[i];
            adj[i] = adj[i]->next;
            delete temp;
        }
        delete adj[i];
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