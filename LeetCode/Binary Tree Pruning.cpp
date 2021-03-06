/*
814. Binary Tree Pruning(unsolved)
We are given the head node root of a binary tree, where additionally every node's value is either a 0 or a 1.
Return the same tree where every subtree (of the given tree) not containing a 1 has been removed.
(Recall that the subtree of a node X is X, plus every node that is a descendant of X.)

Example 1:
Input: [1,null,0,0,1]
Output: [1,null,0,null,1]

Explanation:
Only the red nodes satisfy the property "every subtree not containing a 1".
The diagram on the right represents the answer.

Example 2:
Input: [1,0,1,0,0,0,1]
Output: [1,null,1,null,1]

Example 3:
Input: [1,1,0,1,1,0,1,0]
Output: [1,1,0,1,1,null,1]

Note:

The binary tree will have at most 100 nodes.
The value of each node will only be 0 or 1.

*/
#include<iostream>
#include<queue>
#include<sstream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	int isEnd()
	{
		if (this->left == nullptr&&this->right == nullptr)
		{
			if (this->val == 0)return 0;
			else return 1;
		}
		return -1;
	}
};

class Solution {
public:
	TreeNode * pruneTree(TreeNode* root) {
		if (root!=nullptr)
		{
			if (root->isEnd()==1)
			{
				return root;
			}
			else if (root->isEnd() == 0)
			{
				delete root;
				return nullptr;
			}
			else
			{
				root->left = pruneTree(root->left);
				root->right = pruneTree(root->right);

				//adding this can avoid this method only deleting the last layer of given tree
				if (root->isEnd() == 0)
				{
					delete root;
					return nullptr;
				}

				return root;
			}
		}
		return nullptr;
	}
};

void trimLeftTrailingSpaces(string &input) {
	input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
		return !isspace(ch);
	}));
}

void trimRightTrailingSpaces(string &input) {
	input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
		return !isspace(ch);
	}).base(), input.end());
}

TreeNode* stringToTreeNode(string input) {
	trimLeftTrailingSpaces(input);
	trimRightTrailingSpaces(input);
	input = input.substr(1, input.length() - 2);
	if (!input.size()) {
		return nullptr;
	}

	string item;
	stringstream ss;
	ss.str(input);

	getline(ss, item, ',');
	TreeNode* root = new TreeNode(stoi(item));
	queue<TreeNode*> nodeQueue;
	nodeQueue.push(root);

	while (true) {
		TreeNode* node = nodeQueue.front();
		nodeQueue.pop();

		if (!getline(ss, item, ',')) {
			break;
		}

		trimLeftTrailingSpaces(item);
		if (item != "null") {
			int leftNumber = stoi(item);
			node->left = new TreeNode(leftNumber);
			nodeQueue.push(node->left);
		}

		if (!getline(ss, item, ',')) {
			break;
		}

		trimLeftTrailingSpaces(item);
		if (item != "null") {
			int rightNumber = stoi(item);
			node->right = new TreeNode(rightNumber);
			nodeQueue.push(node->right);
		}
	}
	return root;
}

string treeNodeToString(TreeNode* root) {
	if (root == nullptr) {
		return "[]";
	}

	string output = "";
	queue<TreeNode*> q;
	q.push(root);
	while (!q.empty()) {
		TreeNode* node = q.front();
		q.pop();

		if (node == nullptr) {
			output += "null, ";
			continue;
		}

		output += to_string(node->val) + ", ";

		if (node->isEnd() == 1)continue;

		q.push(node->left);
		q.push(node->right);
	}
	return "[" + output.substr(0, output.length() - 2) + "]";
}

TreeNode* clear(TreeNode *root)
{
	if (root != nullptr)
	{
		if (root->isEnd() == -1)
		{
			root->left = clear(root->left);
			root->right = clear(root->right);
		}
		else
		{
			delete root;
			return nullptr;
		}
		delete root;
	}
	return nullptr;
}

int main() {
	string line;
	while (getline(cin, line)) {
		TreeNode* root = stringToTreeNode(line);

		TreeNode* ret = Solution().pruneTree(root);

		string out = treeNodeToString(ret);
		cout << out << endl;

		root = clear(root);
	}
	return 0;
}