#include <iostream>
#include <algorithm>
using namespace std;

void print1(int n) {

    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {

            cout << " * " ;
        }

        cout << endl;
    }
}


void print2(int n) {
    for(int i=1; i<=n; i++) {

        for(int j=1; j<=i; j++) {
            cout << " * " ;
        }
        cout << endl;
    }
}

void print3(int n) {
    for(int i=1; i<=n; i++) {

        for(int j=1; j<=i; j++) {
            cout << j << " ";
        }
        cout << endl;
    }
}

void print4(int n) {
    for(int i=1; i<=n; i++) {

        for(int j=1; j<=i; j++) {
            cout << i << " ";
        }
        cout << endl;
    }
}

void print5(int n) {
    for(int i=1; i<=n; i++) {

        for(int j=1; j<=n-i+1; j++) {
            cout << " * " ;
        }
        cout << endl;
    }
}

void print6(int n) {
    for(int i=1; i<=n; i++) {

        for(int j=1; j<=n-i+1; j++) {
            cout << j << " ";
        
        }
        cout << endl;
    }
}

void print7(int n) {
    int spaces = n-1;
    for(int i=1; i<=n; i++) {
        //spaces

        for(int j=0; j<spaces; j++) {
            cout << "   " ;
        }

        // stars 
        for(int j=1; j<= 2*i-1; j++) {
            cout << " * " ;
        }

        spaces--;
        cout << endl;
    }
}


void print8(int n) {
    int spaces = 0;
    int stars = 2*n-1;

    for(int i=1; i<=n; i++) {
        //spaces

        for(int j=0; j<spaces; j++) {
            cout << "   " ;
        }

        // stars 
        for(int j=1; j<= stars; j++) {
            cout << " * " ;
        }

        spaces++;
        stars -= 2 ;
        cout << endl;
    }
}


void print9(int n) {
    int spaces = n-1;
    int stars;
    for(int i=1; i<=n; i++) {
        //spaces

        for(int j=0; j<spaces; j++) {
            cout << "   " ;
        }

        // stars 
        for(int j=1; j<= 2*i-1; j++) {
            cout << " * " ;
        }

        spaces--;
        cout << endl;
    }
    spaces = 0;
    stars = 2*n-1;

    for(int i=1; i<=n; i++) {
        //spaces

        for(int j=0; j<spaces; j++) {
            cout << "   " ;
        }

        // stars 
        for(int j=1; j<= stars; j++) {
            cout << " * " ;
        }

        spaces++;
        stars -= 2 ;
        cout << endl;
    }
}


void print10(int n) {

    int stars = 1;

    for(int i=1; i<=2*n; i++) {

        for(int j=0; j<stars; j++) {
            cout << " * ";
        }

        cout << endl;
        if(i <= n) stars++;
        else stars--;
        
    }
}

void print11(int n) {

    for(int i=1; i<=n; i++) {

        for(int j=1; j<=i; j++) {

            if(j + i & 1) cout << " 0 ";
            else cout << " 1 ";

        }

        cout << endl;

    }
}


void print12(int n) {
    // int digit = 1 ;
    int spaces = 2*n-2 ;
    for(int i=1; i<=n; i++ ) {

        for(int j=1; j<=i; j++) {
            cout << " " << j << " ";
        }

        for(int j=1; j<=spaces; j++) {
            cout << "   ";
        }

        for(int j=i; j>=1; j--) {

            cout << " " << j << " ";
        }

        cout << endl;
        spaces -= 2 ;
        


    }
}


void print13(int n) {
    int x = 1 ;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=i; j++) {
            cout << x << " ";
            x++;

        }
        cout << endl;
    }

}
void print14(int n) {
    
    for(int i=1; i<=n; i++) {
        char x = 'A' ;
        for(int j=1; j<=i; j++) {
            cout << x << " ";
            x++;
        }
        cout << endl;
    }

}
void print15(int n) {
    
    for(int i=1; i<=n; i++) {
        char x = 'A' ;
        for(int j=1; j<=n-i+1; j++) {
            cout << x << " ";
            x++;
        }
        cout << endl;
    }

}
void print16(int n) {
    char x = 'A' ;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n-i+1; j++) {
            cout << x << " ";
            
        }
        x++;
        cout << endl;
    }

}


