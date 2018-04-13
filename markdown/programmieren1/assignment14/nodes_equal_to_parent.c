/*
Compile: make nodes_equal_to_parent
Run: ./nodes_equal_to_parent
Compile & run: make nodes_equal_to_parent && ./nodes_equal_to_parent
*/

#include "base.h"

typedef struct Node{
	int value;
	struct Node* left;
	struct Node* right;
}Node;

Node* new_node(Node* left, int value, Node* right){
	Node* node = xmalloc(sizeof(Node));
	node->left = left;
	node->value = value;
	node->right = right;
	return node;
}

void free_node(Node * node){
	if(node){
		free_node(node->left);
		free_node(node->right);
		node->left = NULL;
		node->right = NULL;
		free(node);
	}
}

void print_node(Node* node) {
	if (node == NULL) {
		printf("E");
	} else {
		printf("Node(");
		print_node(node->left);
		printf(", %d, ", node->value);
		print_node(node->right);
		printf(")");
	}
}

//todo
int number_of_nodes_that_are_equal_to_their_parent_nodes(Node* node) {
	int count = 0;
	if(node == NULL) {
		return 0;
	}
	count = number_of_nodes_that_are_equal_to_their_parent_nodes(node->left) + number_of_nodes_that_are_equal_to_their_parent_nodes(node->right);
	if(node->left != NULL) {
		if(node->value == node->left->value){
				count++;
		}
	}
	if(node->right != NULL) {
			if(node->right->value == node->value) {
				count++;
		}
	}
	return count;
}

typedef struct{
	Node* root;
}Tree;

Tree* new_tree(Node* root){
	Tree* tree = xmalloc(sizeof(Tree));
	tree->root = root;
	return tree;
}

void free_tree(Tree* tree){
	if(tree){
		free_node(tree->root);
		tree->root = NULL;
		free(tree);
	}
}

/** Returns the number of nodes that have the same value as their parent node.
      * May need a helper method. */
int number_of_nodes_that_are_equal_to_their_parent(Tree* tree) {
	if (tree->root == NULL) {
		return 0;
	} else {
		return number_of_nodes_that_are_equal_to_their_parent_nodes(tree->root);
	}
}
void print_tree(Tree* tree){
	printf("Tree: ");
	if(tree)
		print_node(tree->root);
	printf("\n");
}



void test() {
	Tree* t = new_tree(NULL);
	test_equal_i(number_of_nodes_that_are_equal_to_their_parent(t), 0);
	free_tree(t);

	t = new_tree(new_node(NULL, 100, NULL));
	test_equal_i(number_of_nodes_that_are_equal_to_their_parent(t), 0);
	free_tree(t);

	t = new_tree(new_node(new_node(NULL, 99, NULL), 100, new_node(NULL, 100, NULL)));
	test_equal_i(number_of_nodes_that_are_equal_to_their_parent(t), 1);
	free_tree(t);

	t = new_tree(new_node(new_node(NULL, 100, NULL), 100, new_node(NULL, 100, NULL)));
	test_equal_i(number_of_nodes_that_are_equal_to_their_parent(t), 2);
	free_tree(t);

	t = new_tree(new_node(new_node(NULL, 101, NULL), 100, new_node(NULL, 100, NULL)));
	test_equal_i(number_of_nodes_that_are_equal_to_their_parent(t), 1);
	free_tree(t);

	t = new_tree(new_node(new_node(new_node(NULL, 25, NULL), 50, new_node(NULL,75, NULL)), 100, new_node(new_node(NULL,125, NULL), 150, new_node(NULL, 175, NULL))));
	test_equal_i(number_of_nodes_that_are_equal_to_their_parent(t), 0);
	free_tree(t);

	t = new_tree(new_node(new_node(new_node(NULL, 0, NULL), 0, new_node(NULL, 0, NULL)), 0, new_node(new_node(NULL, 0, NULL), 0, new_node(NULL, 0, NULL))));
	test_equal_i(number_of_nodes_that_are_equal_to_their_parent(t), 6);
	free_tree(t);

	t = new_tree(new_node(NULL, 100, new_node(NULL, 100, NULL)));
	test_equal_i(number_of_nodes_that_are_equal_to_their_parent(t), 1);
	free_tree(t);

	t = new_tree(new_node(NULL, 100, new_node(NULL, 99, NULL)));
	test_equal_i(number_of_nodes_that_are_equal_to_their_parent(t), 0);
	free_tree(t);

	t = new_tree(new_node(new_node(NULL, 100, NULL), 100, NULL));
	test_equal_i(number_of_nodes_that_are_equal_to_their_parent(t), 1);
	free_tree(t);

}

int main(void) {
	base_init();
    base_set_memory_check(true);
	test();
	return 0;
}
