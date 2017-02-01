#include<iostream>
#include<vector>
#include<algorithm>
#define MIN2(A,B) A<B?A:B
using namespace std;

struct volStatusNode
{
	int volA = 0, volB = 0, volC = 0, tLeft = 0;
	int* volPointer[3];
	volStatusNode() { volPointer[0] = &volA;	volPointer[1] = &volB;	volPointer[2] = &volC; }
	volStatusNode(const volStatusNode& node) { volPointer[0] = &volA;	volPointer[1] = &volB;	volPointer[2] = &volC; volA = node.volA; volB = node.volB; volC = node.volC; tLeft = node.tLeft; }
	bool operator==(const volStatusNode& n) { if ((volA == n.volA) && (volB == n.volB) && (volC == n.volC) && (tLeft == n.tLeft)) return true; else return false; }
};
class bottleSwap
{
	int bottleA = 0, bottleB = 0, bottleC = 0, tLimit = 0;
	int* bottlePointer[3];
	volStatusNode rootNode;
	vector<int> possibleVolC;	
	void nextAvailable(volStatusNode, bool[], short);
	volStatusNode oneStep(volStatusNode, short, short);
	void swapRecursion(volStatusNode, short);
public:
	bottleSwap(int, int, int, int);
	void setInitial(int, int, int, int);
	void startSwap();
};
bottleSwap::bottleSwap(int a = 0, int b = 0, int c = 0, int t = 0)
{
	bottleA = a; bottleB = b; bottleC = c; tLimit = t; possibleVolC.reserve(c);
	bottlePointer[0] = &bottleA; bottlePointer[1] = &bottleB; bottlePointer[2] = &bottleC;
	rootNode.volC = c; rootNode.tLeft = t;
}
void bottleSwap::setInitial(int a, int b, int c, int t)
{
	bottleA = a; bottleB = b; bottleC = c; tLimit = t; 
	possibleVolC.clear();	possibleVolC.reserve(c); 
	cout << a << ", " << b << ", " << c << " : ";
	rootNode.volA = 0; rootNode.volB = 0; rootNode.volC = c; rootNode.tLeft = t;
}
void bottleSwap::nextAvailable(volStatusNode cur_node, bool sign[6], short lastMove)
{
	if (cur_node.volA > 0)
	{
		if (cur_node.volB < bottleB) sign[0] = true; else sign[0] = false;
		if (cur_node.volC < bottleC) sign[1] = true; else sign[1] = false;
	}
	if (cur_node.volB > 0)
	{
		if (cur_node.volA < bottleA) sign[2] = true; else sign[2] = false;
		if (cur_node.volC < bottleC) sign[3] = true; else sign[3] = false;
	}
	if (cur_node.volC > 0)
	{
		if (cur_node.volA < bottleA) sign[4] = true; else sign[4] = false;
		if (cur_node.volB < bottleB) sign[5] = true; else sign[5] = false;
	}
	if(lastMove>=0)	sign[lastMove] = false;
}
volStatusNode bottleSwap::oneStep(volStatusNode cur_node, short source, short destination)
{
	volStatusNode result = cur_node; int movVol = MIN2(*cur_node.volPointer[source], *bottlePointer[destination] - *cur_node.volPointer[destination]);
	*result.volPointer[source] -= movVol;
	*result.volPointer[destination] += movVol;	result.tLeft--;
	return result;
}
void bottleSwap::swapRecursion(volStatusNode cur_node, short lastMove)
{
	bool swapSign[6] = { 0 };
	if (cur_node.volA == 0)
	{
		vector<int>::iterator i = find(possibleVolC.begin(), possibleVolC.end(), cur_node.volC);
		if (i == possibleVolC.end()) possibleVolC.push_back(cur_node.volC);
	}
	if (cur_node.tLeft == 0) return;
	nextAvailable(cur_node, swapSign, lastMove);
	if (swapSign[0])	swapRecursion(oneStep(cur_node, 0, 1), 0);
	if (swapSign[1])	swapRecursion(oneStep(cur_node, 0, 2), 1);
	if (swapSign[2])	swapRecursion(oneStep(cur_node, 1, 0), 2);
	if (swapSign[3])	swapRecursion(oneStep(cur_node, 1, 2), 3);
	if (swapSign[4])	swapRecursion(oneStep(cur_node, 2, 0), 4);
	if (swapSign[5])	swapRecursion(oneStep(cur_node, 2, 1), 5);
}
void bottleSwap::startSwap()
{
	swapRecursion(rootNode, -1);
	sort(possibleVolC.begin(), possibleVolC.end()); cout << *possibleVolC.begin();
	for (vector<int>::iterator i = possibleVolC.begin() + 1; i < possibleVolC.end(); i++) cout << " " << *i; cout << endl;
}

int main()
{
	int volBottleA, volBottleB, volBottleC, tLimit = 8;
	cin >> volBottleA >> volBottleB >> volBottleC;
	bottleSwap G(volBottleA, volBottleB, volBottleC, tLimit);
	G.startSwap();
	/*bottleSwap G;
	for (int i = 0; i < 20; i++)
	{
		G.setInitial(rand() % 20, rand() % 20, rand() % 20, tLimit);
		G.startSwap();
	}*/
	return 0;
}