class Solution {
public:
    int maxSatisfied(vector<int>& cust, vector<int>& g, int mins) {
            int n = cust.size();
            int l=0, r = 0;
            int unsatisfied_customers = 0;
            int max_unsatisfied_customers = 0;

            int st_idx = -1;
            int end_idx = -1; // window at whidch max unsatisfied found

            while(r < n) {

                if(g[r] == 1) {
                    unsatisfied_customers += cust[r];

                }


                if(r-l+1 > mins)  {
                    if(g[l] == 1)
                        unsatisfied_customers -= cust[l];
                    l++;
                }

                if(r-l+1 == mins) {
                    max_unsatisfied_customers = max(unsatisfied_customers, max_unsatisfied_customers);
                    st_idx = l;
                    end_idx = r;
                }


                r++;

            }

            int cnt = max_unsatisfied_customers; // max satisfied customers

            for(int i=0; i<n; i++) {
                if(g[i] == 0) {
                    cnt += cust[i];
                }
            }
        return cnt;
    }
};


class Solution {
public:
    int maxSatisfied(vector<int>& cust, vector<int>& g, int mins) {
            int n = cust.size();
            int l=0, r = mins;
            int unsatisfied_customers = 0;
            int max_unsatisfied_customers = 0;

            int st_idx = -1;
            int end_idx = -1; // window at whidch max unsatisfied found

            for(int i=0; i<mins; i++){
                unsatisfied_customers += cust[i] * g[i];
            }
            max_unsatisfied_customers = unsatisfied_customers;
            
            while(r < n) {

                unsatisfied_customers += cust[r] * g[r];

                unsatisfied_customers -= cust[l] * g[l];

                max_unsatisfied_customers = max(unsatisfied_customers, max_unsatisfied_customers);

                l++;
                r++;

            }

            int cnt = max_unsatisfied_customers; // max satisfied customers

            for(int i=0; i<n; i++) {
                if(g[i] == 0) {
                    cnt += cust[i];
                }
            }
        return cnt;
    }
};