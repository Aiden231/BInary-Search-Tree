#include <stdio.h>
#include <stdlib.h>

// True False ����
#define TRUE 1
#define FALSE 0
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
// ����Ž��Ʈ�� Ž�� �Լ�
TreeNode* search(TreeNode* node, int key, int* visit_count, int* result)
{
	while (node != NULL)
	{
		(*visit_count)++;

		if (key == node->data)
		{
			printf("�˻� ���� : %d\n", key);
			*result = TRUE; // �˻� ���� �� rusult �� 1�� ����
			return node;
		}
		else if (key < node->data){
		node = node->left;
		}
		else {
			node = node->right;
		}
	}
	printf("�˻� ���� : %d\n", key);
	*result = FALSE; // �˻� ���� �� result �� 0 ���� ����
	return NULL;
}
// ���ο� ��� �߰�
TreeNode* new_node(int item)
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	if (temp == NULL)
	{
		// �޸� �Ҵ� ���� �� ���� ó��
		fprintf(stderr, "�޸� �Ҵ� ����\n");
		exit(1); // �Ǵ� �ٸ� ������ ��ġ�� ����
	}
	temp->data = item;
	temp->left = temp->right = NULL;
	return temp;
}
// ����Ž��Ʈ�� ���� ���� ( ����� ��� )
TreeNode* insert_node(TreeNode* node, int key, int* visit_count)
{
	(*visit_count)++; // �湮 ��� ī��Ʈ

	if (node == NULL) return new_node(key);

	if (key < node->data)
		node->left = insert_node(node->left, key,visit_count);
	else if (key > node->data)
		node->right = insert_node(node->right, key,visit_count);

	return node;
}
// ������ ��忡�� �ּҰ� ã��
TreeNode* min_value_node(TreeNode* node)
{
	TreeNode* current = node;

	while (current->left != NULL)
		current = current->left;

	return current;
}
// ����Ž��Ʈ�� ���� ���� ( ����� ��� )
TreeNode* delete_node(TreeNode* root, int key, int* visit_count)
{
	if (root == NULL) return root;

	(*visit_count)++; // �湮 ��� ī��Ʈ

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
		// �� �ڽ��� �ִ� ���
		TreeNode* temp = min_value_node(root->right);

		root->data = temp->data;
		root->right = delete_node(root->right, temp->data, visit_count);
	}
	return root;
}
// ����Ž��Ʈ�� ���� ���� ( �ݺ��� ��� )
TreeNode* insert_iteration(TreeNode* root, int key, int* visit_count)
{
	TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
	if (new_node == NULL)
	{
		// �޸� �Ҵ� ���� �� ���� ó��
		fprintf(stderr, "�޸� �Ҵ� ����\n");
		exit(1); // �Ǵ� �ٸ� ������ ��ġ�� ����
	}
	new_node->data = key;
	new_node->left = new_node->right = NULL;

	TreeNode* parent = NULL;
	TreeNode* current = root;

	while (current != NULL) {
		(*visit_count)++;
		parent = current;
		// �Է°��� ���� ���
		if (key < current->data) {
			current = current->left;
		}
		// �Է°��� ū ���
		else if (key > current->data) {
			current = current->right;
		}
	}

	if (parent == NULL) {
		// Ʈ���� ����ִ� ���
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
//����Ž��Ʈ�� �������� ( �ݺ��� ��� )
TreeNode* delete_iteration(TreeNode* root, int key, int* visit_count)
{
	// ��Ʈ ���
	TreeNode* current = root;
	// ������ ����� �θ� ���
	TreeNode* parent = NULL;

	// Ű�� ���� ��带 ã�� ������ �ݺ�
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
			// ������ ��带 ã��
			break;
		}
	}

	// Ʈ������ �ش� ��带 ã�� ���� ���
	if (current == NULL) {
		return root;
	}

	// ������ ��尡 �ڽ��� ���� ���
	if (current->left == NULL && current->right == NULL) {
		// ������ ��尡 ��Ʈ ����� ���
		if (current == root) {
			free(root);
			return NULL; // ��Ʈ�� NULL�� ������Ʈ
		}

		// �θ� ����� ��ũ�� ����
		if (parent->left == current) {
			parent->left = NULL;
		}
		else {
			parent->right = NULL;
		}

		free(current);
	}
	// ������ ��尡 �� ���� �ڽ��� ���� ���
	else if (current->left == NULL || current->right == NULL) {
		TreeNode* child = (current->left != NULL) ? current->left : current->right;

		// ������ ��尡 ��Ʈ ����� ���
		if (current == root) {
			free(root);
			return child; // �ڽ� ��带 ���ο� ��Ʈ�� ������Ʈ
		}

		// �θ� ����� ��ũ�� �ڽ� ���� ������Ʈ
		if (parent->left == current) {
			parent->left = child;
		}
		else {
			parent->right = child;
		}

		free(current);
	}
	// ������ ��尡 �� ���� �ڽ��� ���� ���
	else {
		// ������ ����Ʈ������ ���� ���� ���� ã��
		TreeNode* successorParent = current;
		TreeNode* successor = current->right;

		while (successor->left != NULL) {
			(*visit_count)++;
			successorParent = successor;
			successor = successor->left;
		}

		// �İ����� �����͸� ���� ���� ����
		current->data = successor->data;

		// �İ��� ��带 ����
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
// ���� �Լ� ����
int main()
{
	char menu_input = 0; // �޴� �Է� ����
	int input = 0; // �� �Է� ����
	int visit_count = 0; // �湮�� ��� ���� ī��Ʈ ����
	int result = NULL; // ã���Լ� �˻� ���

	//��� ����

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

	//�޴�
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
		visit_count = 0; // �湮 ��� �� �ʱ�ȭ

		printf("�޴� �Է� : ");
		scanf_s(" %c", &menu_input,10); // �޴� �Է� �ޱ�

		while (getchar() != '\n'); // �Է� ���� �����

		switch (menu_input)
		{
		case 's':
			printf("�˻��� �� �Է� : ");
			scanf_s("%d", &input);
			search(root, input, &visit_count, &result); // input �� ã��
			printf("�湮�� ����� �� : %d\n", visit_count);

			inorder_iter(root); // ���� ���
			printf("\n\n");
			break;
		case 'i':
			printf("������ �� �Է� : "); // �����Ϸ��� �� �Է� �ޱ�
			scanf_s("%d", &input);

			search(root, input, &visit_count, &result); // input �� ���� Ȯ��
			// �����Ϸ��� �� ���� ���� ��
			if (result == TRUE){
				printf("%d�� �̹� ����Ʈ�� �ȿ� �����մϴ�.\n", input);
			}
			// �����Ϸ��� �� ���� ���� ��
			else if (result == FALSE){
				printf("%d ��/�� ����Ʈ���� �߰��մϴ�.\n",input);
				insert_node(root, input, &visit_count);
				printf("�湮�� ����� �� : %d\n", visit_count);
			}

			inorder_iter(root); // ���� ���
			printf("\n\n");
			break;
		case 'd':
			printf("������ �� �Է� : "); // �����Ϸ��� �� �Է� �ޱ�
			scanf_s("%d", &input);

			search(root, input, &visit_count, &result); // input ���� Ȯ��
			// �����Ϸ��� �� ���� ��
			if (result == TRUE) {
				printf("%d ��/�� ����Ʈ������ �����մϴ�.\n", input);
				delete_node(root, input, &visit_count);
				printf("�湮�� ����� �� : %d\n", visit_count);
			}
			// �����Ϸ��� �� ���� ��
			else if (result == FALSE) {
				printf("%d�� ����Ʈ�� �ȿ� �������� �ʽ��ϴ�.\n", input);
			}

			inorder_iter(root); // ���� ���
			printf("\n\n");
			break;
		case 't':
			inorder_iter(root); // ���� ���
			printf("\n\n");
			break;
		case 'I':
			printf("������ �� �Է� : ");
			scanf_s("%d", &input);

			search(root, input, &visit_count, &result); // input �� ���� Ȯ��
			// �����Ϸ��� �� ���� ���� ��
			if (result == TRUE) {
				printf("%d�� �̹� ����Ʈ�� �ȿ� �����մϴ�.\n", input);
			}
			// �����Ϸ��� �� ���� ���� ��
			else if (result == FALSE) {
				printf("%d ��/�� ����Ʈ���� �߰��մϴ�.\n", input);
				insert_iteration(root, input, &visit_count); //���� �ݺ� ���
				printf("�湮�� ����� �� : %d\n", visit_count);
			}

			inorder_iter(root); // ���� ���
			printf("\n\n");
			break;
		case'D':
			printf("������ �� �Է� : ");
			scanf_s("%d", &input);

			search(root, input, &visit_count, &result); // input ���� Ȯ��
			// �����Ϸ��� �� ���� ��
			if (result == TRUE) {
				printf("%d ��/�� ����Ʈ������ �����մϴ�.\n", input);
				delete_iteration(root, input, &visit_count); // ���� �ݺ� ���
				printf("�湮�� ����� �� : %d\n", visit_count);
			}
			// �����Ϸ��� �� ���� ��
			else if (result == FALSE) {
				printf("%d�� ����Ʈ�� �ȿ� �������� �ʽ��ϴ�.\n", input);
			}

			inorder_iter(root); // ���� ���
			printf("\n\n");
			break;
		case 'c':
			printf("�����մϴ�\n\n");
			break;
		default:
			printf("�߸��� �Է��Դϴ�.\n\n");
			break;
		}
	} while (menu_input != 'c');

	return 0;
}

