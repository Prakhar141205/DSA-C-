#include <stack>
#include <vector>
#include <iostream>
using namespace std;

void insertAtBottom(stack<int> &s, int val){
    if(s.empty()) {
        s.push(val);
        return ;
    }

    int topVal = s.top();
    s.pop();

    insertAtBottom(s, val);

    s.push(topVal);
}
void reverseStack(stack<int> &s){
    if(s.empty()) return ;

    int topval = s.top();
    s.pop();

    reverseStack(s);

    insertAtBottom(s, topval);
}
int main(){
    stack<int> s;
    s.push(4);
    s.push(3);
    s.push(2);

    reverseStack(s);

    while(!s.empty()){
        cout << s.top() << "\n";
        s.pop();
    }
    return 0;
}