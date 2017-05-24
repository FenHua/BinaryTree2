// BinaryTree2.cpp : 定义控制台应用程序的入口点。
//
#include"BinaryTree.h"
#include"iostream"
using namespace std;
void test()
{
	int array[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	size_t size = sizeof(array) / sizeof(array[0]);
	BinaryTree<int>bt(array, size, '#');
	cout << "前序遍历>";
	bt.PrevOrderNoR();   //1  2  3  4  5  6  
	cout << "中序遍历>";
	bt.InOrderNoR();     //3  2  4  1  6  5  
	cout << "后序遍历>";
	bt.PostOrderNoR();   //3  4  2  6  5  1  
	cout << "层序遍历>";
	bt.LevelOrder();     //1  2  5  3  4  6  
	cout << "Size>" << bt.Size() << endl;
	cout << "Depth:" << bt.Depth() << endl;
	cout << "LeafSize:" << bt.LeafSize() << endl;   //3    
	cout << "Level1:" << bt.GetKLevel(1) << endl;  //1  
	cout << "Level2:" << bt.GetKLevel(2) << endl;  //2  
	cout << "Level3:" << bt.GetKLevel(3) << endl; //3 
	BinaryTreeNode<int>*ret = bt.FindNode(6);
	assert(ret);
	cout << "FindNode:6>" << ret->_data << endl;
	ret = bt.FindNode(10);
	cout <<"FindNode:10>"<<ret<< endl;
}
int main()
{
	test();
	system("pause");
	return  0;
}