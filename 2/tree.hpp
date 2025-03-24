// COpyright 2025 Morgan Nilsson
#ifndef _2_TREE_HPP_

typedef struct bin_node {
	bin_node *dot;
	bin_node *dash;
	char value;
} bin_node_t;


typedef struct tree {
	bin_node_t head;
} tree_t;

/**
 * @brief Create a new tree object
 * @return tree_t* Pointer to the new tree object
 */
tree_t *make_tree();
/**
 * @brief Free the tree object
 * @param tree Pointer to the tree object
 */
void free_tree(tree_t* tree);
/**
 * @brief Insert a new node into the tree
 * @param tree the tree to insert into
 * @param c The character to insert
 * @param buf The buffer containing the path to the node
 * @note The buffer should be of length 5 with a \0
 */
void insert_value(tree_t *tree, char c, char *buf);
/**
 * @brief Get the value of a node
 * @param node The node to get the value of
 * @param buf The buffer containing the path to the node
 */
char get_value(tree_t *tree, char *buf);

#endif