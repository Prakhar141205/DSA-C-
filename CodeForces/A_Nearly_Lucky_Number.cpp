#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

   long long int n;

   cin >> n;

   bool isValid = true;
   while(n > 10){
    
    if((n % 10 != 4) && (n % 10) != 7){
        
        isValid = false;
        break;
    }
    n /= 10;
   }

   if(!isValid){
    cout << "NO\n";
   }else if(n == 4){
        cout << "NO\n";
   }else if(n == 7){
    cout << "NO\n";
   }
   else{
    cout << "YES\n";
   }

   
   
    return 0;
}