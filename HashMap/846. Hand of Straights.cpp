// Approach: Simply using map
// T.C : O(n log n) + O(n * groupSize)
// S.C : O(n)

class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        int n = hand.size();

        // If total cards cannot be divided into groups of groupSize,
        // forming consecutive groups is impossible.
        // T.C : O(1)
        if(n % groupSize) {
            return false;
        }

        // Store card frequency in sorted order.
        // Map maintains keys in ascending order.
        map<int, int> mp;

        // Insert all cards and update their frequencies.
        // Each insertion/update takes O(log n).
        // T.C : O(n log n)
        for(int &handNumber : hand) {
            mp[handNumber]++;
        }

        // Process cards until the map becomes empty.
        // Every card is processed exactly once.
        // T.C : O(n * groupSize) overall for the inner loop.
        while(!mp.empty()) {

            // Get the smallest available card.
            // begin() takes O(1).
            int curr = mp.begin()->first;

            // Try to form a consecutive group:
            // curr, curr+1, curr+2, ..., curr+groupSize-1
            for(int i = 0; i < groupSize; i++) {

                // If any required consecutive card is unavailable,
                // we cannot form a valid group.
                // Map lookup using [] takes O(log n).
                if(mp[curr + i] == 0) {
                    return false;
                }

                // Use one occurrence of the current card.
                // T.C : O(log n) for accessing/updating the map.
                mp[curr + i]--;

                // If frequency becomes zero, remove the card
                // from the map.
                // T.C : O(log n) for erase by key.
                if(mp[curr + i] < 1) {
                    mp.erase(curr + i);
                }
            }
        }

        // All cards have been successfully divided into
        // consecutive groups of size groupSize.
        return true;
    }
};