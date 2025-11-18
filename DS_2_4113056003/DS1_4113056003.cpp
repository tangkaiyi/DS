#include <iostream>

using namespace std;

struct Node {
    int data;
    struct Node* next;
};

struct Stack {
    Node* top;
};

void Stack_init(Stack* s) {
    s->top = NULL;
}

bool Stack_isEmpty(Stack* s) {
    return s->top == NULL;
}

void Stack_push(Stack* s, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
}

void Stack_pop(Stack* s) {
    if (Stack_isEmpty(s)) {
        return;
    }
    Node* temp = s->top;
    s->top = s->top->next;
    free(temp);
}

int Stack_top(Stack* s) {
    if (Stack_isEmpty(s)) {
        return -1; 
    }
    return s->top->data;
}

void solve_case() {
    int n;
    cin >> n;
    if (n == 0) {
        cout << "Yes\n";
        return;
    }
    
    int target_order[50001]; 
    for (int i = 0; i < n; ++i) {
        cin >> target_order[i];
    }

    Stack station;
    Stack_init(&station);
    int current_item = 1;
    bool possible = true;

    for (int i = 0; i < n; ++i) {
        int target = target_order[i];
        while (current_item <= target) {
            Stack_push(&station, current_item);
            current_item++;
        }
        
        if (!Stack_isEmpty(&station) && Stack_top(&station) == target) {
            Stack_pop(&station);
        } else {
            possible = false;
            break;
        }
    }
    
    cout << (possible ? "Yes\n" : "No\n");

    while (!Stack_isEmpty(&station)) {
        Stack_pop(&station);
    }
}

int main(){
    freopen("testcase1.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve_case();
    }
    return 0;
}