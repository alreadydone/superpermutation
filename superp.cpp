#include <iostream>
#include <string>
#include <fstream>

using namespace std;

std::ofstream outfile;

int len = 0;

struct Node {
	string value;
	Node* next;
};

// rotate and append c nodes from head to the end
void firstToLast(Node* &head, int c) {
	Node* tail = nullptr;
	Node* node;

	len += c;

	// grow a tail  
	for(int i=0;i<c;i++) {
		node = head;
		head = head->next;
		node->next = tail;
		tail = node;
	}

	node = head;

	// find the end
	while(node->next) {
		node = node->next;
	}

	// append to the end
	node->next = tail;

	// append the tail to result string
	while(tail) {
		outfile << tail->value << " ";
		if (!tail->next) break;
		tail = tail->next;
	}

}

void printChain(Node *head) {
	while(head) {
		cout << head->value << " ";
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

	outfile.open("superperm-"+to_string(n)+".txt");

	Node* next;
	Node* head;
	Node* node = nullptr;

	// create nodes
	for(int i=n;i>0;i--) {
		next = node;
		node = new Node({to_string(i), next});
	}

	head = node;

	while(node) {
		outfile << node->value << " ";
		if (!node->next) break;
		node = node->next;
	}

	processChain(head, n);

	outfile.close();

	cout << "len=" << len << endl;
	
	return 0;
}
