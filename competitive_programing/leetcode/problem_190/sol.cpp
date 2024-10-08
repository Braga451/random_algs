#include <bitset>

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        std::string numStr = std::bitset<32>(n).to_string();

        std::reverse(numStr.begin(), numStr.end());

        return std::stoul(numStr, nullptr, 2);
    }
};
