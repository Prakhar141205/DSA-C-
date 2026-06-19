class Solution {
public:
    bool winnerOfGame(string colors) {

        int n = colors.size();

        int alice_steps = 0;
        int bob_steps = 0;

        for(int i=1; i<n-1; i++){
            if(colors[i] == 'A'){
                if(colors[i-1] == 'A' && colors[i+1] == 'A' ){
                    alice_steps++;
                }

            }else {
                if(colors[i-1] == 'B' && colors[i+1] == 'B'){
                    bob_steps++;
                }
            }
        }

        return alice_steps > bob_steps ? true : false ;
        
    }
};

