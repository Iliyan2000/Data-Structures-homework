#pragma once
#include <string>
#include <vector>

class BST_str
{
public:
	BST_str() : root(nullptr), size(0) {}
	~BST_str() { clear(root); }
	BST_str(const BST_str& tree) = delete;
	BST_str& operator=(const BST_str& tree) = delete;

	bool operator==(const BST_str& tree);
	bool operator!=(const BST_str& tree) { return !(*this == tree); }

	bool find(const std::string& str) const { return find(root, str); }
	void insert(const std::string& str) { if (insert(root, str)) ++size; }
	void remove(const std::string& str) { remove(root, str); }

	size_t getSize() const { return size; }

	std::vector<std::string> inorder() const { return inorder(root); }

private:
	struct Node
	{
		std::string data;
		Node* left, * right;

		Node(const std::string _data = "", Node* _left = nullptr, Node* _right = nullptr)
			: data(_data), left(_left), right(_right)
		{}
	} *root;
	size_t size;

	void clear(Node* node);
	bool equal(Node* node, Node* t_node);
	bool find(const Node* node, const std::string& str) const;
	Node* left_rotation(Node* node);
	Node* right_rotation(Node* node);
	Node* balance(Node* node);
	int balance_num(Node* node) const;
	bool insert(Node*& node, const std::string& str);
	void remove(Node*& node, const std::string& str);
	Node* extractMin(Node*& node);
	size_t height(const Node* node) const;
	std::vector<std::string> inorder(Node* node) const;
};