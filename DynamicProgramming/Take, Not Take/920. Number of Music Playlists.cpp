class Solution {
public:
    int N, GOAL, K ;
    const int mod = 1e9+7 ;

    int t[101][101] ;
    int solve(int cnt_songs, int cnt_unique) {
        if(cnt_songs == GOAL ) {
            return cnt_unique == N ; // as we have to play all the songs at least once
        }
        if(t[cnt_songs][cnt_unique] != -1) return t[cnt_songs][cnt_unique] ;
        long res = 0;
        if (N-cnt_unique >= 0)
            res = (res + (1LL * (N-cnt_unique) % mod * solve(cnt_songs+1, cnt_unique+1) % mod )) % mod ;
        if(cnt_unique - K >= 0)
            res = (res + (1LL * (cnt_unique - K) % mod * solve(cnt_songs+1, cnt_unique) % mod )) % mod ;
        return t[cnt_songs][cnt_unique] = res ;
    }
    int numMusicPlaylists(int n, int goal, int k) {
        N = n;
        GOAL = goal;
        K = k;
        memset(t, -1, sizeof(t)) ;
        return solve(0, 0);  
    }
};