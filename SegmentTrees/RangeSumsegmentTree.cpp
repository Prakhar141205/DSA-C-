#include <iostream>
#include <vector>

using namespace std;

class SegmentTree{
    vector<int> tree;
    int n;
    void buildTree(vector<int> &arr, int st, int end, int node){
        if(st == end ) {tree[node]=arr[st]; return;}
        int mid = st + (end-st)/2;
        buildTree(arr, st, mid, 2*node+1);
        buildTree(arr, mid+1, end, 2*node+2);

        tree[node] = tree[2*node+1] + tree[2*node+2];
    }

    int rangeQuerySumHelper(int qi, int qj, int si, int sj, int node){

        // no overlap case
        if(qi > sj || qj < si) return 0;

        if(si >= qi && sj <= qj){ // complete overlap
            return tree[node];
        }else{ // partial overlap
            int mid = si + (sj - si)/2;

            int leftSum = rangeQuerySumHelper(qi, qj, si, mid, 2*node+1);
            int rightSum = rangeQuerySumHelper(qi, qj, mid+1, sj, 2*node+2);
            return leftSum + rightSum;
        }
    } 

    void updateQueryHelper(int idx, int newVal, int si, int sj, int node){
        if(si == sj){
            tree[node] = newVal;
            return ;
        }

        int mid = si + (sj-si)/2;
        if(si <= idx && idx <= mid){
            updateQueryHelper(idx, newVal, si, mid, 2*node+1);
        }else{
            updateQueryHelper(idx, newVal, mid+1, sj, 2*node+2);
        }

        tree[node] = tree[2*node+1] + tree[2*node+2];
    }

public:
    SegmentTree(vector<int>& arr){
        n = arr.size();
        tree.resize(4*n);
        buildTree(arr, 0, n-1, 0);
    }

    void printTree(){
        for(int x : tree) cout << x << " ";
    }

    int rangeQuerySum(int qi, int qj){  // o(log n)
        return rangeQuerySumHelper(qi, qj, 0, n-1, 0);
    }

    void updateQuery(int idx, int  newVal){
         updateQueryHelper(idx, newVal, 0, n-1, 0);
    }
};
int main(){
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8};

    SegmentTree segmentTree(arr);
    cout << segmentTree.rangeQuerySum(0, 4) << "\n";

    segmentTree.updateQuery(2, 5);
    cout << segmentTree.rangeQuerySum(0, 4) << "\n";
    return 0;
}