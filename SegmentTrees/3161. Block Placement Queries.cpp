class Solution {
public:
    vector<bool> getResults(vector<vector<int>>& queries) {
        vector<bool> result;
        set<int> st;
        for(auto& query : queries){
            if(query[0] == 1) st.insert(query[1]);
            else {
                int x = query[1];
                int sz = query[2];

                int prev = 0;
                bool found = false;

                for(int curr : st) {
                    if(curr > x) break;
                    if(curr - prev >= sz){
                        found = true;
                        break;
                    }

                    prev = curr;
                 }

                 if(!found) found = (x - prev >= sz);

                 result.push_back(found);
            }
        }
        return result;
    }
};

// using SegmentTree

class Solution {
public:
    vector<int> SegmentTree;
    int n = 50000;

    void constructSegmentTree(){
        SegmentTree.resize(4*n, 0);
    }

    void updateSegmentTree(int idx, int val, int i, int l, int r){
        if(l == r) {
            SegmentTree[i]=val;
            return;
        }

        int mid = l + (r-l)/2;

        if(idx <= mid){
            updateSegmentTree(idx, val, 2*i+1, l, mid);
        }else{
            updateSegmentTree(idx, val, 2*i+2, mid+1, r);
        }

        SegmentTree[i] = max(SegmentTree[2*i+1], SegmentTree[2*i+2]);
    }

    int querySegmentTree(int st, int end, int i, int l, int r){
        if(l > end || r < st) return 0;

        if(l >= st && r <= end) return SegmentTree[i];

        int mid = l + (r-l)/2;

        return max(querySegmentTree(st, end, 2*i+1, l, mid), querySegmentTree(st, end, 2*i+2, mid+1, r));
    }
    vector<bool> getResults(vector<vector<int>>& queries) {
        constructSegmentTree();
        set<int> st; // to hold obstacles
        st.insert(0); // assumed obstacle at 0 

        vector<bool> res;

        for(auto& query : queries){
            if(query[0] == 1){
                int x = query[1];

                auto it = st.upper_bound(x);
                int next = (it != st.end()) ? *it : -1; 
                int pre = *prev(it);

                updateSegmentTree(x, x-pre, 0, 0, n-1);
                if(next != -1) updateSegmentTree(next, next-x, 0, 0, n-1);

                st.insert(x);
            }else{
                int x = query[1];
                int sz = query[2];

                auto it = st.upper_bound(x);

                int pre = *prev(it);

                int maxGap = querySegmentTree(0, pre, 0, 0, n-1);
                int best = max(maxGap, x-pre);

                res.push_back(best >= sz);
            }
        }
        return res;
    }
};