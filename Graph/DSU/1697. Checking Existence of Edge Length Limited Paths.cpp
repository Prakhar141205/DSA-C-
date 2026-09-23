class Solution {
public:
    vector<int> parent;
    vector<int> rank;
    int find(int x) {
        if(x == parent[x]) return x;

        return parent[x] = find(parent[x]);
    }

    void Union(int x, int y) {
        int par_x = find(x);
        int par_y = find(y);

        if(rank[par_x] > rank[par_y]) {
            parent[par_y] = par_x;
        }else if(rank[par_y] > rank[par_x]) {
            parent[par_x] = par_y;
        }else {
            parent[par_x] = par_y;
            rank[par_y] += 1;
        }
    }
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        parent.resize(n, 0);
        rank.resize(n);

        for(int i=0; i<n; i++) {
            parent[i] = i;
            rank[i] = 1 ;
        }


        for(int i=0; i<queries.size(); i++) {
            queries[i].push_back(i);
        }

        auto lambda = [&](auto& v1 , auto& v2) {
            return v1[2] < v2[2] ;
        };

        sort(begin(edgeList), end(edgeList), lambda);
        sort(begin(queries), end(queries), lambda);


        vector<bool> result(queries.size());
        int j=0;

        for(auto& query : queries) {
            int u = query[0];
            int v = query[1];
            int w = query[2];
            int idx = query[3];

            while(j < edgeList.size() && edgeList[j][2] < w) {
                Union(edgeList[j][0], edgeList[j][1]);
                j++;
            }

            result[idx] = find(u) == find(v);
        }

        return result;
    }
};