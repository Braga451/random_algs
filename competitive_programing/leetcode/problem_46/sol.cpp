class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> permutations;
        vector<int> vec;
        vector<bool> isInVec(nums.size(), false);
        permutate(nums, vec, permutations, isInVec);
        return permutations;
    }

    void permutate(vector<int>& nums, vector<int>& actualVec, vector<vector<int>>& vectors,
                    vector<bool>& isInVec) {
        if (actualVec.size() == nums.size()) {
            vectors.push_back(actualVec);
            return;
        }

        for (int i = 0; i < nums.size(); ++i) {
            if (isInVec[i] == false) {
                actualVec.push_back(nums[i]);
                isInVec[i] = true;
                permutate(nums, actualVec, vectors, isInVec);
                isInVec[i] = false;
                actualVec.pop_back();
            }
        }
    }
};
