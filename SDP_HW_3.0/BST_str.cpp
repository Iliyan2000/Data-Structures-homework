#include "BST_str.h"

bool BST_str::operator==(const BST_str& tree)
{
	return equal(root, tree.root);
}

void BST_str::clear(Node* node)
{
	if (node)
	{
		clear(node->left);
		clear(node->right);
		delete node;
	}
}
bool BST_str::equal(Node* node, Node* t_node)
{
	if (node == nullptr && t_node == nullptr)
		return true;
	if (node == nullptr || t_node == nullptr || node->data != t_node->data)
		return false;
	return equal(node->left, t_node->right) && equal(node->right, t_node->right);
}
bool BST_str::find(const Node* node, const std::string& str) const
{
	if (!node) return false;
	if (node->data == str) return true;
	return str < node->data ? find(node->left, str) : find(node->right, str);
}
BST_str::Node* BST_str::left_rotation(Node* node)
{
	Node* right_child = node->right;
	Node* left_subtree = right_child->left;

	right_child->left = node;
	node->right = left_subtree;

	return right_child;
}
BST_str::Node* BST_str::right_rotation(Node* node)
{
	Node* left_child = node->left;
	Node* right_subtree = left_child->right;

	left_child->right = node;
	node->left = right_subtree;

	return left_child;
}
BST_str::Node* BST_str::balance(Node* node)
{
	int bal = balance_num(node);

	if (bal > 1)
	{
		int bal_left = balance_num(node->left);
		if (bal_left >= 0)
			return right_rotation(node);
		else
		{
			node->left = left_rotation(node->left);
			return right_rotation(node);
		}
	}
	if (bal < -1)
	{
		int bal_right = balance_num(node->right);
		if (bal_right > 0)
		{
			node->right = right_rotation(node->right);
			return left_rotation(node);
		}
		else
			return left_rotation(node);
	}
	return node;
}
int BST_str::balance_num(Node* node) const
{
	if (!node) return 0;
	return height(node->left) - height(node->right);
}
bool BST_str::insert(Node*& node, const std::string& str)
{
	bool f = true;
	if (!node)
		node = new Node(str);
	else if (node->data == str)
		return false;
	else
		f = insert(str < node->data ? node->left : node->right, str);

	node = balance(node);
	return f;
}
void BST_str::remove(Node*& node, const std::string& str)
{
	if (!node) return;
	if (node->data == str)
	{
		Node* toDel = node;
		if (!node->left) node = node->right;
		else if (!node->right) node = node->left;
		else
		{
			Node* min = extractMin(node->right);
			min->left = node->left;
			min->right = node->right;
			node = min;
		}
		--size;
		delete toDel;
	}
	else remove(str < node->data ? node->left : node->right, str);

	node = balance(node);
}
BST_str::Node* BST_str::extractMin(Node*& node)
{
	if (node->left) return extractMin(node->left);
	Node* n = node;
	node = node->right;
	return n;
}
size_t BST_str::height(const Node* node) const
{
	if (!node) return 0;
	return 1 + std::max(height(node->left), height(node->right));
}
std::vector<std::string> BST_str::inorder(Node* node) const
{
	std::vector<std::string> vec;
	if (node == nullptr)
		return vec;
	if (node->left)
		vec = inorder(node->left);
	vec.push_back(node->data);
	if (node->right)
	{
		std::vector<std::string> r_vec = inorder(node->right);
		vec.insert(vec.end(), r_vec.begin(), r_vec.end());
	}
	return vec;
}