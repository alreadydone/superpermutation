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

// rotate and append c nodes from head to the end
void firstToLast(Node* &head, int c) {
	Node* tail = nullptr;
	Node* node;

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
		result += tail->value;// << " ";
		if (!tail->next) break;
		tail = tail->next;
	}

}

void printChain(Node *head) {
	while(head) {
		cout << head->value;// << " ";
		if (!head->next) break;
		head = head->next;
	}

	cout << endl;
}

void usage(char* argv) {
	cout << "Usage: " << argv << " number" << endl;
}

int main(int argc, char* argv[])
{
	if (argc != 2 ) {
		usage(argv[0]);
		return 1;
	}

	int n = atoi(argv[1]);

	if (n < 1) {
		usage(argv[0]);
		return 1;
	}

	int f = factorial(n) / n;
	
	Node* next;
	Node* node = nullptr;
	Node* head = node;

	// create nodes
	for(int i=n;i>0;i--) {
		next = node;
		node = new Node();
		node->value = to_string(i);
		node->next = next;
	}

	head = node;

	while(node) {
		result += node->value;// << " ";
		if (!node->next) break;
		node = node->next;
	}

	int len = n;

	for(int i=1;i<=f;i++) {
		// print the ring
		printChain(head);

		for (int j=1;j<n;j++) {
			firstToLast(head, 1);
			printChain(head);
			len += 1;
		}

		int m = n - 1;
		int mm = i;
		cout << "==========" << endl;

		// check divisibility
		while (m > 0) {
			if (mm%m == 0) {
				cout << "==========" << endl;
				mm /= m--;
			} else {
				len += n - m + 1;
				firstToLast(head, n - m + 1);
				break;
			}
		}
	}

	cout << "string=" << result << endl;
	cout << "len=" << len << endl;

	return 0;
}

