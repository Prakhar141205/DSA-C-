class Solution {
public:
    int n;
    int  mod=  1e9+7;

    int getIntFromChar(char ch) {

        return ch != 'S' ? ch - '0' : 0 ;
    }

    bool isValid(int i, int j, vector<string> board) {
        return i >=0 && i < n && j >=0 && j < n && board[i][j] != 'X';
    }

    pair<int, int> solve(int i, int j, vector<string>& board) {
        if(board[i][j] == 'E') return {0, 1}; // score=0,  path=1
        if(board[i][j] == 'X') return {0, 0}; // score = 0. paths = 0

        int upScore = 0, upPaths = 0;
        int leftScore = 0, leftPaths = 0;
        int diagScore = 0, diagPaths = 0;

        char ch = board[i][j];

        if(isValid(i-1, j, board)) { // up
            auto [score, paths] = solve(i-1, j, board);
            upScore = score;
            upPaths = paths;

            if(upPaths > 0) {
                upScore += getIntFromChar(ch);
            }
        }
        if(isValid(i, j-1, board)) { // left
            auto [score, paths] = solve(i, j-1, board);
            leftScore = score;
            leftPaths = paths;

            if(leftPaths > 0) {
                leftScore += getIntFromChar(ch);
            }
        }
        if(isValid(i-1, j-1, board)) { // diagonal ==> up-left
            auto [score, paths] = solve(i-1, j-1, board);
            diagScore = score;
            diagPaths = paths;

            if(diagPaths > 0) {
                diagScore += getIntFromChar(ch);
            }
        }

        int bestScore, bestPaths;

        if(upScore == leftScore && leftScore == diagScore ) {
            bestScore = upScore;
            bestPaths = upPaths + leftPaths + diagPaths;
        }else if (upScore == leftScore) {
            bestScore = upScore;
            bestPaths = upPaths + leftPaths;   

            if(diagScore > bestScore || (diagScore == bestScore && diagPaths > bestPaths)) {
                bestScore = diagScore;
                bestPaths = diagPaths;

            }        
        }else if (diagScore == leftScore) {
            bestScore = leftScore;
            bestPaths = diagPaths + leftPaths;   

            if(upScore > bestScore || (upScore == bestScore && upPaths > bestPaths)) {
                bestScore = upScore;
                bestPaths = upPaths;
                
            }        
        }else {
            bestScore = upScore ;
            bestPaths = upPaths;
            if(leftScore > bestScore || (leftScore == bestScore && leftPaths > bestPaths)) {
                bestScore = leftScore ;
                bestPaths = leftPaths;
            }
            if(diagScore > bestScore || (diagScore == bestScore && diagPaths > bestPaths)) {
                bestScore = diagScore ;
                bestPaths = diagPaths;
            }
        }

        return {bestScore, bestPaths % mod};
    }
    vector<int> pathsWithMaxScore(vector<string>& board) {
         n = board.size();

         pair<int, int> result = solve(n-1, n-1, board);

         return {result.first, result.second};
        
    }
};


// Memoization

class Solution {
public:
    int n;
    int  mod=  1e9+7;
    pair<int, int> dp[101][101] ;
    int getIntFromChar(char ch) {

        return ch != 'S' ? ch - '0' : 0 ;
    }

    bool isValid(int i, int j, vector<string> board) {
        return i >=0 && i < n && j >=0 && j < n && board[i][j] != 'X';
    }

