#include <iostream>
#include <vector>

using namespace std;

typedef struct Node{
    int data;
    struct Node *next;
}Node;

typedef struct{
    Node *top;
}Stack;

void push(Stack *st,int x){
    Node *newNode = new Node();
    newNode->data = x;
    newNode->next = st->top;
    st->top = newNode;
}

void pop(Stack *st){
    Node *temp = st->top;
    st->top = st->top->next;
    delete temp;
}

int top(Stack *st){
    return st->top->data;
}

bool isEmpty(Stack *st){
    return st->top == NULL;
}

void clear(Stack *st){
    while(st->top){
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
    int curr = 1;
    bool possible = true;
    for(int target:targets){
        while(isEmpty(st) || top(st) != target){
            if(curr>n){
                possible = false;
                break;
            }
            push(st,curr);
            curr++;
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