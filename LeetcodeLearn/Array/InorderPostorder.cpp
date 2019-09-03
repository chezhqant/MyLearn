#include <iostream>
#include <vector>

using namespace std;

/*
 *inorder = {9,3,15,20,7}
 *postorder = {9, 15,7, 20, 3}
 *
 *
 *                3
 *        9             20
 *                15            7
 */

struct TreeNode{
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
public:
        TreeNode* HalfTree(const vector<int> &inorder, int start, int end, vector<int>::const_iterator &data)
        {
                if (start >= end)
                {
                        ++data;
                        return nullptr;
                }

                int find_loc = start;
                while (find_loc < end)
                {
                        if (*data == inorder[find_loc])
                        {
                                break;
                        }

                        ++find_loc;
                }

                TreeNode *root = new TreeNode(*data);
                root->right = HalfTree(inorder, find_loc+1, end, --data);
                root->left = HalfTree(inorder, start, find_loc, --data);
                return root;
        }

        TreeNode* buildTree(vector<int> &inorder, vector<int> &postorder)
        {
                if (inorder.empty())
                {
                        return nullptr;
                }

                vector<int>::const_iterator val = --(postorder.cend());
                return HalfTree(inorder, 0, inorder.size(), val);
        }
};

int main()
{
        vector<int> inorder = {9,3,15,20,7};
        vector<int> postorder = {9, 15,7, 20, 3};

        class Solution a_class;
        a_class.buildTree(inorder, postorder);

        return 0;
}
