#include <stdio.h>

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

TreeNode* search(TreeNode* node, int key)
{
	while (node != NULL)
	{
		if (key == node->data) return node;
		else if (key < node->data)
			node = node->left;
		else
			node = node->right;
	}
	return NULL;
}

// Treenode 생성
TreeNode n14 = { 64,NULL,NULL};
TreeNode n13 = { 62,NULL,NULL};
TreeNode n12 = { 42,NULL,NULL};
TreeNode n11 = { 70,NULL,NULL};
TreeNode n10 = { 63,&n13,&n14};
TreeNode n9 = { 55, NULL,NULL};
TreeNode n8 = { 46, &n12,NULL};
TreeNode n7 = { 25, NULL,NULL};
TreeNode n6 = { 65,&n10,&n11};
TreeNode n5 = { 53, &n8,&n9};
TreeNode n4 = { 16,NULL,&n7};
TreeNode n3 = { 74,&n6,NULL};
TreeNode n2 = { 41,&n4,&n5};
TreeNode n1 = { 60,&n2,&n3};

TreeNode* root = &n1;

int main()
{
	char menu_input;
	int input;

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
		printf("메뉴 입력 : ");
		scanf_s("%c", &menu_input);

		switch (menu_input)
		{
		case 's':
			printf("검색할 값 입력 : ");
			scanf_s("%d", &input);
			search(root, input);
			inorder_iter(root);
			printf("\n");
			break;
		case 't':
			inorder_iter(root);
			printf("\n");
			break;

		case 'c':
			printf("종료합니다\n");
			break;
		}

	} while (menu_input != 'c');
}

