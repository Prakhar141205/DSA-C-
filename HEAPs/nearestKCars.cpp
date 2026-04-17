// Implementation of Max heap
#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

class Car{
public:
    int i;
    int dist;

    Car(int i, int dist){
        this->i = i;
        this->dist = dist;
    }
    
    bool operator < (const Car &obj) const{
        return this->dist > obj.dist;
    }

};

void nearestKCars(vector<pair<int,int>> pos, int k){
    vector<Car> cars;

    for(int i=0; i<pos.size(); i++){
        int dist = (pos[i].first*pos[i].first) + (pos[i].second * pos[i].second);
        cars.push_back(Car(i, dist));
    }

    priority_queue<Car> pq(cars.begin(), cars.end());

    for(int i=0; i<k; i++){
        cout << "Car " << pq.top().i << "\n";
        pq.pop();
    }
    cout << endl;
}



int main(){
    vector<pair<int, int>> pos;

    pos.push_back({3, 3});
    pos.push_back({5, -1});
    pos.push_back({-2, 4});

    nearestKCars(pos, 2);
    return 0;
}