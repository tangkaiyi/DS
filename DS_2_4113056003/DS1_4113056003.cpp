#include <iostream>
#include <vector>

using namespace std;

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
} Stack;

void push(Stack *s, int val) {
    Node *newNode = new Node();
    newNode->data = val;
    newNode->next = s->top;
    s->top = newNode;
}

int pop(Stack *s) {
    if (s->top == NULL) return -1;
    Node *temp = s->top;
    int val = temp->data;
    s->top = s->top->next;
    delete temp;
    return val;
}

int peek(Stack *s) {
    if (s->top == NULL) return -1;
    return s->top->data;
}

bool isEmpty(Stack *s) {
    return s->top == NULL;
}

void cleanStack(Stack *s) {
    while (!isEmpty(s)) {
        pop(s);
    }
}

void solve(bool last=false) {
    int N;
    if (!(cin >> N)) return;
    
    vector<int> target(N);
    for (int i = 0; i < N; i++) {
        cin >> target[i];
    }

    Stack s;
    s.top = NULL;
    
    int current_input = 1;
    int target_idx = 0;
    bool possible = true;

    while (target_idx < N) {
        int needed = target[target_idx];
        
        if (!isEmpty(&s) && peek(&s) == needed) {
            pop(&s);
            target_idx++;
        } else if (current_input <= N) {
            push(&s, current_input);
            current_input++;
        } else {
            possible = false;
            break;
        }
    }

    if (possible) cout << "Yes";
    else cout << "No";

    if (!last) cout << '\n';
    
    cleanStack(&s);
}

int main() {
    freopen("testcase1.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if (cin >> T) {
        for (int tc = 0; tc < T; ++tc) {
            solve(tc == T - 1);
        }
    }
    return 0;
}