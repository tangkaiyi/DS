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

void initQueue(Queue *q) {
    q->front = q->rear = NULL;
}

void pushBack(Queue *q, Node *node) {
    node->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = node;
        node->pre = NULL;
    } else {
        q->rear->next = node;
        node->pre = q->rear;
        q->rear = node;
    }
}

Node* popFront(Queue *q) {
    if (q->front == NULL) return NULL;
    Node *temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    } else {
        q->front->pre = NULL;
    }
    temp->next = NULL;
    return temp;
}

Node* popBack(Queue *q) {
    if (q->rear == NULL) return NULL;
    Node *temp = q->rear;
    q->rear = q->rear->pre;
    if (q->rear == NULL) {
        q->front = NULL;
    } else {
        q->rear->next = NULL;
    }
    temp->pre = NULL;
    return temp;
}

void solve() {
    int n;
    if (!(cin >> n)) return;

    Queue q1, q2;
    initQueue(&q1);
    initQueue(&q2);

    for (int i = 0; i < n; i++) {
        long long p;
        cin >> p;
        Node *node = new Node();
        node->power = p;
        node->id = i;
        pushBack(&q1, node);
    }

    vector<int> death_at_step(n, -1);
    vector<BattleLog> logs(n + 1);
    int current_beasts = n;

    while (current_beasts > 1) {
        Node *weakest = NULL;
        Node *strongest = NULL;

        if (q2.front == NULL) {
            weakest = popFront(&q1);
        } else if (q1.front == NULL) {
            weakest = popBack(&q2);
        } else {
            if (isWeaker(q1.front->power, q1.front->id, q2.rear->power, q2.rear->id)) {
                weakest = popFront(&q1);
            } else {
                weakest = popBack(&q2);
            }
        }

        if (q2.front == NULL) {
            strongest = popBack(&q1);
        } else if (q1.front == NULL) {
            strongest = popFront(&q2);
        } else {
            if (!isWeaker(q1.rear->power, q1.rear->id, q2.front->power, q2.front->id)) {
                strongest = popBack(&q1);
            } else {
                strongest = popFront(&q2);
            }
        }

        logs[current_beasts].killer_id = strongest->id;
        death_at_step[weakest->id] = current_beasts;

        strongest->power = strongest->power - weakest->power;
        
        pushBack(&q2, strongest);
        delete weakest;

        current_beasts--;
    }

    while (q1.front) delete popFront(&q1);
    while (q2.front) delete popFront(&q2);

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
    freopen("testcase4.txt","r",stdin);
    freopen("output4.txt","w",stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}