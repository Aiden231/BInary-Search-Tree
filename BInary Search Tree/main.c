#include <stdio.h>

//TreeNode ����ü
typedef struct treeNode {
	int data;
	struct treeNode* left, * right;
}TreeNode;

// ���� ����
#define SIZE 100
int top = -1;
TreeNode* stack[SIZE];

// ���� �Լ�
void push(TreeNode* p)
{
	if (top < SIZE - 1) {
		stack[++top] = p;
	}
}

// ���� �Լ�
TreeNode* pop()
{
	TreeNode* p = NULL;
	if (top >= 0) {
		p = stack[top--];
	}
	return p;
}

// ���� ��ȸ ��� �Լ�
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

// Treenode ����
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
	printf("| s : �˻�           |\n");
	printf("| i : ��� �߰�      |\n");
	printf("| d : ��� ����      |\n");
	printf("| t : ���� ��ȸ      |\n");
	printf("| I : ��� �߰�(�ݺ�)|\n");
	printf("| D : ��� ����(�ݺ�)|\n");
	printf("| c : ����           |\n");
	printf("----------------------\n");
	printf("\n\n");

	do
	{
		printf("�޴� �Է� : ");
		scanf_s("%c", &menu_input);

		switch (menu_input)
		{
		case 's':
			printf("�˻��� �� �Է� : ");
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
			printf("�����մϴ�\n");
			break;
		}

	} while (menu_input != 'c');
}

