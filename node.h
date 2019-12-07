#ifndef node_h
#define node_h

#include <set>

using namespace std;

class node {
private:
	set <int> children;
	bool visited = false;
	int postNum;
	int num;
public:
	void addChild(int input) {
                children.insert(input);
        }
	set<int> getChildren() {
		return children;
	}

	void assignPost(int post) {
		postNum = post;
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
	bool isVisited() {
                return visited;
        }
};

#endif //node.h
