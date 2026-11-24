

/********************************************************************* C++ ************************************************************/
//Approach-1 (Using Simple looping)
//T.C : O(n)
//S.C : O(1)
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        int minDistance = INT_MAX;

        ListNode* prev = head;
        ListNode* curr = head->next;
        int currPosition = 1;
        int previousCriticalIndex = 0;
        int firstCriticalIndex = 0;

        while (curr->next != NULL) {
            
            // When we see a critical point
            if ((curr->val < prev->val &&
                 curr->val < curr->next->val) ||
                (curr->val > prev->val &&
                 curr->val > curr->next->val)) {

                    if (previousCriticalIndex == 0) {
                        previousCriticalIndex = currPosition;
                        firstCriticalIndex = currPosition;
                    } else {
                        minDistance =
                            min(minDistance, currPosition - previousCriticalIndex);
                        previousCriticalIndex = currPosition;
                    }
            }

            currPosition++;
            prev = curr;
            curr = curr->next;
        }

        if (minDistance == INT_MAX) {
            return {-1, -1};
        }

        int maxDistance = previousCriticalIndex - firstCriticalIndex;
        return {minDistance, maxDistance};
    }
};



//Approach-2 (similar code but simple)
//T.C : O(n)
//S.C : O(1)
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        int firstCriticalIndex    = 0;
        int previousCriticalIndex = 0;

        int prevValue = 0;
        int currValue = 0;
        int nextValue = 0;

        int minDistance = INT_MAX;
        int index = 0;
        vector<int> result = {-1, -1};

        while (head != NULL) {
            prevValue = currValue;
            currValue = nextValue;
            nextValue = head->val;

            if (prevValue != 0 && currValue != 0 && nextValue != 0 && 
                (prevValue > currValue && currValue < nextValue ||
                prevValue < currValue && currValue > nextValue)) {
                
                if (firstCriticalIndex == 0) {
                    firstCriticalIndex = index;
                } else {
                    minDistance = min(minDistance, index - previousCriticalIndex);
                    result = {minDistance, index - firstCriticalIndex};
                }
                previousCriticalIndex = index;
            }

            index++;
            head = head->next;
        }

        return result;
    }
};

class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {

        if (!head || !head->next || !head->next->next) {
            return {-1, -1};
        }

        int firstCP = -1;
        int prevCP = -1;

        int minD = INT_MAX;
        int maxD = -1;

        ListNode* prev = head;
        ListNode* curr = head->next;

        int idx = 1;

        while (curr->next) {

            idx++;

            bool isMax = curr->val > prev->val &&
                         curr->val > curr->next->val;

            bool isMin = curr->val < prev->val &&
                         curr->val < curr->next->val;

            if (isMax || isMin) {

                if (firstCP == -1) {
                    firstCP = idx;
                }

                if (prevCP != -1) {
                    minD = min(minD, idx - prevCP);
                    maxD = idx - firstCP;
                }

                prevCP = idx;
            }

            prev = curr;
            curr = curr->next;
        }

        if (firstCP == prevCP) {
            return {-1, -1};
        }

        return {minD, maxD};
    }
};


/********************************************************************* JAVA ************************************************************/
//Approach-1 (Using Simple looping)
//T.C : O(n)
//S.C : O(1)
class Solution {
    public int[] nodesBetweenCriticalPoints(ListNode head) {
        int minDistance = Integer.MAX_VALUE;

        ListNode prev = head;
        ListNode curr = head.next;
        int currPosition = 1;
        int previousCriticalIndex = 0;
        int firstCriticalIndex = 0;

        while (curr.next != null) {
            
            // When we see a critical point
            if ((curr.val < prev.val && curr.val < curr.next.val) ||
                (curr.val > prev.val && curr.val > curr.next.val)) {

                if (previousCriticalIndex == 0) {
                    previousCriticalIndex = currPosition;
                    firstCriticalIndex = currPosition;
                } else {
                    minDistance = Math.min(minDistance, currPosition - previousCriticalIndex);
                    previousCriticalIndex = currPosition;
                }
            }

            currPosition++;
            prev = curr;
            curr = curr.next;
        }

        if (minDistance == Integer.MAX_VALUE) {
            return new int[]{-1, -1};
        }

        int maxDistance = previousCriticalIndex - firstCriticalIndex;
        return new int[]{minDistance, maxDistance};
    }
}


//Approach-2 (similar code but simple)
//T.C : O(n)
//S.C : O(1)
class Solution {
    public int[] nodesBetweenCriticalPoints(ListNode head) {
        int firstCriticalIndex    = 0;
        int previousCriticalIndex = 0;

        int prevValue = 0;
        int currValue = 0;
        int nextValue = 0;

        int minDistance = Integer.MAX_VALUE;
        int index = 0;
        int[] result = {-1, -1};

        while (head != null) {
            prevValue = currValue;
            currValue = nextValue;
            nextValue = head.val;

            if (prevValue != 0 && currValue != 0 && nextValue != 0 && 
                ((prevValue > currValue && currValue < nextValue) ||
                (prevValue < currValue && currValue > nextValue))) {
                
                if (firstCriticalIndex == 0) {
                    firstCriticalIndex = index;
                } else {
                    minDistance = Math.min(minDistance, index - previousCriticalIndex);
                    result[0] = minDistance;
                    result[1] = index - firstCriticalIndex;
                }
                previousCriticalIndex = index;
            }

            index++;
            head = head.next;
        }

        return result;
    }
}