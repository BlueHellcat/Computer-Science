/*
Compile: make is_search_tree
Run: ./is_search_tree
Compile & run: make is_search_tree && ./is_search_tree
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

int min_int(int a, int b){
	if(a < b){
		return a;
	}
	return b;
}

int max_int(int a, int b){
	if(a > b){
		return a;
	}
	return b;
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

void print_tree(Tree* tree){
	printf("Tree: ");
	if(tree)
		print_node(tree->root);
	printf("\n");
}

int number_of_nodes(Node* tree) {
	int number = 1;
	if(tree == NULL) {
		return 0;
	} else {
		number = number + number_of_nodes(tree->left) + number_of_nodes(tree->right);
	}
	return number;
}
int number_of_nodes_rec(Tree* tree){
	return number_of_nodes(tree->root);
}
int highest_node_value(Node* tree, int max) {
	if(tree->value > max) {
		max = tree->value;
	}
	if(tree == NULL){
		return 0;
	}
	else {
		if(tree->left != NULL) {
			max = max_int(max,highest_node_value(tree->left, tree->value));
		}
		if(tree->right != NULL) {
		max = max_int(max,highest_node_value(tree->right, tree->value));
		}
	}
	return max;
}

int highest_node_value_rec(Tree* tree, int max) {
	return highest_node_value(tree->root,max);
}

int lowest_node_value(Node* tree, int min) {
	if(tree->value < min) {
		min = tree->value;
	}
	if(tree == NULL) {
		return 0;
	}
	else {
		if(tree->left != NULL) {
			min = min_int(min,lowest_node_value(tree->left,min));
		}
		if(tree->right != NULL) {
			min = min_int(min,lowest_node_value(tree->right, min));
		}
	}
	return min;
}

int lowest_node_value_rec(Tree* tree, int min) {
	return lowest_node_value(tree->root, min);
}
int max_depth(Node* tree, int left_depth, int right_depth){

	if(tree == NULL) {
		return 0;
	}
	else {
		if(tree->left != NULL) {
			left_depth++;
			left_depth =  max_depth(tree->left, left_depth, right_depth);
		}
		if(tree->right != NULL) {
			right_depth++;
			right_depth =  max_depth(tree->right, left_depth, right_depth);
		}
	}
	return max_int(left_depth, right_depth);
}

int max_depth_rec(Tree* tree, int left_depth, int right_depth) {
	return max_depth(tree->root, left_depth, right_depth) + 1;
}

int sum_of_values(Node* tree, int sum) {
	if(tree == NULL) {
		return 0;
	}
	else {
		if(tree->left != NULL) {
			sum = tree->left->value + sum_of_values(tree->left, sum);
		}
		if(tree->right != NULL) {
			sum = tree->right->value + sum_of_values(tree->right, sum);
		}
	}
	return sum;
}

int sum_of_values_rec(Tree* tree, int sum) {
	return sum_of_values(tree->root, sum += tree->root->value);
}

int mean_values_rec(Tree* tree, int mean) {
	return mean = sum_of_values_rec(tree, mean)/number_of_nodes_rec(tree);
}

/** Returns true if this is a search tree. Returns false otherwise.
  * May need a helper method. */
bool is_search_tree_rec(Node* tree) {
	if(tree == NULL){
		return true;
	}
	if(tree->left != NULL){
		if(highest_node_value(tree->left, tree->left->value) > tree->value) {
				return false;
		}
			if(!is_search_tree_rec(tree->left)) return false;
	}
	if(tree->right != NULL) {
		if(lowest_node_value(tree->right,tree->right->value) < tree->value){
				return false;
		}
		if(!is_search_tree_rec(tree->right)) return false;
	}
	return true;
}

bool is_search_tree(Tree* tree){
return is_search_tree_rec(tree->root);
}

//Runs through the tree
void tree_run(Node* tree){
	if(tree == NULL) {
		return;
	}
	else {
		if(tree->left != NULL) {
			tree_run(tree->left);
		}
		if(tree->right != NULL) {
			tree_run(tree->right);
		}
	}
}

void tree_run_rec(Tree* tree) {
	return tree_run(tree->root);
}

int number_of_parents(Node* node){
	int count = 0;
	if(node == NULL) {
		return 0;
	}
	count = number_of_parents(node->left) + number_of_parents(node->right);
	if(node->left != NULL) {
		count++;
	}
	if(node->right != NULL) {
		count++;
	}
	return count;
}

