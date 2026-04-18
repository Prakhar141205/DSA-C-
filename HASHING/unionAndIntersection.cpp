#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// print union of two sets using unordered_set

vector<int> printUnion(vector<int> s1, vector<int> s2){

    unordered_set<int> s;
    vector<int> un;
    for(int x : s1 ){
        s.insert(x);
    }

    for(int x : s2 ){
        s.insert(x);
    }

    for(int x : s){
        un.push_back(x);

    }
        return un;
    }

// print intersection of two sets using unordered_set 
// Warning think of erasing the element once from the  map or the set
vector<int> printIntersection(vector<int> s1, vector<int> s2){
    unordered_set<int> s;
    vector<int> inter;
    for(int x : s1){
        s.push_back(x);
    }
    for(int x : s2){
        if(s.find(x) != s.end()){
            inter.push_back(x);
            s.erase(x);
        }
    }
    return inter;
}
int main(){
    vector<int> s1 = {1, 3, 4, 5};
    vector<int> s2 = {1,2, 3 ,4};

    vector<int> result = printUnion(s1, s2);

    for(int x : result){
        cout << x << " ";
    }
    return 0;
}