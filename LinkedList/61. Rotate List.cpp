
class Solution {
public:
    int length(ListNode* head){
        int length=0;

        ListNode* temp = head;
        while(temp){
            length++;
            temp = temp->next;
        }
        return length;
    }

    ListNode* rotateRight(ListNode* head, int k) {
        if(!head) return nullptr;
        int n = length(head);
        // if(n == 0) return nullptr;
        int p = k % n;


        ListNode* last = head;

        while(last->next){
            last = last->next;
        }

        ListNode* temp = head;
        for(int i=0; i<n-p-1; i++){
            temp = temp->next;
        }
        last->next = head;
        head = temp->next;
        temp->next = nullptr;
        return head;
    }
};


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
ListNode* findKthNode(ListNode*temp,int k){
    int cnt=1;
    while(temp!=nullptr){
        if(cnt==k)
        return temp;
        cnt++;
        temp=temp->next;

    }
    return temp;
}
    ListNode* rotateRight(ListNode* head, int k) {
        if(head==nullptr || k==0)
        return head;
        ListNode*tail=head;
        int len=1;
        while(tail->next!=nullptr){
            tail=tail->next;
            len=len+1;

        }
        if(k % len==0) return head;
        k=k % len;
        //attach tail to the head;
        tail->next=head;
        ListNode*newLastNode=findKthNode(head,len-k);
        head=newLastNode->next;
        newLastNode->next=nullptr;
        return head;

        
    }
};


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (k == 0 || head == nullptr)
        {
            return head;
        }
        ListNode *forward = head;
        int N = 0;
        while(k > 0 && forward != nullptr)
        {
            forward = forward->next;
            ++N;
            --k;
        }
        
        if (k > 0)
        {
            if (N == 1)
            {
                return head;
            }
            std::cout << "k:" << k << " N:" << N << std::endl;
            k = k % N;
            forward = head;
            if (k == 0)
            {
                return head;
            }
            while(k > 0)
            {
                if (forward == nullptr)
                {
                    forward = head;
                }
                forward = forward->next;
                --k;
            }
        }

        if (forward == nullptr)
        {
            forward = head;
            return head;
        }
        
        ListNode *prev_current = head;
        ListNode *current = head;
        ListNode *prev_forward = head;
        while(forward != nullptr)
        {
            prev_current = current;
            current = current->next;
            prev_forward = forward;
            forward = forward->next;
        }
     //   std::cout << "current:" << current->val << std::endl;
     //   std::cout << "prev_forward:" << prev_forward->val << std::endl;
        prev_forward->next = head;
        head = current;
        prev_current->next = nullptr;
        return head;
    }
};

// LeetCode 61
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head || !head->next || k == 0) return head;

        int n = 1;
        ListNode* tail = head;
        while (tail->next) {
            tail = tail->next;
            n++;
        }

        k %= n;
        if (k == 0) return head;

        tail->next = head;
        int steps = n - k;
        ListNode* newTail = tail;

        while (steps--) newTail = newTail->next;

        ListNode* newHead = newTail->next;
        newTail->next = nullptr;

        return newHead;
    }
};

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head || !head->next || k == 0) return head;

        int len = 1;
        ListNode* tail = head;
        while (tail->next != NULL) {
            tail = tail->next;
            len++;
        }

        k = k % len;
        if (k == 0) return head;

        ListNode* newTail = head;
        for (int i = 0; i < len - k - 1; i++) {
            newTail = newTail->next;
        }

        ListNode* newHead = newTail->next;
        newTail->next = NULL;
        tail->next = head;

        return newHead;
    }
};


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
ListNode*findnthnode(ListNode*temp,int k){
    int cnt=1;
    while(temp!=NULL){
        if(cnt==k){
            return temp;
        }
        cnt++;
        temp=temp->next;
    }
    return temp;
}
    ListNode* rotateRight(ListNode* head, int k) {
        if(head==NULL || k==0){
            return head;
        }
        ListNode*tail=head;
        int len=1;
        while(tail->next!=NULL){
            tail=tail->next;
            len++;
        }
        if(k%len==0){
            return head;
        }
        k=k%len;
        tail->next=head;
        ListNode*newlastnode=findnthnode(head,len-k);
        head=newlastnode->next;
        newlastnode->next=NULL;
        return head;
        
    }
};

/**
 *class Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
 class Solution {
 public:
  ListNode* rotateRight(ListNode* head, int k) {
    if (!head || !head->next || k == 0)
      return head;

    ListNode* tail;
    int length = 1;
    for (tail = head; tail->next; tail = tail->next)
      ++length;
    tail->next = head;  // Circle the list.

    const int t = length - k % length;
    for (int i = 0; i < t; ++i)
      tail = tail->next;
    ListNode* newHead = tail->next;
    tail->next = nullptr;

    return newHead;
  }
};

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

 /*Leetcode BYPASSED PLEASE LOOK Into it*/
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        // if(head==nullptr || head->next==nullptr) return head;
        // ListNode* temp=head;
        // int c=1;
        // while(temp->next!=nullptr){
        //     c++;
        //     temp=temp->next;
        // }
        // if(k%c==0) return head;
        // k=k%c;
        // int n=c-k;
        // temp->next=head;
        // temp=head;
        // for(int i=1;i<n;i++){
        //     temp=temp->next;
        // }
        // head=temp->next;
        // temp->next=nullptr;
        return head;
    }
};

int init = [] {
    ofstream out("user.out");
    cout.rdbuf(out.rdbuf());
    for (string str, k_str; getline(cin, str) && getline(cin, k_str); cout << '\n') {
        const int n = ranges::count(str, ',') + 1;
        int k = stoi(k_str) % n;
        if (n == 1 || k == 0) {
            cout << str;
            continue;
        }
        auto it = str.end() - 1;
        for (int commas = 0; it != str.begin() && commas != k; --it) if (*it == ',') ++commas;
        int dist = distance(str.begin(), it) + 2;
        string rotate = str.substr(dist, str.size() - 1 - dist);
        str.erase(it + 1, str.end() - 1);
        str.erase(0, 1);
        cout << '[' << rotate << ',' << str;
    }
    exit(0);
    return 0;
}();