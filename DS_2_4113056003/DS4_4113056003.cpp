#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

typedef struct Node {
    long long power;
    int id; 
    struct Node *next, *pre;
} Node;

typedef struct Queue {
    Node *front, *rear;
} Queue;

struct BattleStep {
    int killer_id;
};

void solve() {
    int n;
    if (!(cin >> n)) return;

    Queue q;
    q.front = q.rear = NULL;

    set<pair<long long, int>> beasts;

    for (int i = 0; i < n; i++) {
        long long p;
        cin >> p;

        beasts.insert({p, i});

        Node *node = new Node();
        node->power = p;
        node->id = i;
        node->next = NULL;
        node->pre = q.rear;
        if (q.rear == NULL) {
            q.front = q.rear = node;
        } else {
            q.rear->next = node;
            q.rear = node;
        }
    }

    vector<BattleStep> logs(n + 1);

    vector<int> death_at_step(n, -1); 

    int current_beasts = n;

    while (current_beasts > 1) {
        auto it_weak = beasts.begin();
        auto it_strong = beasts.rbegin();

        long long weak_power = it_weak->first;
        int weak_id = it_weak->second;

        long long strong_power = it_strong->first;
        int strong_id = it_strong->second;

        logs[current_beasts].killer_id = strong_id;

        death_at_step[weak_id] = current_beasts;

        long long new_val = strong_power - weak_power;

        beasts.erase(it_weak); 
        beasts.erase({strong_power, strong_id});

        beasts.insert({new_val, strong_id});

        current_beasts--;
    }

    int final_stop_at = 1;

    for (int k = 2; k <= n; k++) {
        int killer = logs[k].killer_id;
        int die_step = death_at_step[killer];

        if (die_step != -1 && die_step > final_stop_at) {
            final_stop_at = k;
        }
    }
    
    cout << final_stop_at << endl;

    Node *curr = q.front;
    while (curr) {
        Node *temp = curr;
        curr = curr->next;
        delete temp;
    }
}

int main() {
    freopen("testcase4.txt", "r", stdin);
    freopen("output4.txt", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while(t--) {
            solve();
        }
    }
    return 0;
}