class Solution {
public:
    bool rotateString(string s, string goal) {
        if (s.length() != goal.length()) return false;
        if (s == goal) return true;
        
        for (int i = 1; i < s.length(); i++) {
            string rotated = s.substr(i) + s.substr(0, i);
            if (rotated == goal) return true;
        }
        return false;
    }
};


#include <string>

using namespace std;

class Solution {
public:
    bool rotateString(string s, string goal) {
        if (s.length() != goal.length()) {
            return false;
        }
        
        string doubled = s + s;
        return doubled.find(goal) != string::npos;
    }
};


class Solution {
public:
    bool rotateString(string s, string goal) {
        if(size(s) != size(goal)){
            return false;
        }
        if(s==goal){
            return true;
        }
        int i =1,N=size(s);
        string temps="",halfs="",finals="";
        while(i<N){
            temps = s.substr(0,i);
            halfs = s.substr(i,N);
            finals=halfs+temps;
            if(finals == goal){
                return true;
            }
            i++;
        }
        return false;
    }
};