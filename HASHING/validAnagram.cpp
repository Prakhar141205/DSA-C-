#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;


bool validAnagram(string p, string q){
    if(p.size() != q.size()) return false;
    unordered_map<char, int> m;
    for(int i=0; i<p.size(); i++){
        if(m.count(p[i])){
            m[p[i]]++;
        }else{
            m[p[i]]=1;
        }
    }

    // important step take care of this 
    // we have decrease the frequency and also we have remove the element from the map 
    // if its frequency becomes zero
    for(char x : q ){
        if(m.count(x)){
            m[x]--;
            if(m[x] == 0){
                m.erase(x);
            }
        }else{
            return false;
        }
    }

    return m.size() == 0;
}
int main(){
    string p = "race";
    string q = "care";

    cout << validAnagram(p, q);
    return 0;
}