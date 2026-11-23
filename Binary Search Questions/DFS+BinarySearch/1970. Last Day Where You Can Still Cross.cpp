class Solution {
public:
    int ROW, COL;

    // Four possible movement directions:
    // Down, Up, Right, Left
    vector<vector<int>> directions{
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };

    bool dfs(vector<vector<int>>& grid, int i, int j) {

        // Boundary check:
        // Return false if we go outside the grid
        // or reach a water cell.
        if (i < 0 || i >= ROW || j < 0 || j >= COL ||
            grid[i][j] == 1) {
            return false;
        }

        // If we reach the last row, crossing is possible.
        if (i == ROW - 1) {
            return true;
        }

        // Mark the current land cell as visited
        // to avoid revisiting it and getting stuck in cycles.
        grid[i][j] = 1;

        // Explore all four neighboring cells.
        for (vector<int>& dir : directions) {

            int new_i = i + dir[0];
            int new_j = j + dir[1];

            if (dfs(grid, new_i, new_j)) {
                return true;
            }
        }

        // No path to the bottom row was found.
        return false;
    }

    // Checks whether crossing is possible after 'day' days.
    bool canCross(vector<vector<int>>& cells, int day) {

        // Initially, consider every cell as land (0).
        // Water cells will be marked as 1.
        vector<vector<int>> grid(ROW, vector<int>(COL, 0));

        // Flood all cells that become water
        // from day 0 to day 'day' (inclusive).
        for (int i = 0; i <= day; i++) {

            int r = cells[i][0] - 1;
            int c = cells[i][1] - 1;

            grid[r][c] = 1;
        }

        // We can start crossing from any land cell
        // in the first row.
        for (int j = 0; j < COL; j++) {

            if (grid[0][j] == 0 && dfs(grid, 0, j)) {
                return true;
            }
        }

        return false;
    }

    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {

        ROW = row;
        COL = col;

        int n = cells.size();

        // Binary search over the number of flooded days.
        int l = 0;
        int r = n - 1;

        int lastDay = 0;

        while (l <= r) {

            int mid = l + (r - l) / 2;

            // mid represents a zero-based day index.
            // Therefore, canCross checks mid + 1 flooded days.
            if (canCross(cells, mid)) {

                // Crossing is possible.
                // Store the corresponding number of days.
                lastDay = mid + 1;

                // Try a later day to maximize the answer.
                l = mid + 1;

            } else {

                // Crossing is impossible.
                // Try an earlier day.
                r = mid - 1;
            }
        }

        return lastDay;
    }
};



class Solution {
public:
    int ROW, COL;

    // Four possible movement directions:
    // Down, Up, Right, Left
    vector<vector<int>> directions{
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };

    bool bfs(vector<vector<int>>& grid, int i, int j) {

        // Queue stores the coordinates of cells to explore.
        queue<pair<int, int>> que;

        // Start BFS from the given top-row cell.
        que.push({i, j});

        // Mark the starting cell as visited.
        grid[i][j] = 1;

        while (!que.empty()) {

            // Get the front cell and remove it from the queue.
            auto temp = que.front();
            que.pop();

            int x = temp.first;
            int y = temp.second;

            // If we reach the last row, crossing is possible.
            if (x == ROW - 1) {
                return true;
            }

            // Explore all four neighboring cells.
            for (vector<int>& dir : directions) {

                int new_x = x + dir[0];
                int new_y = y + dir[1];

                // Check:
                // 1. New coordinates are within grid boundaries.
                // 2. The neighboring cell is land (0).
                // 3. The cell has not been visited.
                if (new_x >= 0 && new_x < ROW &&
                    new_y >= 0 && new_y < COL &&
                    grid[new_x][new_y] == 0) {

                    // Add the valid neighboring cell to the queue.
                    que.push({new_x, new_y});

                    // Mark it visited immediately to avoid
                    // inserting the same cell multiple times.
                    grid[new_x][new_y] = 1;
                }
            }
        }

        // No path from the top row to the bottom row exists.
        return false;
    }

