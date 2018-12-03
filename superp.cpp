#include <iostream>
#include <string>

struct Node {
	int value;
	Node* next;
};

// rotate and append c nodes from root to the end
void firstToLast(Node* &root, int c) {
	Node* tail = nullptr;
	Node* node;

	// grow a tail  
	for(int i=0;i<c;i++) {
		node = root;
		root = root->next;
		node->next = tail;
		tail = node;
	}

	node = root;

	// find the end
	while(node->next) {
		node = node->next;
	}

	// append to the end
	node->next = tail;
}

int main(int argv, char** argc)
{
	using namespace std;
	int n = 4;
	string result;

	// count factorial of n
	int factorial = 1;
	for(int i=2;i<=n;i++) 
		factorial *= i;
	
	Node* next;
	Node* last;
	Node* node = nullptr;
	Node* root = node;

	for(int i=n;i>0;i--) {
		next = node;
		node = new Node();
		node->value = i;
		node->next = next;
	}

	root = node;

	int sum = n;

	for(int i=1;i<=factorial;i++) {
		while(node) {
			cout << node->value;// << " ";
			if (!node->next) break;
			node = node->next;
		}

		cout << endl;

		// check divisibility
		int m = n;
		int mm = m;

		while (m > 0) {
			if (i%mm == 0) {
				cout << "==========" << endl;
				mm *= --m;
			} else {
				sum+=n-m+1;
				firstToLast(root, n-m+1);
				break;
			}
		}
		//*/
		node = root;
	}

	cout << "sum=" << sum << endl;

	return 0;
}

