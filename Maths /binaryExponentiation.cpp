
int binaryExponentiation(int a, int b){

    if(b == 0) return 1;

    int halfPower = binaryExponentiation(a, b/2);
    
    int res = halfPower * halfPower;

    if( b % 2 != 0){
        res *= a;
    }
    return res;
} 