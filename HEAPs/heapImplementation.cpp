// Implementation of Max heap
#include <iostream>
#include <vector>
using namespace std;

class Heap{
    vector<int> vec; // CBT

public:

    void push(int val){
        // step 1 => push in the vec
        vec.push_back(val);

        // fix the heap
        int childIn = vec.size()-1;
        int parIn = (childIn - 1)/2;
        
        while(parIn >= 0 && vec[childIn] > vec[parIn]){
            swap(vec[childIn], vec[parIn]);
            childIn = parIn;
            parIn = (childIn-1)/2;
        }
    }
    void heapify(int parIn){
        if(parIn >= vec.size()){
            return ;
        }
        int leftChildIn = 2 * parIn + 1;
        int rightChildIn = 2 * parIn + 2;

        int maxIn = parIn;

        if(leftChildIn < vec.size() && vec[leftChildIn] > vec[maxIn] ){
            maxIn = leftChildIn;
        }

        if(rightChildIn < vec.size() && vec[rightChildIn] > vec[maxIn] ){
            maxIn = rightChildIn;
        }

        swap(vec[parIn], vec[maxIn]);

        if(maxIn != parIn){
            heapify(maxIn);
        }
    }
    void pop(){

        swap(vec[0], vec[vec.size()-1]);
        vec.pop_back();
        heapify(0);

    }

    int top(){
        if(empty()) return -1;
        return vec[0];
    }

    bool empty(){
        return vec.size() == 0;
    }
};
int main(){

    Heap heap;

    heap.push(100);
    heap.push(112300);
    heap.push(12100);
    heap.push(1020);

    cout << "Top = " << heap.top()<<"\n";

    heap.pop();

    cout << "Top = " << heap.top()<<"\n";
    
    return 0;
}