    // Checks whether crossing is possible after 'day' days.
    bool canCross(vector<vector<int>>& cells, int day) {

        // Initially, all cells are land (0).
        vector<vector<int>> grid(ROW, vector<int>(COL, 0));

        // Mark all flooded cells up to the given day.
        for (int i = 0; i <= day; i++) {

            int r = cells[i][0] - 1;
            int c = cells[i][1] - 1;

            grid[r][c] = 1;
        }

        // Start BFS from every available land cell in the first row.
        for (int j = 0; j < COL; j++) {

            if (grid[0][j] == 0 && bfs(grid, 0, j)) {
                return true;
            }
        }

        return false;
    }

    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {

        ROW = row;
        COL = col;

        int n = cells.size();

        // Binary search over all possible flooded days.
        int l = 0;
        int r = n - 1;

        int lastDay = 0;

        while (l <= r) {

            int mid = l + (r - l) / 2;

            // Check whether crossing is possible after mid + 1 days.
            if (canCross(cells, mid)) {

                // Current day is valid.
                lastDay = mid + 1;

                // Search for a later valid day.
                l = mid + 1;

            } else {

                // Current day is invalid.
                // Search for an earlier valid day.
                r = mid - 1;
            }
        }

        return lastDay;
    }
};


class Solution {
public:
    vector<int> parent;
    vector<int> size;

    // Find the ultimate parent of a node.
    // Path compression optimizes future find operations.
    int find(int x) {

        if (parent[x] == x) {
            return x;
        }

        return parent[x] = find(parent[x]);
    }

    // Merge two connected components using Union by Size.
    void Union(int x, int y) {

        int px = find(x);
        int py = find(y);

        // Already belong to the same component.
        if (px == py) {
            return;
        }

        // Attach the smaller component to the larger component.
        if (size[px] < size[py]) {
            swap(px, py);
        }

        parent[py] = px;
        size[px] += size[py];
    }

    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {

        int n = row * col;

        // Two extra nodes represent the virtual top and bottom.
        int TOP = n;
        int BOTTOM = n + 1;

        // Initialize DSU.
        parent.resize(n + 2);
        size.assign(n + 2, 1);

        for (int i = 0; i < n + 2; i++) {
            parent[i] = i;
        }

        // Initially, all cells are water (inactive).
        vector<vector<int>> grid(row, vector<int>(col, 0));

        // Four neighboring directions.
        vector<vector<int>> directions{
            {1, 0}, {-1, 0}, {0, 1}, {0, -1}
        };

        // Reverse the flooding process.
        // Start from the last day and move towards day 0.
        for (int i = n - 1; i >= 0; i--) {

            // Convert the current water cell back into land.
            int r = cells[i][0] - 1;
            int c = cells[i][1] - 1;

            grid[r][c] = 1;

            // Convert 2D coordinates into a 1D DSU index.
            int curr = r * col + c;

            // If the current cell belongs to the first row,
            // connect it to the virtual TOP node.
            if (r == 0) {
                Union(curr, TOP);
            }

            // If the current cell belongs to the last row,
            // connect it to the virtual BOTTOM node.
            if (r == row - 1) {
                Union(curr, BOTTOM);
            }

            // Connect the current land cell with all
            // its neighboring land cells.
            for (vector<int>& dir : directions) {

                int new_r = r + dir[0];
                int new_c = c + dir[1];

                // Check grid boundaries and whether
                // the neighboring cell is already land.
                if (new_r >= 0 && new_r < row &&
                    new_c >= 0 && new_c < col &&
                    grid[new_r][new_c] == 1) {

                    int neighbor = new_r * col + new_c;

                    // Merge the two connected components.
                    Union(curr, neighbor);
                }
            }

            // Check whether the TOP and BOTTOM virtual nodes
            // belong to the same connected component.
            if (find(TOP) == find(BOTTOM)) {

                // Crossing becomes possible after i days.
                return i;
            }
        }

        return 0;
    }
};