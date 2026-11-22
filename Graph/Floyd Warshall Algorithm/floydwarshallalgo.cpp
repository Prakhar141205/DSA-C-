geeksforgeeks
Search...
Courses
Tutorials
Practice
Jobs

P



Refresh

Time (IST)	Status	Marks	Lang	Test Cases	Code
2026-11-22 15:38:20	Wrong	
0
cpp	99 / 1120	View
2026-11-22 15:37:22	Wrong	
0
cpp	0 / 1120	View
2026-08-05 12:17:50	Correct	
4
cpp	1120 / 1120	View
2026-08-05 12:15:00	Wrong	
0
cpp	0 / 1120	View
Output Window
Problem Solved Successfully
Suggest Feedback
No marks added for this submission as you have already solved this problem. For more details, check the "Submissions" tab.
Test Cases Passed
1120 / 1120
Attempts : Correct / Total
2 / 5
Accuracy :
40%
Time Taken
0.09
Don't risk your placements! Get interview-ready with GfG Placement 360. Flat 30% OFF - Limited Time!

banner
C++ (17)



                    if(grid[i][via] == 1e8 or grid[via][j] == 1e8) continue;



Custom Input
class Solution {
  public:
    void floydWarshall(vector<vector<int>> &dist) {
        int n = dist.size() ;
        
        for(int via=0; via < n; via++) {
            for(int u = 0; u<n; u++) {
                for(int v=0; v <n; v++) {
                    if(dist[u][via] == 1e8 || dist[via][v] == 1e8 ) continue ;
                    int newDist = dist[u][via] + dist[via][v] ;
                   
                    dist[u][v] = min(dist[u][v], newDist) ;
                }
            }
        }
        
    }
};