/*Pseudo code 
for every layer:

    ---------------------------------
    STEP 1 : EXTRACT THE LAYER
    ---------------------------------

    arr = empty vector

    # top row
    for j = left -> right:
        arr.push(grid[top][j])

    # right column
    for i = top+1 -> bottom:
        arr.push(grid[i][right])

    # bottom row
    for j = right-1 -> left:
        arr.push(grid[bottom][j])

    # left column
    for i = bottom-1 -> top+1:
        arr.push(grid[i][left])



    ---------------------------------
    STEP 2 : ROTATE
    ---------------------------------

    len = arr.size()

    r = k % len

    rotated = vector(len)

    for i = 0 -> len-1:

        newIndex = (i-r+len) % len

        rotated[newIndex] = arr[i]



    ---------------------------------
    STEP 3 : PUT BACK
    ---------------------------------

    idx = 0

    # top row
    for j = left -> right:
        grid[top][j] = rotated[idx]
        idx++

    # right column
    for i = top+1 -> bottom:
        grid[i][right] = rotated[idx]
        idx++

    # bottom row
    for j = right-1 -> left:
        grid[bottom][j] = rotated[idx]
        idx++

    # left column
    for i = bottom-1 -> top+1:
        grid[i][left] = rotated[idx]
        idx++



    ---------------------------------
    STEP 4 : MOVE TO INNER LAYER
    ---------------------------------

    top++
    left++
    bottom--
    right--
    
    */
class Solution {
public:
    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
        int n = grid.size();
        int m = grid[0].size();
        
        int srow = 0, scol = 0, erow = n-1, ecol=m-1;

            while(srow < erow && scol < ecol){
            int rot = k % (2*(m+n) - 4);

            while(rot--){
                // top row
                for(int i=scol; i<ecol; ++i){
                    swap(grid[srow][i], grid[srow][i+1]);
                }

               
                // right col
                for(int i=srow; i<erow; ++i){
                    swap(grid[i][ecol], grid[i+1][ecol]);
                    
                }

              
                // bottom row
                for(int i=ecol; i>scol; --i){
                    swap(grid[erow][i], grid[erow][i-1]);
                }

                
                // left col
                for(int i=erow; i>srow+1; --i){
                    swap(grid[i][scol], grid[i-1][scol]);
                }


            }

                
                srow++;
                scol++;
                ecol--;
                erow--;
                m-=2;
                n-=2;
                
            }
    return grid;
        
    }
};

auto init = []() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 'c';
}();

// approach 2
class Solution {
public:
    vector<vector<int>> rotateGrid(vector<vector<int>>& g, int k) {
        int n = g.size(), m = g[0].size();
        for (int t = 0, l = 0, r = m - 1, b = n - 1; t < b && l < r; l++, r--, t++, b--) {
            int perim = 2 * (r - l + b - t);
            int shift = k % perim;
            while (shift--) {
                int temp = g[t][l];
                for (int j = l; j < r; j++)
                    g[t][j] = g[t][j + 1];
                int temp2 = g[b][l];
                for (int i = b; i > t; i--)
                    g[i][l] = g[i - 1][l];
                g[t + 1][l] = temp;
                int temp3 = g[b][r];
                for (int j = r; j > l; j--)
                    g[b][j] = g[b][j - 1];
                g[b][l + 1] = temp2;
                for (int i = t; i < b; i++)
                    g[i][r] = g[i + 1][r];
                g[b - 1][r] = temp3;
            }
        }
        return g;
    }
};

int layer[196]; 

class Solution {
public:
    static inline void inc(int& id, int p){ id=(id==p-1)?0:id+1; }
    static vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
        const int r=grid.size(), c=grid[0].size(), L=min(r, c)/2;
        
        for(int d=0; d<L; d++){
            const int si=d, sj=d, ei=r-d-1, ej=c-d-1;
            const int h=r-2*d, w=c-2*d; 
            const int p=(h+w-2)*2; // Perimeter for this layer
            
            int id=0;
            // Extract the layer elements
            for(int j=0; j<w-1; j++) 
                layer[id++]=grid[si][sj+j];
            for(int i=0; i<h-1; i++) 
                layer[id++]=grid[si+i][ej];
            for(int j=0; j<w-1; j++) 
                layer[id++]=grid[ei][ej-j];
            for(int i=0; i<h-1; i++) 
                layer[id++]=grid[ei-i][sj];

            // Rotate
            id=k%p;

            for(int j=0; j<w-1; j++) 
                grid[si][sj+j]=layer[id], inc(id, p);
            for(int i=0; i<h-1; i++) 
                grid[si+i][ej]=layer[id], inc(id, p);
            for(int j=0; j<w-1; j++) 
                grid[ei][ej-j]=layer[id], inc(id, p);
            for(int i=0; i<h-1; i++) 
                grid[ei-i][sj]=layer[id], inc(id, p);
        }
        return grid;
    }
};

auto init = []() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 'c';
}();

class Solution {
public:
    void cyclicRead(vector<vector<int>> const & grid, int r, int c, int m, int n, vector<int> & arr) {
        arr.reserve(m*n);
        for (int j = c; j < c + n - 1; j++) arr.push_back(grid[r][j]);
        for (int i = r; i < r + m - 1; i++) arr.push_back(grid[i][c+n-1]);
        for (int j = c+n-1; j > c; j--) arr.push_back(grid[r+m-1][j]);
        for (int i = r+m-1; i > r; i--) arr.push_back(grid[i][c]);
    } 

    void cyclicWrite(vector<vector<int>> & grid, int r, int c, int m, int n, vector<int> const & arr, int k) {
        int idx = k; // index of arr
        int sz = arr.size(); 
        for (int j = c; j < c + n - 1; j++, idx++) grid[r][j] = arr[idx % sz];
        for (int i = r; i < r + m - 1; i++, idx++) grid[i][c+n-1] = arr[idx % sz]; 
        for (int j = c+n-1; j > c; j--, idx++) grid[r+m-1][j] = arr[idx % sz]; 
        for (int i = r+m-1; i > r; i--, idx++) grid[i][c] = arr[idx % sz]; 
    } 

    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        int layers = min(m,n) >> 1;
        // cout << "layers: " << layers << endl;
        for (int l = 0; l < layers; l++) {
            int sz = 2 * (m - l*2) + 2 * (n - l*2 - 2);
            // cout << "sz: " << sz << endl;
            int r = k % sz;
            if (!r) continue;
            vector<int> arr;
            cyclicRead(grid, l, l, m-2*l, n-2*l, arr);
            // for (int const & num: arr) cout << num << " ";
            // cout << endl;
            cyclicWrite(grid, l, l, m-2*l, n-2*l, arr, r);
        }
        return grid;
    }
};