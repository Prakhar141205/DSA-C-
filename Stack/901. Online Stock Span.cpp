class StockSpanner {
public:
    vector<int> st;
    StockSpanner() : st() {};
    
    int next(int price) {
        st.push_back(price);
        int n = st.size();

        int ans = 0;
        while(n > 0 && st[n-1] <= price) {
            ans++;
            n--;
        }
        return ans;
    }
};

// Using stack

class StockSpanner {
public:
    stack<pair<int, int>> st;
    StockSpanner() {}
    
    int next(int price) {
        int span = 1;
        while(!st.empty() && st.top().first <= price) {
            span += st.top().second;
            st.pop();
        }
        st.push({price, span});
        return span;
    }
};