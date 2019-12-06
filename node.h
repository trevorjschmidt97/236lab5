#ifndef node_h
#define node_h


#include <set>

using namespace std;

class node
{
private:
	set <int> children;
	bool visited = false;
	int postNum;
	int num;

public:
	set<int> getChildren() {
		return children;
	}

	void addChild(int input) {
		children.insert(input);
	}
	//if needed add a new dfs funtion for finding scc's

	void assignPost(int post) {
		postNum = post;
	}
	bool isVisited() {
		return visited;
	}
	int getPost() {
		return postNum;
	}
	void setNum(int input) {
		num = input;
	}
	int getNum() {
		return num;
	}
	void hasBeenVisited() {
		visited = true;
	}



};

#endif //node.h
