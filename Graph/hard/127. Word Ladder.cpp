class Solution {
public:
  
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        
        queue<pair<string, int>> que ;
        que.push({beginWord, 1});

        unordered_set<string> vis(wordList.begin(), wordList.end()) ;
        vis.erase(beginWord);

        while(!que.empty()) {
            auto [start, lev] = que.front();
            que.pop();

            if(start == endWord) return lev ;

            for(int i=0; i<start.length(); i++) {
                char original = start[i];

                for(char c = 'a'; c <= 'z'; c++) {
                    start[i] = c ;
                    if(vis.find(start) != vis.end()) {
                        vis.erase(start);
                        que.push({start, lev+1}) ;
                    }


                }

                start[i] = original ;
            }
        }

        return 0;
    }
};