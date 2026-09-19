/* class Solution:
    def checkOverlap(self, r: int, c1: int, c2: int, x1: int, y1: int, x2: int, y2: int) -> bool:
        """Check wether this recatangle and the circle overlap to each other or not ?0 """
        # case 1 circle inside the rectangle completely
        xi = -1 
        yi = -1
        if x1 > c1 :
            xi = x1
        elif x2 < c1 :
            xi = x2
        else :
            xi = c1


        if y1 > c2 :
            yi = y1
        elif y2 < c2 :
            yi = y2
        else:
            yi = c2

        

        def find_distance(c1, c2, a1, b1):

            d1 = ((c1-a1) ** 2 + (c2 - b1) ** 2 ) ** 0.5

            return d1 

        final_min_distance = find_distance(c1, c2, xi, yi)

        print(final_min_distance)
        return final_min_distance <= r

        */



class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {
        //nearest point
        int xi = clamp(xCenter, x1, x2);
        int yi = clamp(yCenter, y1, y2);

        if(y1 > yCenter) {
            yi = y1;
        } else if(y2 < yCenter) {
            yi = y2;
        } else {
            yi = yCenter;
        }

        //(xi, yi) ------- (xCenter, yCenter)
        return sqrt((xi - xCenter)*(xi - xCenter) + (yi - yCenter)*(yi - yCenter)) <= radius;
    }
};

class Solution:
    def checkOverlap(self, r: int, c1: int, c2: int, x1: int, y1: int, x2: int, y2: int) -> bool:
        # Clamp circle center to the closest point on the rectangle boundaries
        closest_x = max(x1, min(c1, x2))
        closest_y = max(y1, min(c2, y2))
        
        # Calculate squared distance
        squared_dist = (c1 - closest_x) ** 2 + (c2 - closest_y) ** 2
        
        # Check against squared radius
        return squared_dist <= r ** 2
