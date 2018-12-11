#ifndef QUE_H
#define QUE_H

	typedef struct Node {
		int val;
		struct Node *next;
	} Node;

	typedef struct Que {
		Node *front, *back;
		int size;
	} Que;

	Node *new_node(int v);
	void free_node(Node* nd);

	int init_que(Que *q);
	void clear_que(Que *q);
	int is_empty_que(Que *q);
	int size_que(Que *q);
	int push_que(Que *q, int v);
	int pop_que(Que *q, int*v);

#endif
