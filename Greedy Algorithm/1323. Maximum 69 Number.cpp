class Solution {
public:
    int maximum69Number (int num) {


       int placeVal = 0;
       int placeValSix = -1;

       int temp = num;

       while(temp > 0)  {

        if(temp % 10 == 6)  {
            placeValSix = placeVal;
        }

        placeVal++;
        temp /= 10 ;
       }

       return placeValSix == -1 ? num : num +  3 * pow(10, placeValSix);
    }
};