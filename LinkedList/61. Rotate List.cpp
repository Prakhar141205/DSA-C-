// using space complexity O(n) and time complexity O(n)

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(!head) return nullptr;
        vector<int> nodes;
        
        ListNode* temp = head;
        while(temp) {
            nodes.push_back(temp->val);
            temp = temp->next;
        }
        
        int n = nodes.size();
        k = k % n;
        for(int x : nodes) cout << x << " ";
        cout << endl;
        
        reverse(begin(nodes), begin(nodes)+n-k);
        reverse(begin(nodes)+ n - k, end(nodes));
        reverse(begin(nodes), end(nodes));

        for(int x : nodes) cout << x << " ";
        int i=0;

        ListNode* newHead = new ListNode(nodes[i]);
        i++;
        ListNode* curr = newHead;
        for(i=1; i<nodes.size(); i++) {
            ListNode* n = new ListNode(nodes[i]);
            curr->next = n ;
            curr =  n ;
        }

        return newHead;
    }
};


// using constant space complexity O(1) and time complexity O(n)


class Solution {
public:
    int getSize(ListNode* head) {
        ListNode* temp = head;
        int ans = 0;
        while(temp) {
            ans += 1;
            temp = temp->next;
        }

        return ans;
    }
    ListNode* rotateRight(ListNode* head, int k) {
        if(!head) return nullptr;
        int n = getSize(head);
        k = k % n;

        ListNode* temp = head;
        ListNode* tail = head;
        while(tail->next) {
            tail = tail->next;
        }

        tail->next = head;
        for(int i=1; i<n-k; i++) {
            temp = temp->next;
        }
        ListNode* newHead = temp->next;

        temp->next = nullptr;

        return newHead;
    }
};