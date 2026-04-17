// Implementation of Max heap
#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

class Student{
public:
    string name;

    int marks;

    Student(string name, int marks){
        this-name = name;
        this->marks = marks;
    }

bool operator < (const Student &obj) const{
    return this->marks < obj.marks;
}
};



int main(){
    priority_queue<Student> pq;

    pq.push("aman", 500);
    pq.push("Prakhar", 2500);

    pq.push("Rahul", 1500);

    while(!pq.empty()){
        cout << pq.top() << "\n";
        pq.pop();
    }
    return 0;
}