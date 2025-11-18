#include <iostream>

using namespace std;

struct Node{
    int order, num;
    struct Node *next, *prev;
};

struct LinkedList{
    struct Node *head;
};


int main(){
    freopen("testcase2.txt", "r", stdin);
    freopen("output2.txt", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}