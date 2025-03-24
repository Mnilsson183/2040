// Copyright 2025 Morgan Nilsson
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <sys/types.h>

#include "tree.hpp"


// =========================== SUBTREE FUNCS =================================

/**
 * @brief Free the a subtree
 * @param tree Pointer to the tree object
 */
void free_sub_tree(bin_node_t *node) {
	
	if (node == NULL) {
		return;
	}

	if (node->dash == NULL && node->dot == NULL) {
		
		free(node);
		return;

	}

	if (node->dash != NULL) {

		free_sub_tree(node->dash);

	} else if (node->dot != NULL) {

		free_sub_tree(node->dot);

	}

	return;

}

/**
 * @brief Build a new node
 * @return bin_node_t* Pointer to the new node
 */
bin_node_t *build_node() {

	bin_node_t *bin_node = (bin_node_t*)malloc(sizeof(bin_node_t));

	if (bin_node == NULL) {

		std::cout << "Error mallocing memory\n";
		return NULL;

	}

	bin_node->dash = NULL;
	bin_node->dot = NULL;

	return bin_node;

}

/**
 * @brief Insert a new node into the tree
 * @param tree the tree to insert into
 * @param c The character to insert
 * @param buf The buffer containing the path to the node
 * @note The buffer should be of length 5 with a \0
 */
void insert_node(bin_node_t *node, char c, char *buf) {

	if (*buf == '*') {

		if (node->dot == NULL) {

			node->dot = build_node();

		}

		insert_node(node->dot, c, ++buf);

	} else if (*buf == '-') {

		if (node->dash == NULL) {

			node->dash = build_node();

		}

		insert_node(node->dash, c, ++buf);

	} else if (*buf == '\0') {

		node->value = c;

	}

}

/**
 * @brief Get the value of a node
 * @param node The node to get the value of
 * @param buf The buffer containing the path to the node
 */
char get_value_subtree(bin_node_t *node, char *buf) {

	if (*buf == '*') {

		return get_value_subtree(node->dot, ++buf);

	} else if (*buf == '-') {

		return get_value_subtree(node->dash, ++buf);

	} else if (*buf == '\0') {

		return node->value;

	} else {

		std::cout << "Invalid character in path\n";
		return '\0';

	}

}

// =========================== FULL TREE FUNCS =================================

/**
 * @brief Create a new tree object
 * @return tree_t* Pointer to the new tree object
 */
tree_t *make_tree() {

	tree_t *tree = (tree_t*)malloc(sizeof(tree_t));

	if (tree == NULL) {

		std::cout << "Unable to malloc for tree\n";
		return NULL;

	} else {

		return tree;

	}

}

/**
 * @brief Free the tree object
 * @param tree Pointer to the tree object
 */
void free_tree(tree_t* tree) {
	free_sub_tree(&tree->head);
}

/**
 * @brief Insert a new node into the tree
 * @param tree the tree to insert into
 * @param c The character to insert
 * @param buf The buffer containing the path to the node
 * @note The buffer should be of length 5 with a \0
 */
void insert_value(tree_t *tree, char c, char *buf) {

	insert_node(&tree->head, c, buf);

}

/**
 * @brief Get the value of a node
 * @param node The node to get the value of
 * @param buf The buffer containing the path to the node
 */
char get_value(tree_t *tree, char *buf) {

	return get_value_subtree(&tree->head, buf);

}