class Solution {
public:
    typedef long long ll;

    string freeSlotsFiller(ll required, ll length) {
        string str ;

        for(int dig = 9; dig >= 2; dig--) {
            while(required % dig == 0) {
                str.push_back(dig + '0') ;
                required /= dig ;
            }
        }

        while(str.length() < length) {
            str.push_back('1') ;
        }

        reverse(str.begin(), str.end()) ;
        return str ;
    }
    string smallestNumber(string num, long long t) {
        int n = num.length() ;

        ll temp = t ;
        for(int primeFact : {2, 3, 5, 7}) {
            while(temp % primeFact == 0) {
                temp /= primeFact ;
            }
        }

        if(temp != 1) {
            return "-1" ;
        }

        // precompute remaining factor 
        vector<ll> remainingFactor(n+1, t) ;

        for(int i=0; i<n; i++) {
            int dig = num[i] - '0';

            if(dig == 0) {
                break;
            }
            remainingFactor[i+1] = remainingFactor[i] / gcd(remainingFactor[i], (ll) dig) ;

        }

        if(remainingFactor[n] == 1) {
            return num ;
        }

        int zeroPos = num.find('0') ;
        int zeroIdx = n-1 ;

        if(zeroPos != -1) {
            zeroIdx = zeroPos ;
        }

        for(int i=zeroIdx; i>=0; i--) {
            ll required = remainingFactor[i] ;
            int freeSlots = n - 1 - i ;

            for(int dig = (num[i] - '0') + 1; dig <= 9; dig++) {
                ll furtherRequired = required / gcd((ll)dig, required) ;
                string requiredNumber = freeSlotsFiller(furtherRequired, freeSlots) ;

                if(requiredNumber.length() == freeSlots) {
                    return num.substr(0, i) + (char)(dig + '0') + requiredNumber ; 
                }
            }
        }

        return freeSlotsFiller(t, n+1) ;
    }
};