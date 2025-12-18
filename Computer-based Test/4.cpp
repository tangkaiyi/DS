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

void push(Stack *st,int val){
    Node *newNode = new Node();
    newNode->data = val;
    newNode->next = st->top;
    st->top = newNode;
}

int pop(Stack *st){
    if(st->top == NULL) return -1;
    Node *temp = st->top;
    st->top = st->top->next;
    delete temp;
    return temp->data;
}

int top(Stack *st){
    if(st->top == NULL) return -1;
    return st->top->data;
}

bool isEmpty(Stack *st){
    return st->top == NULL;
}

void clear(Stack *st){
    while(!isEmpty(st)){
        pop(st);
    }
}

void solve_case(){
    int n;
    cin >> n;
    vector<int> targets(n);
    for(int i=0;i<n;i++){
        cin >> targets[i];
    }
    int current = 1;
    bool possible = true;

    Stack *st = new Stack();
    st->top = NULL;

    for(int target:targets){
        while(isEmpty(st) || top(st) != target){
            if(current>n){
                possible = false;
                break;
            }
            push(st,current);
            current++;
        }
        if(!isEmpty(st) && top(st) == target){
            pop(st);
        }
        else{
            possible = false;
            break;
        }
    }

    if(possible) cout << "Yes\n";
    else cout << "No\n";

    clear(st);
    delete st;
}

int main(){
    freopen("testcase1.txt","r",stdin);
    freopen("output1.txt","w",stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t--){
        solve_case();
    }
    return 0;
}   