void print17(int n) {

    for(int i=0; i<n; i++) {

        // spaces
        for(int j=0; j<n-i-1; j++) {
            cout << "   ";

        }
        // characters
        int breakPoint = (2*i+1)/2;
        char x = 'A';
        for(int j=0; j<2*i+1; j++) {
            cout << " " << x << " ";
            if(j <= breakPoint) x++;
            else x--;
        }

        cout << endl;
    }
}
// void print19(int n) {
//     int spaces = 0;

//     for(int i=0; i < n; i++) {

//         // star
//         for(int j=1; j<=n-i; j++) {
//             cout << " * ";
//         }
//         // space
//         for(int j=0; j<spaces; j++) {
//             cout << "   ";
//         }

//         // stars
//         for(int j=1; j<=n-i; j++) {
//             cout << " * ";
//         }

//         spaces += 2 ;
//         cout << endl;

//     }

//     spaces = 2*n-2;

//     for(int i=1; i <= n; i++) {

//         // star
//         for(int j=1; j<=i; j++) {
//             cout << " * ";
//         }
//         // space
//         for(int j=0; j<spaces; j++) {
//             cout << "   ";
//         }

//         // stars
//         for(int j=1; j<=i; j++) {
//             cout << " * ";
//         }
//         spaces -= 2 ;
//         cout << endl;

//     }


// }

void print19(int N) {
        // Initial spaces for upper half
        int iniS = 0;

        // Loop for upper half rows
        for (int i = 0; i < N; i++) {
            // Print stars on left
            for (int j = 1; j <= N - i; j++) {
                cout << "*";
            }
            // Print spaces in middle
            for (int j = 0; j < iniS; j++) {
                cout << " ";
            }
            // Print stars on right
            for (int j = 1; j <= N - i; j++) {
                cout << "*";
            }
            // Increase middle spaces by 2
            iniS += 2;
            // Move to next row
            cout << endl;
        }

        // Initial spaces for lower half
        iniS = 2 * N - 2;

        // Loop for lower half rows
        for (int i = 1; i <= N; i++) {
            // Print stars on left
            for (int j = 1; j <= i; j++) {
                cout << "*";
            }
            // Print spaces in middle
            for (int j = 0; j < iniS; j++) {
                cout << " ";
            }
            // Print stars on right
            for (int j = 1; j <= i; j++) {
                cout << "*";
            }
            // Decrease middle spaces by 2
            iniS -= 2;
            // Move to next row
            cout << endl;
        }
    }

void print20(int n) {

    int spaces = 2*n-2;

    for(int i=1; i<=2*n-1; i++) {

        int stars = i ;

        if(i > n ) stars = 2*n-i;
        // stars
        for(int j=1; j<=stars; j++) {
            cout <<" * ";
        }
        // spaces
        for(int j=1; j<=spaces; j++) {
            cout << "   ";
        }
        // starts

        for(int j=1; j <= stars; j++) {
            cout << " * " ;
        }

        cout << endl;

        if(i < n) spaces -= 2;
        else spaces += 2;
    }
}
void _1print21(int n) {

    for(int i=0; i<n; i++) {

        if(i == 0 || i == n-1) {
            for(int j=0; j<n; j++) {
                cout << " * ";
            }

            cout << endl;
        }else {
            for(int j=0; j<n; j++) {
                if(j == 0 || j == n-1) {
                    cout << " * ";
                }else {
                    cout << "   ";
                }
            
            }
             cout << endl;
        }
    }
}

void _2print21(int n) {
    /*
    Approach:
        loop thrugh all the matrix
        whenver there is boundary print 
        else print the space
    */
    for(int i=0; i<n; i++) {

        for(int j=0; j<n; j++) {

            if(i == 0 || j == 0 || i == n-1 || j == n-1) {
                cout << " * ";
            }else {
                cout << "   ";
            
            }
        }

        cout << endl;
    }
}
void print22(int n) {
    /*
        Approach: subtract all the number of the matrix with n
        than from observation all the element are nothing but the minimum distance from all the corners
        i.e min({top, right, bottom, left})
        n - min({top, right, bottom, left})
        
    */
    for(int i=0; i<2*n-1; i++) {
        for(int j=0; j<2*n-1; j++) {

            int top = i;
            int bottom = 2*n-2-i;
            int left = j;
            int right = 2*n-2-j;

            cout << n - min({top, bottom, left, right}) ;
        }

        cout << "\n";
    }
}

int main() {

    int n ; 
    cout << "Enter the number: ";cin >> n ;

    print17(n);
    

    return 0;
}