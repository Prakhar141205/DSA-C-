#include <iostream> 
#include <vector>

using namespace std;

class SegmentTreeMax{
    vector<int> tree;
    int n ;

    int rangeQueryMaxHelper(int qi, int qj, int si, int sj, int node){
        // no overlap
        if(sj < qi || qj < si) return 0;
        // complete overlap
        if(si >= qi && sj <= qj) return tree[node];
        // partial overlap
       
            int mid = si + (sj - si)/2;
            int leftMax = rangeQueryMaxHelper(qi, qj, si, mid, 2*node+1);
            int rightMax = rangeQueryMaxHelper(qi, qj, mid+1, sj, 2*node+2);
            return max(leftMax, rightMax);
    }
public:

    SegmentTreeMax(vector<int>& arr){
        n = arr.size();
        tree.resize(4*n, 0);
        buildSegmentTree(arr, 0, n-1, 0);
    }

    void buildSegmentTree(vector<int> arr, int start, int end, int node){
        if(start == end){
            tree[node] = arr[start];
            return;
        }

        int mid = start + (end-start)/2;

        buildSegmentTree(arr, start, mid, 2*node+1);
        buildSegmentTree(arr, mid + 1, end, 2*node+2);

        tree[node] = max(tree[2*node+1], tree[2*node+2]);
    }

    void printTree(){
        for(int x : tree) cout << x << " ";
    }

    int rangeQueryMax(int qi, int qj){
        return rangeQueryMaxHelper(qi, qj, 0, n-1, 0);
    }

};
int main(){

    vector<int> arr = {2, 5, 1, 6, 87, 43, 32};

    SegmentTreeMax segmentTree(arr);

    cout << segmentTree.rangeQueryMax(0, 2);
    return 0;
}