#include <iostream>
#include <stack>
#include <vector>


using namespace std;

void insertAtCorrectPos(stack<int>& s, int val){
    if(s.empty() || s.top() <= val){
        s.push(val);
        return;
    }

    int topVal = s.top();
    s.pop();

    insertAtCorrectPos(s, val);

    s.push(topVal);
}

void sortStack(stack<int>& s){

    if (s.empty()) return;

    int topVal = s.top();
    s.pop();

    sortStack(s);

    insertAtCorrectPos(s, topVal);
}

int main(){
    stack<int> s;

    s.push(2);
    s.push(1);
    s.push(3);

    sortStack(s);

    while(!s.empty()){
        cout << s.top() << "\n";
        s.pop();
    }

    return 0;
}