// whenver you have to convert one string to another string by changing one character at a time and each intermediate string should be present in the given bank of strings then you can use BFS to find the minimum number of steps required to convert the start string to the end string.


class Solution {
public:
    int minMutation(string startGene, string endGene, vector<string>& bank) {
        unordered_set<string> bankSet(bank.begin(), bank.end());

        unordered_set<string> vis;
        int level = 0;
        vis.insert(startGene);
        queue<string> que;
        que.push(startGene) ;

        while(!que.empty()) {
            int n = que.size();

            while(n--) {
                string curr = que.front();
                que.pop();

                if(curr == endGene) {
                    return level;
                }

                for(char ch : "ACGT") {
                
                for(int i=0; i<curr.length(); i++) {
                    string ngbr = curr;
                    ngbr[i] = ch ;

                    if(vis.find(ngbr) == vis.end() && 
                        bankSet.find(ngbr) != bankSet.end()) {
                            vis.insert(ngbr);
                            que.push(ngbr);

                        }

                }
            }
            }

            level++;
        }

        return -1;
        
    }
};