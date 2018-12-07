#include <iostream>
#include <string>

using namespace std;

string result = "";

struct Node {
	string value;
	Node* next;
};

uint factorial0(uint n) {
	uint factorial = 1;

	for(uint i=2;i<=n;i++) 
		factorial *= i;

	return factorial;
}

uint factorial(uint n) {
	uint f = 1;

	while (n > 1) {
		for(uint i=3;i<=n;i+=2) 
			f *= i;
		n >>= 1;
		f <<= n;
	}

	return f;
}

// rotate and append c nodes from head to the end
void firstToLast(Node* &head, uint c) {
	Node* tail = nullptr;
	Node* node;

	// grow a tail  
	for(uint i=0;i<c;i++) {
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

	uint n = atoi(argv[1]);

	if (n < 1) {
		usage(argv[0]);
		return 1;
	}

	uint f = factorial(n-1);
	
	Node* next;
	Node* node = nullptr;
	Node* head = node;

	// create nodes
	for(uint i=n;i>0;i--) {
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

	uint len = n;

	for(uint i=1;i<=f;i++) {
		// print the ring
		printChain(head);

		for (uint j=1;j<n;j++) {
			firstToLast(head, 1);
			printChain(head);
			len++;
		}

		uint m = n - 1;
		uint mm = i;
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

