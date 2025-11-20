#include <iostream>
#include <vector>

using namespace std;

typedef struct Node {
    long long power;
    int id; 
    struct Node *next, *pre;
} Node;

typedef struct Queue {
    Node *front, *rear;
} Queue;

struct BattleLog {
    int killer_id;
};

bool isWeaker(long long p1, int id1, long long p2, int id2) {
    if (p1 != p2) return p1 < p2;
    return id1 < id2;
}

void insertSorted(Queue *q, Node *newNode) {
    if (q->front == NULL) {
        q->front = q->rear = newNode;
        newNode->next = newNode->pre = NULL;
        return;
    }

    if (!isWeaker(newNode->power, newNode->id, q->rear->power, q->rear->id)) {
        newNode->pre = q->rear;
        newNode->next = NULL;
        q->rear->next = newNode;
        q->rear = newNode;
        return;
    }

    if (isWeaker(newNode->power, newNode->id, q->front->power, q->front->id)) {
        newNode->next = q->front;
        newNode->pre = NULL;
        q->front->pre = newNode;
        q->front = newNode;
        return;
    }

    Node *curr = q->rear;
    
    while (curr != NULL && isWeaker(newNode->power, newNode->id, curr->power, curr->id)) {
        curr = curr->pre;
    }
    
    newNode->next = curr->next;
    newNode->pre = curr;
    if (curr->next) {
        curr->next->pre = newNode;
    }
    curr->next = newNode;
}

void solve() {
    int n;
    if (!(cin >> n)) return;

    Queue q;
    q.front = q.rear = NULL;
    
    for (int i = 0; i < n; i++) {
        long long p;
        cin >> p;
        Node *node = new Node();
        node->power = p;
        node->id = i;
        
        if (q.rear == NULL) {
            q.front = q.rear = node;
            node->pre = node->next = NULL;
        } else {
            q.rear->next = node;
            node->pre = q.rear;
            node->next = NULL;
            q.rear = node;
        }
    }

    vector<int> death_at_step(n, -1);
    vector<BattleLog> logs(n + 1);

    int current_beasts = n;
    
    while (current_beasts > 1) {
        Node *weakest = q.front;
        Node *strongest = q.rear;

        logs[current_beasts].killer_id = strongest->id;
        death_at_step[weakest->id] = current_beasts;

        long long new_val = strongest->power - weakest->power;
        int killer_id = strongest->id;

        q.front = weakest->next;
        if (q.front) q.front->pre = NULL;
        else q.rear = NULL;

        if (strongest == q.front) { 
             q.front = NULL; 
             q.rear = NULL;
        } else {
            q.rear = strongest->pre;
            if (q.rear) q.rear->next = NULL;
            else q.front = NULL;
        }
        
        delete weakest;
        delete strongest;

        Node *newNode = new Node();
        newNode->power = new_val;
        newNode->id = killer_id;
        insertSorted(&q, newNode);

        current_beasts--;
    }

    if (q.front) delete q.front;

    int final_stop_at = 1; 
    for (int k = 2; k <= n; k++) {
        int killer = logs[k].killer_id;
        int die_step = death_at_step[killer];
        
        if (die_step != -1 && die_step > final_stop_at) {
            final_stop_at = k;
        }
    }
    
    cout << final_stop_at << "\n";
}

int main() {
    freopen("testcase4.txt", "r", stdin);
    freopen("output4.txt", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (cin >> T) {
        while(T--) {
            solve();
        }
    }
    return 0;
}