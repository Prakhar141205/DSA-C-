class Solution {
public:
        struct Node {
        long long score = -1;
        vector<int> idxs;
    };
    vector<vector<Node>> t;
    int n;
    vector<int> nextIndex; // preprocess so that no need to use binary search for each index


    Node solve(vector<vector<int>>& intervals, int i, int k) {
        if(i >= n || k <= 0) return Node();
        if(t[i][k].score != -1) return t[i][k];

        Node skip = solve(intervals, i+1, k);
        
        int weight = intervals[i][2];
        int idx = intervals[i][3];
        int j = nextIndex[i];
        Node temp = solve(intervals, j, k-1);

        Node take;
        take.score = temp.score + weight;
        take.idxs = temp.idxs;
        take.idxs.push_back(idx );
        // because we have to return shortest lexicographically incase of score is equal
        sort(begin(take.idxs), end(take.idxs));

        Node result ;
        if(skip.score > take.score) {
            result = skip;
        }else if(skip.score < take.score ) {
            result = take;
        }else {
            // assign the smallest one incase of tie

            result = (take.idxs > skip.idxs) ? skip : take ;
        }

        return t[i][k] = result;
    }
    int getNextIndex(vector<vector<int>>& intervals, int endTime) {
        int r = n-1;
        int res = n;
        int l=0;
        while(l <= r) {
            int m = l + (r-l)/2;

            if(intervals[m][0] > endTime) {
                res = m;
                r = m - 1 ;
            }else {
                l = m + 1;
            }
        }
        return res;
    }
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        n = intervals.size();

        // store the index so that index remain safe 
        for(int i=0; i<n; i++) {
            intervals[i].push_back(i);
        }

        // sort on baiss of start time
        sort(begin(intervals), end(intervals));
        nextIndex.resize(n);

        for(int i=0; i<n; i++) {
            int end = intervals[i][1];
            nextIndex[i] = getNextIndex(intervals, end);
        }

        int k = 4;
        t.assign(n+1, vector<Node> (k+1));

        return solve(intervals, 0, k).idxs ;
       
    }
};

// Bottom Up Approach

class Solution {
public:
        struct Node {
        long long score = -1;
        vector<int> idxs;
    };
    vector<vector<Node>> t;
    int n;
    vector<int> nextIndex; // preprocess so that no need to use binary search for each index


    Node solve(vector<vector<int>>& intervals, int i, int k) {
        if(i >= n || k <= 0) return Node();
        if(t[i][k].score != -1) return t[i][k];

        Node skip = solve(intervals, i+1, k);
        
        int weight = intervals[i][2];
        int idx = intervals[i][3];
        int j = nextIndex[i];
        Node temp = solve(intervals, j, k-1);

        Node take;
        take.score = temp.score + weight;
        take.idxs = temp.idxs;
        take.idxs.push_back(idx );
        // because we have to return shortest lexicographically incase of score is equal
        sort(begin(take.idxs), end(take.idxs));

        Node result ;
        if(skip.score > take.score) {
            result = skip;
        }else if(skip.score < take.score ) {
            result = take;
        }else {
            // assign the smallest one incase of tie

            result = (take.idxs > skip.idxs) ? skip : take ;
        }

        return t[i][k] = result;
    }
    int getNextIndex(vector<vector<int>>& intervals, int endTime) {
        int r = n-1;
        int res = n;
        int l=0;
        while(l <= r) {
            int m = l + (r-l)/2;

            if(intervals[m][0] > endTime) {
                res = m;
                r = m - 1 ;
            }else {
                l = m + 1;
            }
        }
        return res;
    }
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        n = intervals.size();

        // store the index so that index remain safe 
        for(int i=0; i<n; i++) {
            intervals[i].push_back(i);
        }

        // sort on baiss of start time
        sort(begin(intervals), end(intervals));
        nextIndex.resize(n);

        for(int i=0; i<n; i++) {
            int end = intervals[i][1];
            nextIndex[i] = getNextIndex(intervals, end);
        }

        int k = 4;
        t.assign(n+1, vector<Node> (k+1));

        for(int i=n-1; i>=0; i--) {
                
        int weight = intervals[i][2];
        int idx = intervals[i][3];
        int j = nextIndex[i];

        for(int k=1; k<=4; k++) {
            Node skip = t[i+1][k];
            Node temp = t[j][k-1];

            Node take;
            take.score = temp.score + weight;
            take.idxs = temp.idxs;
            take.idxs.push_back(idx );
            // because we have to return shortest lexicographically incase of score is equal
            sort(begin(take.idxs), end(take.idxs));

            Node result ;
            if(skip.score > take.score) {
                result = skip;
            }else if(skip.score < take.score ) {
                result = take;
            }else {
                // assign the smallest one incase of tie

                result = (take.idxs > skip.idxs) ? skip : take ;
            }

            t[i][k] = result;
        }
        }

        return t[0][k].idxs;
    }
};

