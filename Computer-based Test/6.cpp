#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef struct Node{
    int data;
    struct Node *next, *prev;
}Node;

void addEdge(Node** adj,int data1,int data2){
    Node *newNode = new Node();
    newNode->data = data1;
    newNode->next = adj[data2];
    adj[data2] = newNode;

    Node *newNode1 = new Node();
    newNode1->data = data2;
    newNode1->next = adj[data1];
    adj[data1] = newNode1;
}

int bfs(int startnode,int n,Node** adj,vector<int>hubs){
    vector<int>dist(n+1,-1);
    queue<int> q;

    q.push(startnode);
    dist[startnode] = 0;
    while(!q.empty()){
        int x = q.front();
        q.pop();

        Node *ptr = adj[x];
        while(ptr != NULL){
            int y = ptr->data;
            if(dist[y] == -1){
                dist[y] = dist[x]+1;
                q.push(y);
            }
            ptr = ptr->next;
        }
    }
    int total_dist = 0;
    for(int hub:hubs){
        if(dist[hub] != -1)total_dist += dist[hub];
    }
    return total_dist;
}
void solve_case(){
    int n,s;
    cin >> n >> s;
    Node** adj = new Node*[n + 1];
    for(int i=0;i<=n;i++) adj[i] = NULL;
    vector<int> count(n+1,0);
    for(int i=0;i<s;i++){
        int data,prev = -1;
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
    vector<int>hubs;
    for(int i=0;i<=n;i++){
        if(count[i]>1){
            hubs.push_back(i);
        }
    }
    int min_dist = -1;
    int best_hub = -1;

    for(int hub:hubs){
        int dist = bfs(hub,n,adj,hubs);
        if(min_dist == -1 || dist < min_dist){
            min_dist = dist;
            best_hub = hub;
        }
        else if(dist == min_dist){
            if(hub < best_hub){
                best_hub = hub;
            }
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