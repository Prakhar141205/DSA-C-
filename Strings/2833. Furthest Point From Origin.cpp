class Solution {
public:
    int furthestDistanceFromOrigin(const std::string_view& moves) {
        char ret = 0;
        char underscoreIsRight = std::count_if(moves.begin(), moves.end(), [](auto& c) { return c=='R';}) >= std::count_if(moves.begin(), moves.end(), [](auto& c) { return c=='L';}) 
            ? 1 : -1;
        for(auto const& c : moves) {
            switch(c) {
                case 'R':
                    ++ret;
                    break;
                case 'L':
                    --ret;
                    break;
                default:
                    ret += underscoreIsRight;
            }
        }
        return std::abs(ret);
    }
};