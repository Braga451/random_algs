/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        bool result = false; 
        int currentSum = 0;

        s(root, targetSum, currentSum, result);
        return result;
    }

    void s(TreeNode * n, int& targetSum , int& currentSum, bool& result) {
        if (n == nullptr || result) return;
        currentSum += n->val;

        if ( (n->left == nullptr) && (n->right == nullptr) && currentSum == targetSum) {
            result = true;
            return;
        }
        s(n->left, targetSum, currentSum, result);
        s(n->right, targetSum, currentSum, result);
        currentSum -= n->val;
    }
};
