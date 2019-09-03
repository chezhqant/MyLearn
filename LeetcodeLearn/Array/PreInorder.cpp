#include <iostream>
#include <vector>

using namespace std;

struct TreeNode
{
        int val;
        TreeNode *left;
        TreeNode *right;

        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/*
 *pre = {3, 9, 20, 15, 7}
 *inorder = (9, 3, 15, 20 ,7)
 *
 *                3
 *        9             20
 *                15            7
 */

class Solution
{
public:
        TreeNode* HalfTree(const vector<int> &inorder, int start, int end, vector<int>::const_iterator val)
        {
                if (start == end)
                {
                        --val;
                        return nullptr;
                }

                int find_loc = start;
                while (find_loc < end)
                {
                        if (inorder[find_loc] == *val)
                        {
                                break;
                        }
                        ++find_loc;
                }

                TreeNode *root = new TreeNode(*val);
                root->left = HalfTree(inorder, start, find_loc, ++val);
                root->right = HalfTree(inorder, find_loc+1, end, ++val);

                return root;
        }

        TreeNode* buildTree(vector<int> &preorder, vector<int> &inorder)
        {
                if (preorder.empty())
                {
                        return nullptr;
                }

                vector<int>::const_iterator val = preorder.cbegin();
                return HalfTree(inorder, 0, inorder.size(), val);
        }
};

int main()
{
        vector<int> preorder{1,2};
        vector<int> inorder{1,2};

        class Solution a_class;
        TreeNode *node = a_class.buildTree(preorder, inorder);

        return 0;
}
