#include <iostream>
#include <vector>

using namespace std;

int fractionalKnapSack(vector<int> value, vector<int> weight, int W){
    int n = value.size(), profit=0;
    vector<pair<double, int>> ratio(n); // ratio, idx
    for(int i=0; i<n; i++){
        ratio.push_back({(value[i]/(double)weight[i]), i});
    }

    sort(ratio.begin(), ratio.end(), [](pair<double, int> p1, pair<double, int> p2) {
        return p1.first > p2.first;
    };);

    for(int i=0; i<n; i++){

        double val = ratio[i].first;
        int idx = ratio[i].second;

        if(weight[idx] <= W){
            profit += value[idx];
            W -= weight[idx];
        }else{
            profit += val * W;
            W = 0;
            break;
        }
    }
    return profit;
}
int main(){
    vector<int> weight = {10, 2, 5};
    vector<int> value = {20, 10, 50};

    cout << "Maximum profit is " <<fractinalKnapSack(value, weight, 50);
    return 0;

}