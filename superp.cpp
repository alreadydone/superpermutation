#include <iostream>
#include <string>
#include <fstream>

using namespace std;

std::ofstream outfile;
string spaces;

int len = 0;

struct Node {
	string value;
	Node* next;
};

Node* last_node;

// rotate and append c nodes from head to the end
void firstToLast(Node* &head, int c) {
	Node* tail = nullptr;
	Node* node;

	len += c;

	node = head;
	head = head->next;
	node->next = tail;
	tail = node;
	Node* tail_last = tail;

	// grow a tail  
	c--;
	for(int i=0;i<c;i++) {
		node = head;
		head = head->next;
		node->next = tail;
		tail = node;
	}

	node = last_node;

	// append to the end
	node->next = tail;
	last_node = tail_last;

	// append the tail to result string
	while(tail) {
		outfile << tail->value << spaces;
		tail = tail->next;
	}

}

void printChain(Node *head) {
	while(head) {
		cout << head->value << spaces;
		if (!head->next) break;
		head = head->next;
	}

	cout << endl;
}

void usage(char* argv) {
	cout << "Usage: " << argv << " number" << endl;
}

void rotateNprint(Node* &head, int n, int k, bool cando) {
	if (k <= n) {
		for (int i=0;i<k-1;i++) {
			rotateNprint(head, n, k+1, true);
		}

		rotateNprint(head, n, k+1, false);

		if (cando) {
			printChain(head);
			firstToLast(head, n-k+2);

			for (int j=0;j<n-k+1;j++) {
				cout << "===========" << endl;
			}
		}

	} else {
		if (cando) {
			printChain(head);
			firstToLast(head, 1);
		}
	}
}

void processChain(Node* &head, int n) {
	Node* node = head;

	while(node) {
		outfile << node->value << spaces;
		if (!node->next) break;
		node = node->next;
	}

	len = n;
	rotateNprint(head, n, 1, false);
	printChain(head);
	cout << "==============================================" << endl;
}

int main(int argc, char* argv[]) {
	if (argc != 2 ) {
		usage(argv[0]);
		return 1;
	}

	int n = atoi(argv[1]);

	if (n < 1) {
		usage(argv[0]);
		return 1;
	}

	if (n > 9) spaces = " ";

	outfile.open("superperm-"+to_string(n)+".txt");

	Node* next = nullptr;

	// create nodes
	Node *node = new Node({to_string(n), next});
	last_node = node;

	for(int i=n-1;i>0;i--) {
		next = node;
		node = new Node({to_string(i), next});
	}

	processChain(node, n);
	outfile.close();

	cout << "len=" << len << endl;

	return 0;
}
