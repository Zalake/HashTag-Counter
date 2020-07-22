#include <string>
class Node {
	public:
		int Degree, data;
		Node* leftSibling;
		Node* rightSibling;
		Node* child; 
		Node* parent;
		std::string hashTag;
		bool childCut;
		Node();
		Node(int data, std::string hashTag);
		int getData();
};

