#include <iostream>
#include <vector>

using namespace std;

struct Node{
    int oreder,num;
    struct Node *next, *prev;
};

struct LinkedList{
    struct Node *head;
};

void llinsert(Node* node,Node* newNode){
    newNode->next = node->next;
    newNode->prev = node;
    node->next->prev = newNode;
    node->next = newNode;
}

void lldelete(Node* node){
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete(node);
}

int gcd(int a,int b){
    if(b == 0){
        return a;
    }
    return gcd(b, a%b);
}

void solve_case(){
    int m;
    cin >> m;
    LinkedList* ll = new LinkedList();
    Node* newNode = new Node();
    vector<int>del;
    newNode->oreder = 1;
    cin >> newNode->num;
    ll->head = newNode;
    newNode->next = newNode;
    newNode->prev = newNode;
    Node* temp = ll->head;
    for(int i=2;i<=m;i++){
        Node* newNode = new Node();
        newNode->oreder = i;
        cin >> newNode->num;
        llinsert(temp,newNode);
        temp = newNode;
    }
    int time = 0;
    ll->head = ll->head->next;
    while(time!=m){
        if(gcd(ll->head->num,ll->head->prev->num) == 1){
            Node* temp = ll->head->next;
            del.push_back(ll->head->oreder);
            lldelete(ll->head);
            m--;
            time=0;
            ll->head=temp;
            ll->head=ll->head->next;
        }
        else{
            time++;
            ll->head=ll->head->next;
        }
    }
    cout << del.size() << " ";
    for(int k:del){
        cout << k << " " ;
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