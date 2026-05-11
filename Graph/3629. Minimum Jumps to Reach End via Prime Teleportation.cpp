class Solution {
public:

    vector<bool> isPrime;

    void buildSieve(int maxEl){
        isPrime.resize(maxEl+1, true);
        isPrime[0] = false;
        isPrime[1] = false;

        for(int num=2; num*num<=maxEl; num++){
            if (isPrime[num]){
                for(int mul = num*num; mul<=maxEl; mul+=num){
                    isPrime[mul] =  false;
                }
            }
        }
        }
    int minJumps(vector<int>& nums) {
        int n =nums.size();
        unordered_map<int, vector<int>> mp;  // element => indices
        int maxEl = 0;

        for(int i=0;  i<n; i++){
            mp[nums[i]].push_back(i);
            maxEl = max(maxEl, nums[i]);
        }

        // build the vector of prime number 
        buildSieve(maxEl);

        // BFS
        queue<int> q;
        vector<bool> vis(n, false);
        q.push(0);
        vis[0] = true;

        unordered_set<int> st; // contain the seen element 
        int steps =0 ;

        while(!q.empty()){
            int size = q.size();
            while(size--){
                int i = q.front();
                q.pop();

                if(i == n-1) return steps; // get the answer

                // process the left neighbour
                if(i-1 >= 0 && !vis[i-1]){
                    q.push(i-1);
                    vis[i-1] = true;
                }

                // process the right neighbour
                if(i+1 <= n-1  && !vis[i+1]){
                    q.push(i+1);
                    vis[i+1] = true;
                }

                // process the prime steps teleport destination 

                if(!isPrime[nums[i]] || st.count(nums[i])){ // number is not prime or it is seen once
                    continue;
                } 


                for(int multiple = nums[i]; multiple<=maxEl; multiple += nums[i]){
                    if(!mp.contains(multiple)) continue;


                    for(int &j : mp[multiple]){
                            if(!vis[j]){
                                q.push(j);
                                vis[j]=true;
                            }
                    }
                }

                st.insert(nums[i]);
            }

            steps++;
        }       
        
        return steps;
    }
};


const int MAX_VAL = 1e6;
vector<bool> isPrime(MAX_VAL + 1, true);
bool isFilled = false;

class Solution {
public:
    void fill() {
        if (isFilled) return;
        isPrime[0] = isPrime[1] = false;
        for (int i = 2; i * i <= MAX_VAL; ++i) {
            if (isPrime[i]) {
                for (int j = i * i; j <= MAX_VAL; j += i)
                    isPrime[j] = false;
            }
        }
        isFilled = true;
    }

    int minJumps(vector<int>& nums) {
        fill();
        int n = nums.size();
        if (n <= 1) return 0;

        int maxi = *max_element(nums.begin(), nums.end());
        unordered_map<int, vector<int>> mp;
        for (int i = 0; i < n; i++) {
            mp[nums[i]].push_back(i);
        }

        vector<int> dist(n, -1);
        queue<int> qu;
        unordered_set<int> visitedPrime;

        qu.push(0);
        dist[0] = 0;

        while (!qu.empty()) {
            int curr = qu.front();
            qu.pop();

            if (curr == n - 1) return dist[curr];

            // 1. Move Left
            if (curr - 1 >= 0 && dist[curr - 1] == -1) {
                dist[curr - 1] = dist[curr] + 1;
                qu.push(curr - 1);
            }

            // 2. Move Right
            if (curr + 1 < n && dist[curr + 1] == -1) {
                dist[curr + 1] = dist[curr] + 1;
                qu.push(curr + 1);
            }

            // 3. Jump via Multiples (Only if nums[curr] is Prime)
            int val = nums[curr];
            if (val > 1 && isPrime[val] && !visitedPrime.count(val)) {
                // For a prime p, jump to all indices of multiples: p, 2p, 3p...
                for (int multiple = val; multiple <= maxi; multiple += val) {
                    if (mp.count(multiple)) {
                        for (int idx : mp[multiple]) {
                            if (dist[idx] == -1) {
                                dist[idx] = dist[curr] + 1;
                                if (idx == n - 1) return dist[idx];
                                qu.push(idx);
                            }
                        }
                        // Efficiency: Once we process a multiple's indices, clear it
                        mp.erase(multiple); 
                    }
                }
                visitedPrime.insert(val);
            }
        }

        return dist[n - 1];
    }
};