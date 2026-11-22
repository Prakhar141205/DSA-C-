class Solution {
public:
    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
        int n = pairs.size();
        unordered_map<int, vector<int>> adj;
        unordered_map<int, int> indegree, outdegree ;
        for(auto pair : pairs) {
            int u = pair[0];
            int v = pair[1];

            adj[u].push_back(v);
            indegree[v]++;
            outdegree[u]++;
        }

        int startNode = pairs[0][0] ;

        for(auto [node, _] : adj) {
 
            if(outdegree[node] - indegree[node] == 1) {
                startNode = node;
                break;
            }
        }

        vector<int> eulerPath;
        stack<int> st;
        st.push(startNode);

        while(!st.empty()) {
            int curr = st.top();

            if(!adj[curr].empty()) {
                int ngbr = adj[curr].back();
                adj[curr].pop_back();
                st.push(ngbr);
                
            }else {
                eulerPath.push_back(curr);
                st.pop();
            }
        }
        
        reverse(eulerPath.begin(), eulerPath.end());
        for(int x : eulerPath) cout << x <<" ";
        vector<vector<int>> ans;
        for(int i=0; i<eulerPath.size()-1; i++) {
            vector<int> temp = {eulerPath[i], eulerPath[i+1]} ;
            ans.push_back(temp);
        }

        return ans ;
    }
};