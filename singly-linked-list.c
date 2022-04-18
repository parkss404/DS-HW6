/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>


typedef struct Node {
	int key;
	struct Node* link;
}listNode;

typedef struct Head {
	struct Node* first;
}headNode;
//필요한 구조체 선언

headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
        [----- [박성준] [2021040026] -----]
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	// headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제
	if(h != NULL)
		freeList(h);

	// headNode에 대한 메모리를 할당하여 리턴 
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp; //initial시 받게되는 first값은 null상태로  
}

int freeList(headNode* h){

	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}
//listNode 메모리 해제
//headNode 메모리 해제
	 

// 리스트를 검색 후 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key; //입력받은 수 
	node->link = NULL; //주소는 null

	if (h->first == NULL)//h->first가 null값일 경우에 
	{
		h->first = node; // h->first를 node로 
		return 0;
	}

	listNode* n = h->first; //first값에 listNode의 주소값을 넣는다. = n
	listNode* trail = h->first; //first값에 listNode의 주소값을 넣는다. = trail

	// key를 통해 삽입위치를 찾는다 
	while(n != NULL) {
		if(n->key >= key) {// 있던 key가 들어올 key보다 클 때
			/* 첫 노드 앞쪽에 삽입해야 할 경우 인지 검사 */
			if(n == h->first) { //시작 시 
				h->first = node; //listNode의 주소값이 대입됨
				node->link = n; //h->first의 주소를 나타내는 n으로 
			} else { // 중간,마지막 부분
				node->link = n; //link값에 n넣기
				trail->link = node;//trail값에 n넣기
			}
			return 0;
		}

		trail = n; //trail = 삽입할 위치
		n = n->link;// n->link로 바뀌며 반복문 진행
	}

	// 마지막 노드까지 key보다 큰값이 없는 경우 마지막에 삽입
	trail->link = node;
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key; //입력받은 수 
	node->link = NULL;//주소는 null

	if (h->first == NULL) //처음인 경우
	{ 
		h->first = node; //node값(받은 키값과 null이 있는 주소)을 h->first에  
		return 0;
	}

	listNode* n = h->first; //first값을 리스트노드의 주소 값에 넣기 
	while(n->link != NULL) {
		n = n->link; //n의 값을 계속 변경하면서 n->link가 null이 될때까지 기다리고,
	}
	n->link = node; //null이 되었을때가 마지막일테니, 이때 node값을 대입함으로써, 새로운 리스트를 연결해준다. 
	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); 
	node->key = key; //key값 저장

	node->link = h->first; //node link 부분을 h의 첫번째 부분으로 바꾸고
	h->first = node; //h->first가 node로 바뀌면, 첫번째와 연결됨.

	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}//비어있을경우 

	listNode* n = h->first;
	listNode* trail = NULL; //n과 trail 정의

	// key를 기준으로 삽입할 위치를 찾는다 
	while(n != NULL) {
		if(n->key == key) {
			// 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 
			if(n == h->first) {//n이 첫 주소를 가르킬 경우에,
				h->first = n->link; //첫번째 주소를 n의 link값으로 설정 (연결 끊기)
			} else { // 중간인 경우거나 마지막인 경우 
				trail->link = n->link; //중간에서, trail의 링크값을 n의 링크로 교체(trail은 n의 한 시기 이전)
			}
			free(n); 
			return 0;
		}

		trail = n; //trail 변경
		n = n->link;//n변경 (n의 값을 n의 link값으로)
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}//비어있을경우

	listNode* n = h->first;
	listNode* trail = NULL; //n과 trail 정의

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->link == NULL) {//마지막 노드일 경우, 
		h->first = NULL;//h->first을 null로 
		free(n);
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->link != NULL) {
		trail = n; 
		n = n->link; //n의 값을 계속 변경하면서 n->link가 null이 될때까지 기다리고,
	}

	trail->link = NULL;//n의 한단계 전으로 기록된 trail값의 link를 NULL로 연결고리 끊기
	free(n); 

	return 0;
}
/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL) //h->first가 null일때
	{ 
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first; //첫번째 주소값을 n으로 하는 

	h->first = n->link; //h->first를 n의 링크로 변경 첫번째 연결 끊기
	free(n); 

	return 0;
} 


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {


	if(h->first == NULL) { 
		printf("nothing to invert...\n");
		return 0;
	}//다음 노드가 없을 경우에, 
	listNode *n = h->first; 
	listNode *trail = NULL;
	listNode *middle = NULL; // n,trail,middle 정의

	while(n != NULL){ //마지막 노드까지
		trail = middle; 
		middle = n; 
		n = n->link;
		middle->link = trail;
	}// trail,middle,n을 이용해서 주소 정보 반대로 변경 

	h->first = middle;//시작 주소를 기존의 가장 마지막 노드에 가장

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	} //아무것도 없을때

	p = h->first;

	while(p != NULL) { 
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	} //반복문을 통해서 리스트 출력

	printf("  items = %d\n", i); 
}

