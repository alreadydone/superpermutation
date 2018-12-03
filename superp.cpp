#include <iostream>
#include <string>

using namespace std;

string result = "";

struct Node {
	string value;
	Node* next;
};

int factorial(int n) {
	if (n <= 0) return 1;
	int factorial = 1;

	for(int i=2;i<=n;i++) 
		factorial *= i;

	return factorial;
}

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

	// append the tail to result string
	while(tail) {
		result += tail->value;// << " ";
		if (!tail->next) break;
		tail = tail->next;
	}

}

void printChain(Node *root) {
	while(root) {
		cout << root->value;// << " ";
		if (!root->next) break;
		root = root->next;
	}

	cout << endl;
}

int main(int argc, char* argv[])
{
	if (argc != 2) {
		cout << "Usage: " << argv[0] << " number" << endl;
		return 1;
	}

	int n = atoi(argv[1]);

	int fact = factorial(n);
	
	Node* next;
	Node* node = nullptr;
	Node* root = node;

	// create nodes
	for(int i=n;i>0;i--) {
		next = node;
		node = new Node();
		node->value = to_string(i);
		node->next = next;
	}

	root = node;

	while(node) {
		result += node->value;// << " ";
		if (!node->next) break;
		node = node->next;
	}

	int sum = n;

	for(int i=1;i<=fact;i++) {
		printChain(root);

		// check divisibility
		int m = n;
		int mm = i;

		while (m > 0) {
			if (mm%m == 0) {
				cout << "==========" << endl;
				mm /= m--;
			} else {
				sum += n - m + 1;
				firstToLast(root, n - m + 1);
				break;
			}
		}
	}

	cout << "sum=" << sum << endl;
	cout << "string=" << result << endl;

	return 0;
}

