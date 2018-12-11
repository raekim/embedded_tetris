#include <stdlib.h>
#include "que.h"

Node *new_node(int v){
	Node *ret;
	ret = malloc(sizeof(Node));

	if (ret == NULL)
		return NULL;

	ret->next = NULL;
	ret->val = v;
	return ret;
}

void free_node(Node* nd){
	free(nd);
	return;
}

int init_que(Que *q){
	q->front = q->back = NULL;
	q->size = 0;

	return 0;
}

void clear_que(Que *q){
	int tmp;

	while (!is_empty_que(q))
		pop_que(q, &tmp);

	return;
}

int is_empty_que(Que *q) {
	return q->size == 0;
}

int size_que(Que *q){
	return q->size;
}

int push_que(Que *q, int v) {
	Node *add = new_node(v);

	if (add == NULL)
		return -1;

	if (q->back == NULL)
		q->front = add;
	else 
		q->back->next = add;

	q->back = add;
	q->size++;

	return 0;
}

int pop_que(Que *q, int *v) {
	Node *del;

	if (is_empty_que(q))
		return -1; 

	del = q->front;

	if (q->front == q->back)
		q->back = NULL;

	q->front = q->front->next;

	*v = del->val;
	free_node(del);

	q->size--;

	return 0;
}
