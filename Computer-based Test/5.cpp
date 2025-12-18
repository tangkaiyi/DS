#include <iostream>
#include <vector>

using namespace std;

struct Node{
    int order, num;
    struct Node *next,*prev;
};

struct LinkedList{
    struct Node *head;
};

void llinsert(Node *node,Node *newnode){
    newnode->next = node->next;
    newnode->prev = node;
    node->next->prev = newnode;
    node->next = newnode;
}

void lldelete(Node *deletenode){
    Node *temp = deletenode;
    deletenode->prev->next = deletenode->next;
    deletenode->next->prev = deletenode->prev;
    delete temp;
}

int gcd(int a,int b){
    if(b == 0) return a;
    return gcd(b,a%b);
}

void solve_case(){
    int m;
    cin >> m;
    vector<int>del;
    LinkedList *ll = new LinkedList();
    Node *newNode = new Node();
    newNode->order = 1;
    cin >> newNode->num;
    newNode->next = newNode;
    newNode->prev = newNode;
    ll->head = newNode;
    int time = 0;
    Node *temp = ll->head;
    for(int i=2;i<=m;i++){
        Node *newNode = new Node();
        newNode->order = i;
        cin >> newNode->num;
        llinsert(temp,newNode);
        temp = newNode;
    }
    ll->head = ll->head->next;
    while(time != m){
        if(gcd(ll->head->prev->num,ll->head->num) == 1){
            Node *temp = ll->head->next;
            del.push_back(ll->head->order);
            lldelete(ll->head);
            time = 0;
            m--;
            ll->head = temp->next;
        }
        else{
            time++;
            ll->head = ll->head->next;
        }
    }
    cout << del.size() << " ";
    for(int x:del){
        cout << x << " ";
    }
    cout << endl;
}

int main(){
    freopen("testcase5.txt","r",stdin);
    freopen("output5.txt","w",stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        solve_case();
    }
    return 0;
}