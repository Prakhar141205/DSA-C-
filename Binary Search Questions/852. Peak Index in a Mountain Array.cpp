class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {

        int n = arr.size();

        // Initialize binary search boundaries
        int l = 0, r = n - 1;

        while (l <= r) {

            // Calculate the middle index
            int m = l + (r - l) / 2;

            // Check whether the current element is the peak:
            // It must be greater than both its neighbors.
            if (m > 0 && m < n - 1 &&
                arr[m] > arr[m - 1] &&
                arr[m] > arr[m + 1]) {

                return m;
            }

            // If the next element is greater,
            // we are on the increasing slope.
            // Therefore, the peak must be on the right side.
            if (arr[m] < arr[m + 1]) {
                l = m + 1;
            }

            // Otherwise, we are on the decreasing slope
            // or at the peak's right side.
            // Therefore, search on the left side.
            else {
                r = m - 1;
            }
        }

        // Peak not found
        return -1;
    }
};