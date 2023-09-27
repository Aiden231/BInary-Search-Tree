#include <stdio.h>
#include <stdlib.h>

// True False 정의
#define TRUE 1
#define FALSE 0
//TreeNode 구조체
typedef struct treeNode {
	int data;
	struct treeNode* left, * right;
}TreeNode;
// 스택 생성
#define SIZE 100
int top = -1;
TreeNode* stack[SIZE];
// 삽입 함수
void push(TreeNode* p)
{
	if (top < SIZE - 1) {
		stack[++top] = p;
	}
}
// 삭제 함수
TreeNode* pop()
{
	TreeNode* p = NULL;
	if (top >= 0) {
		p = stack[top--];
	}
	return p;
}
// 중위 순회 출력 함수
void inorder_iter(TreeNode* root)
{
	while (1) {
		for (; root; root = root->left)
			push(root);
		root = pop();
		if (!root) break;
		printf("%d ", root->data);
		root = root->right;
	}
}
// 이진탐색트리 탐색 함수
TreeNode* search(TreeNode* node, int key, int* visit_count, int* result)
{
	while (node != NULL)
	{
		(*visit_count)++;

		if (key == node->data)
		{
			printf("검색 성공 : %d\n", key);
			*result = TRUE; // 검색 성공 시 rusult 값 1로 설정
			return node;
		}
		else if (key < node->data){
		node = node->left;
		}
		else {
			node = node->right;
		}
	}
	printf("검색 실패 : %d\n", key);
	*result = FALSE; // 검색 실패 시 result 값 0 으로 설정
	return NULL;
}
// 새로운 노드 추가
TreeNode* new_node(int item)
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	if (temp == NULL)
	{
		// 메모리 할당 실패 시 에러 처리
		fprintf(stderr, "메모리 할당 실패\n");
		exit(1); // 또는 다른 적절한 조치를 취함
	}
	temp->data = item;
	temp->left = temp->right = NULL;
	return temp;
}
// 이진탐색트리 삽입 연산 ( 재귀적 방법 )
TreeNode* insert_node(TreeNode* node, int key, int* visit_count)
{
	(*visit_count)++; // 방문 노드 카운트

	if (node == NULL) return new_node(key);

	if (key < node->data)
		node->left = insert_node(node->left, key,visit_count);
	else if (key > node->data)
		node->right = insert_node(node->right, key,visit_count);

	return node;
}
// 오른쪽 노드에서 최소값 찾기
TreeNode* min_value_node(TreeNode* node)
{
	TreeNode* current = node;

	while (current->left != NULL)
		current = current->left;

	return current;
}
// 이진탐색트리 삭제 연산 ( 재귀적 방법 )
TreeNode* delete_node(TreeNode* root, int key, int* visit_count)
{
	if (root == NULL) return root;

	(*visit_count)++; // 방문 노드 카운트

	if (key < root->data)
		root->left = delete_node(root->left, key, visit_count);
	else if (key > root->data)
		root->right = delete_node(root->right, key, visit_count);
	else {
		if (root->left == NULL) {
			TreeNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}
		// 두 자식이 있는 경우
		TreeNode* temp = min_value_node(root->right);

		root->data = temp->data;
		root->right = delete_node(root->right, temp->data, visit_count);
	}
	return root;
}
// 이중탐색트리 삽입 연산 ( 반복적 방법 )
TreeNode* insert_iteration(TreeNode* root, int key, int* visit_count)
{
	TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
	if (new_node == NULL)
	{
		// 메모리 할당 실패 시 에러 처리
		fprintf(stderr, "메모리 할당 실패\n");
		exit(1); // 또는 다른 적절한 조치를 취함
	}
	new_node->data = key;
	new_node->left = new_node->right = NULL;

	TreeNode* parent = NULL;
	TreeNode* current = root;

	while (current != NULL) {
		(*visit_count)++;
		parent = current;
		// 입력값이 작은 경우
		if (key < current->data) {
			current = current->left;
		}
		// 입력값이 큰 경우
		else if (key > current->data) {
			current = current->right;
		}
	}

	if (parent == NULL) {
		// 트리가 비어있는 경우
		return new_node;
	}
	else if (key < parent->data) {
		parent->left = new_node;
	}
	else {
		parent->right = new_node;
	}

	return root;
}
//이진탐색트리 삭제연산 ( 반복적 방법 )
TreeNode* delete_iteration(TreeNode* root, int key, int* visit_count)
{
	// 루트 노드
	TreeNode* current = root;
	// 삭제할 노드의 부모 노드
	TreeNode* parent = NULL;

	// 키를 가진 노드를 찾을 때까지 반복
	while (current != NULL) {
		(*visit_count)++;
		if (key < current->data) {
			parent = current;
			current = current->left;
		}
		else if (key > current->data) {
			parent = current;
			current = current->right;
		}
		else {
			// 삭제할 노드를 찾음
			break;
		}
	}

	// 트리에서 해당 노드를 찾지 못한 경우
	if (current == NULL) {
		return root;
	}

	// 삭제할 노드가 자식이 없는 경우
	if (current->left == NULL && current->right == NULL) {
		// 삭제할 노드가 루트 노드인 경우
		if (current == root) {
			free(root);
			return NULL; // 루트를 NULL로 업데이트
		}

		// 부모 노드의 링크를 끊음
		if (parent->left == current) {
			parent->left = NULL;
		}
		else {
			parent->right = NULL;
		}

		free(current);
	}
	// 삭제할 노드가 한 개의 자식을 가진 경우
	else if (current->left == NULL || current->right == NULL) {
		TreeNode* child = (current->left != NULL) ? current->left : current->right;

		// 삭제할 노드가 루트 노드인 경우
		if (current == root) {
			free(root);
			return child; // 자식 노드를 새로운 루트로 업데이트
		}

		// 부모 노드의 링크를 자식 노드로 업데이트
		if (parent->left == current) {
			parent->left = child;
		}
		else {
			parent->right = child;
		}

		free(current);
	}
	// 삭제할 노드가 두 개의 자식을 가진 경우
	else {
		// 오른쪽 서브트리에서 가장 작은 값을 찾음
		TreeNode* successorParent = current;
		TreeNode* successor = current->right;

		while (successor->left != NULL) {
			(*visit_count)++;
			successorParent = successor;
			successor = successor->left;
		}

		// 후계자의 데이터를 현재 노드로 복사
		current->data = successor->data;

		// 후계자 노드를 삭제
		if (successorParent->left == successor) {
			successorParent->left = successor->right;
		}
		else {
			successorParent->right = successor->right;
		}

		free(successor);
	}

	return root;
}
// 메인 함수 시작
int main()
{
	char menu_input = 0; // 메뉴 입력 변수
	int input = 0; // 값 입력 변수
	int visit_count = 0; // 방문한 노드 개수 카운트 변수
	int result = NULL; // 찾기함수 검색 결과

	//노드 생성

	TreeNode* root = NULL;
	root = insert_node(root, 60, &visit_count);
	root = insert_node(root, 41, &visit_count);
	root = insert_node(root, 74, &visit_count);
	root = insert_node(root, 16, &visit_count);
	root = insert_node(root, 53, &visit_count);
	root = insert_node(root, 65, &visit_count);
	root = insert_node(root, 25, &visit_count);
	root = insert_node(root, 46, &visit_count);
	root = insert_node(root, 55, &visit_count);
	root = insert_node(root, 63, &visit_count);
	root = insert_node(root, 70, &visit_count);
	root = insert_node(root, 42, &visit_count);
	root = insert_node(root, 62, &visit_count);
	root = insert_node(root, 64, &visit_count);

	//메뉴
	printf("----------------------\n");
	printf("| s : 검색           |\n");
	printf("| i : 노드 추가      |\n");
	printf("| d : 노드 삭제      |\n");
	printf("| t : 중위 순회      |\n");
	printf("| I : 노드 추가(반복)|\n");
	printf("| D : 노드 삭제(반복)|\n");
	printf("| c : 종료           |\n");
	printf("----------------------\n");
	printf("\n\n");

	do
	{
		visit_count = 0; // 방문 노드 값 초기화

		printf("메뉴 입력 : ");
		scanf_s(" %c", &menu_input,10); // 메뉴 입력 받기

		while (getchar() != '\n'); // 입력 버퍼 지우기

		switch (menu_input)
		{
		case 's':
			printf("검색할 값 입력 : ");
			scanf_s("%d", &input);
			search(root, input, &visit_count, &result); // input 값 찾기
			printf("방문한 노드의 수 : %d\n", visit_count);

			inorder_iter(root); // 중위 출력
			printf("\n\n");
			break;
		case 'i':
			printf("삽입할 값 입력 : "); // 삽입하려고 값 입력 받기
			scanf_s("%d", &input);

			search(root, input, &visit_count, &result); // input 값 유뮤 확인
			// 삽입하려고 한 값이 있을 때
			if (result == TRUE){
				printf("%d은 이미 이진트리 안에 존재합니다.\n", input);
			}
			// 삽입하려고 한 값이 없을 떄
			else if (result == FALSE){
				printf("%d 을/를 이진트리에 추가합니다.\n",input);
				insert_node(root, input, &visit_count);
				printf("방문한 노드의 수 : %d\n", visit_count);
			}

			inorder_iter(root); // 중위 출력
			printf("\n\n");
			break;
		case 'd':
			printf("삭제할 값 입력 : "); // 삭제하려는 값 입력 받기
			scanf_s("%d", &input);

			search(root, input, &visit_count, &result); // input 유무 확인
			// 삭제하려는 값 있을 때
			if (result == TRUE) {
				printf("%d 을/를 이진트리에서 삭제합니다.\n", input);
				delete_node(root, input, &visit_count);
				printf("방문한 노드의 수 : %d\n", visit_count);
			}
			// 삭제하려는 값 없을 때
			else if (result == FALSE) {
				printf("%d은 이진트리 안에 존재하지 않습니다.\n", input);
			}

			inorder_iter(root); // 중위 출력
			printf("\n\n");
			break;
		case 't':
			inorder_iter(root); // 중위 출력
			printf("\n\n");
			break;
		case 'I':
			printf("삽입할 값 입력 : ");
			scanf_s("%d", &input);

			search(root, input, &visit_count, &result); // input 값 유뮤 확인
			// 삽입하려고 한 값이 있을 때
			if (result == TRUE) {
				printf("%d은 이미 이진트리 안에 존재합니다.\n", input);
			}
			// 삽입하려고 한 값이 없을 떄
			else if (result == FALSE) {
				printf("%d 을/를 이진트리에 추가합니다.\n", input);
				insert_iteration(root, input, &visit_count); //삽입 반복 방법
				printf("방문한 노드의 수 : %d\n", visit_count);
			}

			inorder_iter(root); // 중위 출력
			printf("\n\n");
			break;
		case'D':
			printf("삭제할 값 입력 : ");
			scanf_s("%d", &input);

			search(root, input, &visit_count, &result); // input 유무 확인
			// 삭제하려는 값 있을 때
			if (result == TRUE) {
				printf("%d 을/를 이진트리에서 삭제합니다.\n", input);
				delete_iteration(root, input, &visit_count); // 삭제 반복 방법
				printf("방문한 노드의 수 : %d\n", visit_count);
			}
			// 삭제하려는 값 없을 때
			else if (result == FALSE) {
				printf("%d은 이진트리 안에 존재하지 않습니다.\n", input);
			}

			inorder_iter(root); // 중위 출력
			printf("\n\n");
			break;
		case 'c':
			printf("종료합니다\n\n");
			break;
		default:
			printf("잘못된 입력입니다.\n\n");
			break;
		}
	} while (menu_input != 'c');

	return 0;
}

