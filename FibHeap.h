#include "Node.h"
class FibHeap
{
public:
	Node* max;
	int totalNodes;// total number of nodes in the root list
	FibHeap();
	void insert(Node* node);
	void increaseCount(Node* node,int value);
	void pairWiseCombine(FibHeap* fHeap);
	Node* removeMax();
	void cut(FibHeap* fHeap, Node* node, Node* parent);
	void cascadeCut(FibHeap* fHeap, Node* parent);
	void combine(Node* x, Node* y);
};

