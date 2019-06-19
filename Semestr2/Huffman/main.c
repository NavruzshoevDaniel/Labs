#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman_tree.h"
#include "bit_manipulation.h"

#define AL_POW 256
#define STOP_S (unsigned char)(-1)
#define BUFF_SIZE 10000
#define PRINT_MODE "%c"

int main(int argc, char* argv[]) {

	
	unsigned char c;
	long long table[AL_POW] = { 0 };
	long long sym_num = 0;
	struct lNode* root = NULL;
	struct hNode* hTable = NULL;

	char* in = "in.txt";
	char* out = "out.txt";

	unsigned char* mode = (unsigned char*)malloc(sizeof(unsigned char) * 3);
	unsigned char* buf = (unsigned char*)malloc(sizeof(unsigned char) * BUFF_SIZE);

	FILE* fin;
	FILE* fout;

	for (int i = 0; i < BUFF_SIZE; i++) buf[i] = 0;

	if (argc > 1) {
		char* in = argv[2];
		char* out = argv[3];

		fin = fopen(in, "rb");
		fout = fopen(out, "wb");

		if (!fin) {
			printf("Can't open %s.", in);
			exit(0);
		}
		if (!out) {
			printf("Can't open %s.", out);
			exit(0);
		}

		mode[0] = argv[1][0];
	}
	else {
		fin = fopen(in, "rb");
		fout = fopen(out, "wb");

		if (!fin) {
			printf("Can't open %s.", in);
			exit(0);
		}
		if (!fout) {
			printf("Can't open %s.", out);
			exit(0);
		}

		fread(mode, sizeof(unsigned char), 3, fin);
	}

	
	if (mode[0] == 'c') {

		
		unsigned char buffer = 0;

		int text_size = 0;
		int buf_i = 0;
		int cur_bit = 0;

		
		text_size = fread(buf, sizeof(unsigned char), BUFF_SIZE, fin);

		
		if (text_size == 0) exit(0);

		
		do {
			for (int i = 0; i < text_size; i++) {
				c = buf[i];
				if (++table[c] == 1) sym_num++;
			}
		} while (text_size = fread(buf, sizeof(unsigned char), BUFF_SIZE, fin));

		
		for (int i = 0; i < 256; i++) {
			if (table[i] > 0) {
				root = add_node(root, create_lNode(create_tNode((unsigned char)i, table[i], 1)));
			}
		}

		
		struct tNode* tRoot = build_tree(root);

		
		hTable = set_codes(tRoot, tRoot->code, hTable);

		
		struct hNode* cur_tab = hTable;

		

		struct packed_tree* packed_tree = (unsigned char*)malloc(sizeof(struct packed_tree) * (sym_num * 2));
		int n = pack_tree(tRoot, packed_tree, 0);

		for (int i = 0; i < n; i++) {
			if (cur_bit > 7) {
				fprintf(fout, PRINT_MODE, buffer);
				buffer = 0;
				cur_bit = 0;
			}
			if (packed_tree[i].det) {
				buffer = set_bit(buffer, cur_bit++, 1);
				if (cur_bit > 7) {
					fprintf(fout, PRINT_MODE, buffer);
					buffer = 0;
					cur_bit = 0;
				}
				for (int j = 0; j < 8; j++) {
					buffer = set_bit(buffer, cur_bit++, get_bit(packed_tree[i].symbol, j));
					if (cur_bit > 7) {
						fprintf(fout, PRINT_MODE, buffer);
						buffer = 0;
						cur_bit = 0;
					}
				}
			}
			else {
				buffer = set_bit(buffer, cur_bit++, 0);
				if (cur_bit > 7) {
					fprintf(fout, PRINT_MODE, buffer);
					buffer = 0;
					cur_bit = 0;
				}
			}
		}
		fprintf(fout, "%c%d\n", buffer, cur_bit);

		
		fseek(fin, 0, SEEK_SET);
		if (argc == 1) {
			fread(mode, sizeof(unsigned char), 3, fin);
		}
		text_size = fread(buf, sizeof(unsigned char), BUFF_SIZE, fin);

	
		cur_bit = 0;
		buffer = 0;

		
		do {
			buf_i = 0;
			while (buf_i < text_size) {
				c = buf[buf_i++];
				if (cur_tab->symbol != c) {
					while ((cur_tab->next) && (cur_tab->symbol != c)) cur_tab = cur_tab->next;
				}

				int j = 0;
				while ((cur_tab->code[j] != -1)/* && (j < 8)*/) {
					if (cur_bit > 7) {
						cur_bit = 0;
						fprintf(fout, PRINT_MODE, buffer);
						buffer = 0;
					}
					buffer = set_bit(buffer, cur_bit++, cur_tab->code[j]);
					j++;
				}

				cur_tab = hTable;
			}
		} while (text_size = fread(buf, sizeof(unsigned char), BUFF_SIZE, fin));
		fprintf(fout, "%c%d", buffer, cur_bit);

	}
	else if (mode[0] == 'd') {

		
		int k = 0, bit_num = 0, buf_i = 0;

		
		fseek(fin, 0, SEEK_SET);
		if (argc == 1) {
			fread(mode, sizeof(unsigned char), 3, fin);
		}
		int text_size = fread(buf, sizeof(unsigned char), BUFF_SIZE, fin);

		
		if (!text_size) exit(0);

		
		unsigned char c1 = buf[buf_i++];
		if (feof(stdin)) {
			return 0;
		}
		unsigned char c2 = buf[buf_i++];
		unsigned char buffer = 0;

		struct lNode* stack = NULL;
		struct tNode* root = create_tNode(NULL, 0, 0);

		
		while ((c2 != (unsigned char)('\n')) || ((c1 > '9') || (c1 < '0'))) {
			c1 = c2;
			c2 = buf[buf_i++];
			k++;
		}

		
		int buf_j = buf_i;

		bit_num = (k - 1) * 8 + (int)(c1 - (unsigned char)('0'));

		buf_i = 0;

		for (int j = 0; j < bit_num; j++) {

			if (j % 8 == 0) {
				c1 = buf[buf_i++];
			}
			if (get_bit(c1, j % 8)) {
				j++;
				for (int i = 0; (i < 8) && (j < bit_num); i++, j++) {
					if (j % 8 == 0) {
						c1 = buf[buf_i++];
					}
					buffer = set_bit(buffer, i, get_bit(c1, j % 8));
				}
				j--;
				stack = add_stack_node(stack, create_lNode(create_tNode(buffer, 0, 1)));
			}
			else {
				if (stack->data) {
					root->left = stack->data;
					stack = delete_stack_node(stack);
				}
				if (stack->data) {
					root->right = stack->data;
					stack = delete_stack_node(stack);
				}

				stack = add_stack_node(stack, create_lNode(root));

				root = create_tNode(NULL, 0, 0);
			}
		}

		k = 0;

		buf_i = buf_j;

		c1 = buf[buf_i++];
		k++;

		while (buf_i < text_size) {
			c1 = buf[buf_i++];
			k++;
			if (buf_i == BUFF_SIZE) {
				if (text_size = fread(buf, sizeof(unsigned char), BUFF_SIZE, fin)) {
					buf_i = 0;
				}
			}
		}

		struct tNode* cur_pos = stack->data;

		bit_num = (k - 2) * 8 + (c1 - '0');

		buf_i = buf_j;

		fseek(fin, 0, SEEK_SET);
		if (argc == 1) {
			fread(mode, sizeof(unsigned char), 3, fin);
		}
		text_size = fread(buf, sizeof(unsigned char), BUFF_SIZE, fin);

		for (int j = 0; j < bit_num; j++) {
			if (j % 8 == 0) {
				c1 = buf[buf_i++];
				if (buf_i == text_size) {
					if (text_size = fread(buf, sizeof(unsigned char), BUFF_SIZE, fin)) {
						buf_i = 0;
					}
					else break;
				}
			}

			if (get_bit(c1, j % 8)) {
				if (!cur_pos->det) cur_pos = cur_pos->right;
				if (cur_pos->det) {
					fprintf(fout, "%c", cur_pos->symbol);
					cur_pos = stack->data;
				}
			}
			else {
				if (!cur_pos->det) cur_pos = cur_pos->left;
				if (cur_pos->det) {
					fprintf(fout, "%c", cur_pos->symbol);
					cur_pos = stack->data;
				}
			}
		}
	}
	free(buf);
	free(mode);
	fclose(fin);
	fclose(fout);
	return 0;
}
