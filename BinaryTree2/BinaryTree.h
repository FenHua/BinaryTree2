#include<stack>
#include<queue>
#include<assert.h>
#include"iostream"
using namespace std;
template<typename T>struct BinaryTreeNode
{
	T _data;
	BinaryTreeNode*_left;
	BinaryTreeNode*_right;
	BinaryTreeNode(const T&data = T()) :_data(data), _left(NULL), _right(NULL)
	{}
};
template<typename T>class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
protected:
	Node*_root;
public:
	BinaryTree() :_root(NULL)
	{}
	BinaryTree(const T*array, size_t size, const T&invalid)
	{
		size_t index = 0;
		_root = _CreateTree(array, size, index, invalid);
	}
	BinaryTree(const BinaryTree<T>&bt)
	{
		_root = _Copy(bt._root);
	}
	BinaryTree<T>&operator=(const BinaryTree<T>&bt)
	{
		if (this != &bt)
		{
			BinaryTree<T>tmp(bt);
			std::swap(_root, tmp._root);
		}
		return *this;
	}
	~BinaryTree()
	{
		_Destroy(_root);
	}
	void PreOrder()
	{
		//先序排序
		_PreOrder(_root);
		cout << endl;
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
	void PostOrder()
	{
		_PostOrder(_root);
		cout << endl;
	}
public:
	void PrevOrderNoR()
	{
		//先序遍历
		stack<Node*>s;
		Node*cur = _root;
		while (cur || !s.empty())
		{
			while (cur)
			{
				//一直向左遍历直到左为空
				cout << cur->_data << " ";//访问根节点
				s.push(cur);
				cur = cur->_left;
			}
			//此时已经访问过当前节点，且当前节点的左子树为空
			Node*top = s.top();
			s.pop();
			cur = top->_right;//访问右子树
		}
		cout << endl;
	}
	void InOrderNoR()
	{
		//中序遍历，先左子树，再根节点
		stack<Node*>s;
		Node*cur = _root;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			Node*top = s.top();
			cout << top->_data << " ";
			s.pop();
			cur = top->_right;
		}
		cout << endl;
	}
	void PostOrderNoR()
	{
		stack<Node*>s;
		Node*cur = _root;
		Node*prev = NULL;
		while (cur || !s.empty())
		{
			while (cur)
			{
				//先遍历左子树
				s.push(cur);
				cur = cur->_left;
			}
			cur = s.top();
			if (cur->_right == NULL || cur->_right == prev)
			{
				//最后判断当前节点
				cout << cur->_data << " ";
				prev = cur;
				s.pop();
				cur = NULL;
			}
			else
			{
				//访问右子树
				cur = cur->_right;
			}
		}
		cout << endl;
	}
	void LevelOrder()
	{
		//层次遍历
		_LevelOrder(_root);
		cout << endl;
	}
	size_t Size()
	{
		//树的总节点
		size_t size = _Size(_root);
		return size;
	}
	size_t Depth()
	{
		//树的深度
		size_t depth = _Depth(_root);
		return depth;
	}
	size_t LeafSize()
	{
		//求叶子节点的总数
		size_t leaf = _LeafSize(_root);
		return leaf;
	}
	size_t GetKLevel(int level)
	{
		//level层的所以节点的个数
		size_t count =_GetKLevel(_root, level);
		return count;
	}
	Node*FindNode(const T&x = T())
	{
		return _FindNode(_root, x);
	}
protected:
	Node*_CreateTree(const T*array, size_t size, size_t&index, const T&invalid)
	{
		assert(array);
		Node*root = NULL;
		if (index < size&&array[index] != invalid)
		{
			root = new Node(array[index]);
			root->_left = _CreateTree(array, size, ++index, invalid);
			root->_right = _CreateTree(array, size, ++index, invalid);
		}
		return root;
	}
	Node*_Copy(Node*root)
	{
		Node*cur = root;
		Node*proot = NULL;
		if (cur)
		{
			proot = new Node(cur->_data);
			proot->_left = _Copy(cur->_left);
			proot->_right = _Copy(cur->_right);
		}
		return proot;
	}
	void _Destroy(Node*root)
	{
		Node*cur = root;
		if (cur)
		{
			_Destroy(cur->_left);
			_Destroy(cur->_right);
			delete cur;
			cur = NULL;
		}
	}
	void _PrevOrder(Node*root)
	{
		Node*cur = root;
		if (cur)
		{
			cout << cur->_data << " ";
			_PrevOrder(root->_left);
			_PrevOrder(root->_right);
		}
	}
	void _InOrder(Node*root)
	{
		Node*cur = root;
		if (cur)
		{
			_InOrder(cur->_left);
			cout << cur->_data << " ";
			_InOrder(cur->_right);
		}
	}
	void _PostOrder(Node*root)
	{
		Node*cur = root;
		if (cur)
		{
			_PostOrder(cur->_left);
			_PostOrder(cur->right);
			cout << cur->_data << " ";
		}
	}
	void _LevelOrder(Node*root)
	{
		queue<Node*>q;
		Node*cur = root;
		q.push(cur);
		while (!q.empty())
		{
			Node*front = q.front();
			cout << front->_data << " ";
			if (front->_left != NULL)
			{
				q.push(front->_left);
			}
			if (front->_right != NULL)
			{
				q.push(front->_right);
			}
			q.pop();
		}
	}
	size_t _Size(Node*root)
	{
		static size_t count = 0;
		if (root == NULL)
			return 0;
		count++;
		_Size(root->_left);
		_Size(root->_right);
		return count;
	}
	size_t _Depth(Node*root)
	{
		Node*cur = root;
		if (root == NULL)
		{
			return 0;
		}
		size_t depth1 = _Depth(cur->_left) + 1;
		size_t depth2 = _Depth(cur->_right) + 1;
		return depth1 > depth2 ? depth1 : depth2;
	}
	size_t _LeafSize(Node*root)
	{
		Node*cur = root;
		if (cur == NULL)
		{
			return 0;
		}
		else if ((cur->_left == NULL) && (cur->_right == NULL))
		{
			return 1;
		}
		else
		{
			return _LeafSize(cur->_left) + _LeafSize(cur->_right);
		}
	}
	size_t _GetKLevel(Node*root, int level)
	{
		size_t count = 0;
		if (root == NULL)
		{
			return 0;
		}
		if (level == 1)
		{
			count++;
		}
		else
		{
			count += _GetKLevel(root->_left, level - 1);
			count += _GetKLevel(root->_right, level - 1);
		}
		return count;
	}
	Node*_FindNode(Node*root, const T&x)
	{
		if (root == NULL)
			return NULL;
		if (root->_data == x)
			return root;
		Node*ret = _FindNode(root->_left, x);
		if (ret == NULL)
		{
			ret = _FindNode(root->_right, x);
		}
		return ret;
	}
};