int number_of_parents_rec(Tree* tree) {
	return number_of_parents(tree->root) + 1;
}
// todo: implement number_of_nodes but with tree_run_rec to go trough the tree.

void test() {
	Tree* t = new_tree(NULL);
	test_equal_b(is_search_tree(t), true);
	free_tree(t);

	t = new_tree(new_node(NULL, 100, NULL));
	test_equal_b(is_search_tree(t), true);
	free_tree(t);

	t = new_tree(new_node(new_node(NULL, 99, NULL), 100, new_node(NULL, 101, NULL)));
	test_equal_b(is_search_tree(t), true);
	free_tree(t);

	t = new_tree(new_node(new_node(NULL, 101, NULL), 100, new_node(NULL, 99, NULL)));
	test_equal_b(is_search_tree(t), false);
	free_tree(t);

	t = new_tree(new_node(new_node(NULL, 101, NULL), 100, new_node(NULL, 199, NULL)));
	test_equal_b(is_search_tree(t), false);
	free_tree(t);

	t = new_tree(new_node(new_node(new_node(NULL, 6, NULL), 7, new_node(NULL, 9, NULL)), 8, NULL));
	test_equal_b(is_search_tree(t), false);
	free_tree(t);

	t = new_tree(new_node(new_node(NULL, 11, NULL), 100, new_node(NULL, 99, NULL)));
	test_equal_b(is_search_tree(t), false);
	free_tree(t);

	t = new_tree(new_node(new_node(new_node(NULL, 25, NULL), 50, new_node(NULL,75, NULL)), 100, new_node(new_node(NULL,125, NULL), 150, new_node(NULL, 175, NULL))));
	test_equal_b(is_search_tree(t), true);
	free_tree(t);

	t = new_tree(new_node(new_node(new_node(NULL, 55, NULL), 50, new_node(NULL, 75, NULL)), 100, new_node(new_node(NULL, 125, NULL), 150, new_node(NULL, 175, NULL))));
	test_equal_b(is_search_tree(t), false);
	free_tree(t);

	t = new_tree(new_node(NULL, 101, new_node(NULL, 100, NULL)));
	test_equal_b(is_search_tree(t), false);
	free_tree(t);

	t = new_tree(new_node(new_node(NULL, 50, NULL), 100, NULL));
	test_equal_b(is_search_tree(t), true);
	free_tree(t);

	t = new_tree(new_node(new_node(NULL,20,NULL),100,new_node(NULL,45,NULL)));
	test_equal_i(number_of_nodes_rec(t), 3);
	free_tree(t);

	t = new_tree(new_node(new_node(NULL,110,NULL),100,new_node(NULL,45,NULL)));
	test_equal_i(highest_node_value_rec(t,0), 110);
	free_tree(t);

	t = new_tree(new_node(new_node(NULL,20,NULL),100,new_node(NULL,45,new_node(NULL, 30, NULL))));
	test_equal_i(max_depth_rec(t,0,0), 3);
	free_tree(t);

	t = new_tree(new_node(NULL,100,new_node(new_node(NULL,10, NULL),60,new_node(NULL, 1, NULL))));
	test_equal_i(max_depth_rec(t,0,0),3);
	free_tree(t);

	t = new_tree(new_node(new_node(NULL,20,NULL),100,new_node(NULL,45,new_node(NULL, 30, NULL))));
	test_equal_i(sum_of_values_rec(t,0), 195);
	free_tree(t);

	t = new_tree(new_node(new_node(NULL,20,NULL),100,new_node(NULL,45,new_node(NULL, 30, NULL))));
	test_equal_i(mean_values_rec(t,0),48);
	free_tree(t);

	t = new_tree(new_node(new_node(NULL,50,NULL),70,new_node(NULL,45,new_node(NULL, 30, NULL))));
	test_equal_i(lowest_node_value_rec(t,100),30);
	free_tree(t);

	t = new_tree(new_node(new_node(NULL,50,NULL),70,new_node(NULL,45,new_node(NULL, 30, NULL))));
	test_equal_i(number_of_parents_rec(t),2);
	free_tree(t);

	t = new_tree(new_node(NULL, 100, NULL));
	test_equal_i(number_of_parents_rec(t), 0);
	free_tree(t);

	t = new_tree(new_node(new_node(NULL, 50, NULL), 100, NULL));
	test_equal_i(number_of_parents_rec(t), 1);
	free_tree(t);
}


int main(void) {
	base_init();
	base_set_memory_check(true);
	test();
	return 0;
}
