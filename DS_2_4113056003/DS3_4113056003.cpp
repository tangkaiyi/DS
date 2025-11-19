#include <iostream>
#include <vector>

using namespace std;

typedef struct Node{
    int data;
    struct Node *next, *pre;
}Node;

typedef struct Queue{
    Node *front, *rear;
}Queue;

void initQueue(Queue* q){
    q -> front = q -> rear = NULL;
}

void enqueue(Queue *q, int v) {
    Node *temp = new Node();
    temp->data = v;
    temp->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = temp;
    } else {
        q->rear->next = temp;
        q->rear = temp;
    }
}

int dequeue(Queue *q) {
Node *temp = q->front;
    int val = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    delete temp;
    return val;
}

bool isQueueEmpty(Queue *q) {
    return q->front == NULL;
}

void addEdge(Node** adj,int data1,int data2){
    Node* newNode = new Node();
    newNode -> data = data1;
    newNode -> next = adj[data2];
    adj[data2] = newNode;

    newNode = new Node();
    newNode -> data = data2;
    newNode -> next = adj[data1];
    adj[data1] = newNode;

}

int bfs(int startnode,int n,Node** adj,vector<int> hubs){
    vector<int> dist(n+1,-1);
    Queue* q = new Queue();
    initQueue(q);

    enqueue(q,startnode);
    dist[startnode] = 0;

    while(!isQueueEmpty(q)){
        int x = dequeue(q);

        Node* ptr = adj[x];
        while(ptr != NULL){
            int y = ptr -> data;
            if(dist[y] == -1){
                dist[y] = dist[x] + 1;
                enqueue(q,y);
            }
            ptr = ptr -> next;
        }
    }

    int total_dist = 0;
    for(int h:hubs){
        if(h == startnode) continue;
        if(dist[h] != -1) total_dist+= dist[h];
    }
    return total_dist;
}

void solve_case(){
    int n,s;
    cin >> n >> s;
    Node** adj = new Node*[n + 1];
    for(int i=0;i<=n;i++) adj[i] = NULL;
    vector<int> route_counts(n+1,0);

    for(int i=0;i<s;i++){
        int data,prev = -1;
        bool first = true;
        while(cin >> data && data != 0){
            route_counts[data]++;
            if(!first){
                addEdge(adj,prev,data);
            }
            prev = data;
            first = false;
        }
    }

    vector<int> hubs;
    for(int i=1;i<=n;i++){
        if(route_counts[i] > 1){
            hubs.push_back(i);
        }
    }

    int min_total_dist = -1;
    int best_hub = -1;

    for(int h:hubs){
        int dist = bfs(h,n,adj,hubs);
        if(min_total_dist == -1 || dist < min_total_dist){
            min_total_dist = dist;
            best_hub = h;
        }
        else if(dist == min_total_dist){
            if(h < best_hub) best_hub = h;
        }
    }
    cout << best_hub << endl;

    for(int i=0; i<=n; i++) {
        Node *curr = adj[i];
        while(curr) {
            Node *temp = curr;
            curr = curr->next;
            delete temp;
        }
    }
    delete[] adj;
}

int main(){
    freopen("testcase3.txt", "r", stdin);
    freopen("output3.txt", "w", stdout);
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t--){
        solve_case();
    }

}