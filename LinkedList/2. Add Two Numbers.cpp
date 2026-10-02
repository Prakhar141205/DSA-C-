
class Solution {
 public:
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    ListNode* curr = &dummy;
    int carry = 0;

    while (l1 != nullptr || l2 != nullptr || carry > 0) {
      if (l1 != nullptr) {
        carry += l1->val;
        l1 = l1->next;
      }
      if (l2 != nullptr) {
        carry += l2->val;
        l2 = l2->next;
      }
      curr->next = new ListNode(carry % 10);
      carry /= 10;
      curr = curr->next;
    }

    return dummy.next;
  }
};


// Brute force


#define ALL(x) begin(x),  end(x)
class Solution {
public:
    typedef ListNode* ll ;

    string addLargeNumbers(string s1, string s2) {

        int i = s1.length()-1;
        int j = s2.length()-1;
        int carry = 0;
        string res = "";
        while(i >= 0 || j >= 0 || carry > 0) {

            int sum = carry;

            if(i >= 0) {
                sum += s1[i] - '0';
                i--;
            }

            if(j >= 0) {
                sum += s2[j] - '0';
                j--;
            }

            carry = sum / 10;
            res += to_string(sum % 10);

        }

        reverse(ALL(res));

        return res;
        
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        string s1 = "";

        ll t1 = l1;
        while(t1) {
            s1 += to_string(t1->val);
            t1 = t1->next;
        }
        reverse(ALL(s1));
        

        // long long n2 = 0;
        string s2 = "";

        ll t2 = l2;
        while(t2) {
            s2 += to_string(t2->val);
            t2 = t2->next;
        }
        reverse(ALL(s2));

        // for(char c : s2) {
        //     n2 = n2 * 10 + (c-'0');
        // }

        // int finalNumber = n1 + n2 ;

        // string s = to_string(finalNumber);
        string s = addLargeNumbers(s1, s2);

        // // reverse(ALL(x));
        int sz = s.length();

        // int num = 0;

        // for(char c : s ) {
        //     num = num * 10 + (c-'0');
        // }
        int k = sz-1;
        ListNode* finalHead = new ListNode(s[k] - '0');
        k--;

        // finalNumber /= 10 ;

        ll temp = finalHead;
        
        while(k >= 0) {
            // int d = finalNumber % 10 ;
            ListNode* newNode = new ListNode(s[k] - '0');
            temp->next = newNode;
            temp = temp->next;

            // finalNumber /= 10 ;
            k--;
            // sz--;
        }


        return finalHead;
        
    }
};