class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();

        // Step 1: Transpose the matrix
        for(int i = 0; i < n; i++)
        {
            for(int j = i + 1; j < n; j++)
            {
                swap(matrix[i][j], matrix[j][i]);
            }
        }

        // Step 2: Reverse each row
        for(int i = 0; i < n; i++)
        {
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};


// using inplace swap using upper triangular matrix

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();

        // inplace swap using upper triangular part of the matrix
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(j > i ){
                    swap(matrix[j][i], matrix[i][j]);
                }
            }
        }


        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
               cout << matrix[i][j]<<" ";
            }
            cout << endl;
        }

        int row=0;
        while(row < n){
            int st = 0, end=m-1;
            while(st <= end){
                swap(matrix[row][st++], matrix[row][end--]);
            }
            row++;
        }

    }
};

// competitive programmming

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        for(int row = 0; row <matrix.size();row++){
            for(int col = row + 1;col < matrix[0].size();col++){
                swap(matrix[row][col],matrix[col][row]);
            }
        }

        for(int row = 0;row < matrix.size();row++){
            reverse(matrix[row].begin(),matrix[row].end());
        }
    }
};

static const bool __boost = []() {
	cin.tie(nullptr);
	cout.tie(nullptr);
	return std::ios_base::sync_with_stdio(false);
	}();

const size_t BUFFER_SIZE = 0x6fafffff;
alignas(std::max_align_t) char buffer[BUFFER_SIZE];
size_t buffer_pos = 0;
void* operator new(size_t size) {
	constexpr std::size_t alignment = alignof(std::max_align_t);
	size_t padding = (alignment - (buffer_pos % alignment)) % alignment;
	size_t total_size = size + padding;
	char* aligned_ptr = &buffer[buffer_pos + padding];
	buffer_pos += total_size;
	return aligned_ptr;
}
void operator delete(void* ptr, unsigned long) {}
void operator delete(void* ptr) {}
void operator delete[](void* ptr) {}


class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        std::reverse(matrix.begin(), matrix.end());
        for(int a = 0; a < n ;a++){
            for(int i = a + 1; i < n; i++){
                swap(matrix[a][i], matrix[i][a]);
        }
    }
    }
};



#pragma GCC optimize("Ofast")

#include <iostream>

static constexpr std::size_t max_align = alignof(std::max_align_t);
alignas(max_align) static unsigned char BUFFER[64 * 1024 * 1024];
static std::size_t pos = 0;

void *operator new(const std::size_t size) {
    const std::size_t padding = (max_align - (pos % max_align)) % max_align;
    pos += padding + size;
    return static_cast<void *>(&BUFFER[pos - size]);
}

void *operator new[](const std::size_t size) {
    return operator new(size);
}

void operator delete(void *) noexcept {}

void operator delete[](void *) noexcept {}

void operator delete(void *, std::size_t) noexcept {}

void operator delete[](void *, std::size_t) noexcept {}
