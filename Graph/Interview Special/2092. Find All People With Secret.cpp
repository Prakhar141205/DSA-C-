class Solution {
public:
    typedef pair<int, int> P ;
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        map<int, vector<P> > timeMeetings;

        for(auto& meeting : meetings) {
            int t = meeting[2];
            int person1 = meeting[0 ];
            int person2 = meeting[1];

            timeMeetings[t].push_back({person1 , person2}) ;
        }

        vector<bool> knowsSecret(n, false);
        knowsSecret[0] = true;
        knowsSecret[firstPerson] = true;

        for(auto&  it : timeMeetings) {
            int t = it.first;
            vector<P> meets = it.second ;
            unordered_map<int, vector<int>> adj ;
            queue<int> que;
            unordered_set<int> alreadyAdded ;

            for(auto& [person1 , person2] : meets) {

                adj[person1].push_back(person2);
                adj[person2].push_back(person1);
 
                if(knowsSecret[person1] && alreadyAdded.find(person1) == alreadyAdded.end()) {
                    que.push(person1);
                    alreadyAdded.insert(person1);
                    
                } 

                if(knowsSecret[person2] && alreadyAdded.find(person2) == alreadyAdded.end()) {
                    que.push(person2);
                    alreadyAdded.insert(person2) ;

                } 


            }

            while(!que.empty()) {
                int person = que.front();
                que.pop();

                for(auto& nextPerson : adj[person]) {
                    if(knowsSecret[nextPerson] == false) {
                        que.push(nextPerson ) ;
                        knowsSecret[nextPerson] = true;
                    }
                }
            }



        }

        vector<int> result ;

        for(int i=0; i<n; i++) {
            if(knowsSecret[i] == true){
                result.push_back(i);
            }
        }

        return result;
    }
};