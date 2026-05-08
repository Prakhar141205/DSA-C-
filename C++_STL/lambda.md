### A lambda function is a small anonymous function that you 
## can write directly inside expressions, STL algorithms, loops, sorting logic, etc.

## basic syntax

[capture](parameters) -> return_type {
    body
}


# Simplest example

auto square = [](int x){
    return x*x;
};

cout << square(5);


## Using lambda inside the count_if function

count_if(v.begin(), v.end(),
         [](int x){
             return x%2==0;
         });




## 1. Capture List []

This is the most important concept.

It controls access to outside variables.

copies the outside variable 

int x = 10;

auto f = [x]() {
    return x;
};

## using the actual value using reference

int x = 10;

auto f = [&x]() {
    x++;
};

f();
cout << x;

## capture using [=] => capture all the variables that are initialized
int a=1,b=2;

auto f = [=]() {
    return a+b;
};

## Return type => compiler automatically detects
[](int x){
    return x*x;
}

## if you want to explicity mention than 
[](int x) -> int {
    return x*x;
}


## lamnda using STL

## sortig pairs
sort(v.begin(), v.end(),
     [](auto &a, auto &b){
         return a.second < b.second;
     });

## for each
for_each(v.begin(), v.end(),
         [](int x){
             cout << x << " ";
         });

## minheap

priority_queue<int>,vector<int>,greater<int>> pq;

## custom implementation
auto cmp = [](int a, int b){
    return a > b;
};

priority_queue<int>,vector <int>,decltype(cmp)> pq(cmp);

## sort the string on the basis of length
sort(words.begin(), words.end(),
     [](string &a,string &b){
         return a.size()<b.size();
     });