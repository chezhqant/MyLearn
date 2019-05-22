#include <iostream>
#include <stack>

using namespace std;

// refer: <https://leetcode.com/problems/same-tree/>
/*
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
//参考：https://blog.csdn.net/qq_26286193/article/details/80256324
class Solution {
public:
    //非递归的方法,栈
	/*
	 * bool isSameTree(TreeNode* p, TreeNode* q) [>{{{<]
	 * {
	 *     stack<TreeNode*> st;
	 *     st.push(p);
	 *     st.push(q);
	 *     
	 *     while (!st.empty())
	 *     {
	 *         TreeNode *left = st.top();
	 *         st.pop();
	 *         
	 *         TreeNode *right = st.top();
	 *         st.pop();
	 *         
	 *         if (left == NULL && right == NULL)
	 *         {
	 *             continue;
	 *         }
	 *         else if (left == NULL || right == NULL)
	 *         {
	 *             return false;
	 *         }
	 *         
	 *         if (left->val != right->val)
	 *         {
	 *             return false;
	 *         }
	 *         
	 *         st.push(right->right);
	 *         st.push(left->right);
	 *         st.push(right->left);
	 *         st.push(left->left);
	 *     }
	 *     
	 *     return true;
	 * }[>}}}<]
	 */

    //递归的方法
    bool isSameTree(TreeNode *p, TreeNode *q)/*{{{*/
    {
        if ((p == NULL) && (q == NULL))
        {
            return true;
        }

        if ((p == NULL) || (q == NULL))
        {
            return false;
        }

        if ((p != NULL) && (q != NULL))
        {
            if (p->val != q->val)
            {
                return false;
            }
        }

        return (isSameTree(p->left, q->left) && isSameTree(p->right, q->right));
    }/*}}}*/
};
