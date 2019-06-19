
struct tNode {
	unsigned char symbol;
	long long weight;

	int det;

	char code[255];

	struct tNode* right;
	struct tNode* left;
};


struct lNode {
	struct tNode* data;
	struct lNode* next;
};


struct hNode {
	unsigned char symbol;
	int det;
	char code[255];
	struct hNode* next;
};

struct packed_tree {
	unsigned char symbol;
	int det;
};

struct tNode* create_tNode(unsigned char symbol, long long weight, int det) {
	struct tNode* node = (struct tNode*)malloc(sizeof(struct tNode));

	for (int i = 0; i < 255; i++) {
		node->code[i] = -1;
	}

	node->left = node->right = NULL;
	node->det = det;
	node->symbol = symbol;
	node->weight = weight;

	return node;
}


struct lNode* create_lNode(struct tNode* tNode) {
	struct lNode* node = (struct lNode*)malloc(sizeof(struct lNode));
	node->next = NULL;
	node->data = tNode;

	return node;
}


struct hNode* create_hNode(unsigned char symbol, char* code, int det) {
	struct hNode* node = (struct hNode*)malloc(sizeof(struct hNode));
	node->det = det;
	node->next = NULL;
	node->symbol = symbol;
	for (int i = 0; i < 255; i++) {
		node->code[i] = code[i];
	}
	return node;
}


struct lNode* add_node (struct lNode* root, struct lNode* node) {
	if (!root) return node;
	if (root->data->weight >= node->data->weight) {
		node->next = root;
		return node;
	} else {
		root->next = add_node(root->next, node);
		return root;
	}
}


struct lNode* add_stack_node(struct lNode* root, struct lNode* node) {
	if (!root) return node;
	node->next = root;
	return node;
}


struct lNode* delete_stack_node(struct lNode* root) {
	if (!root) return root;
	struct lNode* node = root->next;
	free(root);
	return node;
}


struct hNode* add_symbol_in_table(struct hNode* root, unsigned char symbol, char* _code) {
	char code[255];
	for (int i = 0; i < 255; i++) {
		code[i] = _code[i];
	}
	if (!root) return create_hNode(symbol, code, 1);
	root->next = add_symbol_in_table(root->next, symbol, code);
	return(root);
}


struct lNode* delete_node(struct lNode* root) {
	if (!root) return NULL;
	struct lNode* new_root = root->next;
	free(root);
	return new_root;
}


struct tNode* build_tree(struct lNode* root) {
	while (root->next != NULL) {
		struct tNode* new_tNode = create_tNode((unsigned char)NULL, root->data->weight + root->next->data->weight, 0);
		new_tNode->left = root->data;
		new_tNode->right = root->next->data;
		root = delete_node(root);
		root = delete_node(root);
		root = add_node(root, create_lNode(new_tNode));
	}
	return root->data;
}

struct hNode* set_codes(struct tNode* root, char _str[], struct hNode* table) {

	char str[255] = { 0 };
	for (int i = 0; i < 255; i++) {
		str[i] = _str[i];
	}

	int j = 0;

	if (!root) return table;

	
	for (int i = 0; i < 255; i++) {
		root->code[i] = str[i];
		
	}

	if (root->det) {
		
		if (root->code[0] == -1) root->code[0] = 1;
		table = add_symbol_in_table(table, root->symbol, root->code);
		return table;
	}

	while (((str[j] == 1) || (str[j] == 0)) && (j < 255)) j++;

	
	str[j] = 0;
	table = set_codes(root->left, str, table);

	str[j] = 1;
	table = set_codes(root->right, str, table);

	return table;
}

int pack_tree(struct tNode* root, struct packed_tree* packed_tree, int cur_cell) {
	if (root->det) {
		packed_tree[cur_cell].symbol = root->symbol;
		packed_tree[cur_cell].det = 1;
		return cur_cell + 1;
	}
	cur_cell = pack_tree(root->right, packed_tree, cur_cell);
	cur_cell = pack_tree(root->left, packed_tree, cur_cell);
	packed_tree[cur_cell++].det = 0;
	return cur_cell;
}
