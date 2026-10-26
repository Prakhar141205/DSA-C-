class Solution {
public:
    bool possibleInGivenTime(vector<int>& time, long long givenTime, int totalTrips) {
        long long ans = 0;

        for (int i = 0; i < time.size(); i++) {
            ans += (givenTime / time[i]);

            if (ans >= totalTrips) {
                return true;
            }
        }

        return false;
    }

    long long minimumTime(vector<int>& time, int totalTrips) {
        long long l = 1;
        long long r = (long long)totalTrips *
                      (*min_element(time.begin(), time.end()));

        while (l < r) {
            long long mid = l + (r - l) / 2;

            if (possibleInGivenTime(time, mid, totalTrips)) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }

        return l;
    }
};