    pair<int, int> solve(int i, int j, vector<string>& board) {
        if(board[i][j] == 'E') return {0, 1}; // score=0,  path=1
        if(board[i][j] == 'X') return {0, 0}; // score = 0. paths = 0


        if(dp[i][j] != make_pair(-1, -1) ) return dp[i][j];

        int upScore = 0, upPaths = 0;
        int leftScore = 0, leftPaths = 0;
        int diagScore = 0, diagPaths = 0;

        char ch = board[i][j];

        if(isValid(i-1, j, board)) { // up
            auto [score, paths] = solve(i-1, j, board);
            upScore = score;
            upPaths = paths;

            if(upPaths > 0) {
                upScore += getIntFromChar(ch);
            }
        }
        if(isValid(i, j-1, board)) { // left
            auto [score, paths] = solve(i, j-1, board);
            leftScore = score;
            leftPaths = paths;

            if(leftPaths > 0) {
                leftScore += getIntFromChar(ch);
            }
        }
        if(isValid(i-1, j-1, board)) { // diagonal ==> up-left
            auto [score, paths] = solve(i-1, j-1, board);
            diagScore = score;
            diagPaths = paths;

            if(diagPaths > 0) {
                diagScore += getIntFromChar(ch);
            }
        }

        int bestScore, bestPaths;

        if(upScore == leftScore && leftScore == diagScore ) {
            bestScore = upScore;
            bestPaths = upPaths + leftPaths + diagPaths;
        }else if (upScore == leftScore) {
            bestScore = upScore;
            bestPaths = upPaths + leftPaths;   

            if(diagScore > bestScore || (diagScore == bestScore && diagPaths > bestPaths)) {
                bestScore = diagScore;
                bestPaths = diagPaths;

            }        
        }else if (diagScore == leftScore) {
            bestScore = leftScore;
            bestPaths = diagPaths + leftPaths;   

            if(upScore > bestScore || (upScore == bestScore && upPaths > bestPaths)) {
                bestScore = upScore;
                bestPaths = upPaths;
                
            }        
        }else {
            bestScore = upScore ;
            bestPaths = upPaths;
            if(leftScore > bestScore || (leftScore == bestScore && leftPaths > bestPaths)) {
                bestScore = leftScore ;
                bestPaths = leftPaths;
            }
            if(diagScore > bestScore || (diagScore == bestScore && diagPaths > bestPaths)) {
                bestScore = diagScore ;
                bestPaths = diagPaths;
            }
        }

        return dp[i][j] = {bestScore, bestPaths % mod};
    }
    vector<int> pathsWithMaxScore(vector<string>& board) {
         n = board.size();
        memset(dp, -1, sizeof(dp));
        pair<int, int> result = solve(n-1, n-1, board);
         
         return {result.first, result.second};
        
    }  
};

// bottom up approach


class Solution {
public:
    int n;
    int  mod=  1e9+7;
    int getIntFromChar(char ch) {       
        return ch != 'S' ? ch - '0' : 0 ;
    }   

    bool isValid(int i, int j, vector<string> board) {
        return i >=0 && i < n && j >=0 && j < n && board[i][j] != 'X';
    }

    vector<int> pathsWithMaxScore(vector<string>& board) {
        n = board.size();
        vector<vector<pair<int, int>>> dp(n, vector<pair<int, int>>(n, {0, 0}));
        dp[0][0] = {0, 1};

        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                if(i==0 && j==0) continue;
                if(board[i][j] == 'X') continue;

                int upScore = 0, upPaths = 0;
                int leftScore = 0, leftPaths = 0;
                int diagScore = 0, diagPaths = 0;

                char ch = board[i][j];

                if(isValid(i-1, j, board)) { // up
                    auto [score, paths] = dp[i-1][j];
                    upScore = score;
                    upPaths = paths;

                    if(upPaths > 0) {
                        upScore += getIntFromChar(ch);
                    }
                }
                if(isValid(i, j-1, board)) { // left
                    auto [score, paths] = dp[i][j-1];
                    leftScore = score;
                    leftPaths = paths;

                    if(leftPaths > 0) {
                        leftScore += getIntFromChar(ch);
                    }
                }
                if(isValid(i-1, j-1, board)) { // diagonal ==> up-left
                    auto [score, paths] = dp[i-1][j-1];
                    diagScore = score;
                    diagPaths = paths;

                    if(diagPaths > 0) {
                        diagScore += getIntFromChar(ch);
                    }
                }

                int bestScore, bestPaths;

                if(upScore == leftScore && leftScore == diagScore ) {
                    bestScore = upScore;
                    bestPaths = upPaths + leftPaths + diagPaths;
                }else if (upScore == leftScore) {
                    bestScore = upScore;
                    bestPaths = upPaths + leftPaths;   

                    if(diagScore > bestScore || (diagScore == bestScore && diagPaths > bestPaths)) {
                        bestScore = diagScore;
                        bestPaths = diagPaths;

                    }        
                }else if (diagScore == leftScore) {
                    bestScore = leftScore;
                    bestPaths = diagPaths + leftPaths;  

                    if(upScore > bestScore || (upScore == bestScore && upPaths > bestPaths)) {
                        bestScore = upScore;
                        bestPaths = upPaths;

                    }       
                }else {
                    bestScore = upScore ;
                    bestPaths = upPaths;
                    if(leftScore > bestScore || (leftScore == bestScore && leftPaths > bestPaths)) {
                        bestScore = leftScore ;
                        bestPaths = leftPaths;
                    }
                    if(diagScore > bestScore || (diagScore == bestScore && diagPaths > bestPaths)) {
                        bestScore = diagScore ;
                        bestPaths = diagPaths;
                    }
                }
                dp[i][j] = {bestScore, bestPaths%mod};   
            }
        }
            pair<int, int> res = dp[n-1][n-1];

            return  { res.first, res.second % mod};
        }
    };