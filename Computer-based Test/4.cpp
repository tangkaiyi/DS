#include <iostream>
#include <vector>

using namespace std;

typedef struct Node{
    int data;
    Node *next;
}Node;

typedef struct{
    Node *top;
}Stack;

bool isEmpty(Stack *st){
    return st->top == NULL;
}

void push(Stack *st,int x){
    Node *newNode = new Node();
    newNode->data = x;
    newNode->next = st->top;
    st->top = newNode;
}

void pop(Stack *st){
    if(st->top == NULL) return;
    Node *temp = st->top;
    st->top = temp->next;
    delete temp;
}

int top(Stack *st){
    if(st->top == NULL) return -1;
    return st->top->data;
}

void clear(Stack *st){
    while(st->top != NULL){
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
    Stack *st = new Stack();
    st->top = NULL;
    int current = 1;
    bool possible = true;
    for(int target:targets){
        while(isEmpty(st) || target != top(st)){
            if(current>n){
                possible = false;
                break;
            }
            push(st,current);
            current++;
        }
        if(!isEmpty(st) && target == top(st)){
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
    freopen("testcase4.txt","r",stdin);
    freopen("output4.txt","w",stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t--){
        solve_case();
    }
    return 0;
}