#include <iostream>
#include <vector>

using namespace std;

struct Node{
    int order,num;
    struct Node *next,*prev;
};

struct LinkedList{
    struct Node *head;
};

void linsert(Node* node,Node* newnode){
    newnode->prev = node;
    newnode->next = node->next;
    node->next->prev = newnode;
    node->next = newnode;
}

void ldelete(Node* node,Node* deleted){
    deleted->prev->next = deleted->next;
    deleted->next->prev = deleted->prev;
    delete(deleted);
}

int gcd(int a,int b){
    if(b == 0)
        return a;
    
    return gcd(b, a%b);
}

void solve_case(){
    int m;
    cin >> m;
    LinkedList* ll = new LinkedList();
    Node* newNode = new Node();
    cin >> newNode->num;
    newNode->order = 1;
    ll->head = newNode;
    newNode->next = newNode;
    newNode->prev = newNode;
    Node* temp = ll->head;
    for(int i=2;i<=m;i++){
        Node* newNode = new Node();
        cin >> newNode->num;
        newNode->order = i;
        linsert(temp,newNode);
        temp = newNode;
    }
    vector<int> del;
    int time = 0;
    ll->head = ll->head->next;
    while(time != m){
        if(gcd(ll->head->num,ll->head->prev->num) == 1){
            temp = ll->head->next;
            del.push_back(ll->head->order);
            ldelete(ll->head->prev,ll->head);
            time = 0;
            m--;
            ll->head = temp;
            ll->head = ll->head->next;
        }
        else{
            ll->head = ll->head->next;
            time++;
        }
    }
    cout << del.size() << " ";
    for(int i=0;i<del.size()-1;i++){
        cout << del[i] <<" ";
    }
    cout << del[del.size()-1];
    cout << endl;

}

int main(){
    if(!freopen("testcase2.txt","r",stdin)) return -1;
    if(!freopen("output2.txt","w",stdout)) return -1;
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t--){
        solve_case();
    }
    return 0;
}