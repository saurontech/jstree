#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "jsmn.h"
#include "jstree.h"
#include "jstree_read.h"

int main()
{
	_tree_node * root;
	_tree_node * tmp;
	_tree_node ** ptr;
	char key[128];
	char val[128];
	char * tx_buf;
	int i;
	int fd;
	int datalen;
	int ret;
	int tid;
	tid = 0;

	fd = open("./output1.json", O_CREAT|O_TRUNC|O_RDWR, S_IRWXU);
	root = alloc_tree_node(JSMN_ARRAY);

	ptr = &root->r;

	for(i = 0; i < 8; i++){
		ptr = end_node(ptr);
		printf("[%d] ptr = %p\n", i, ptr);
		*ptr = alloc_tree_node(JSMN_OBJECT);
	}

	for(i = 0; i < 8; i++ ){
		int j;
		tmp =  next_node(root->r, i);

		if(i == 0){
			continue;
		}

		if(i == 4){
			ptr = end_node(&tmp->r);
			snprintf(key, sizeof(key), "obj%d", tid++);
			*ptr = alloc_tree_node(JSMN_STRING, key);
			(*ptr)->r = alloc_tree_node(JSMN_OBJECT);

			continue;
		}

		if(i == 3){

			for(j = 0; j < i; j++){
				ptr = end_node(&tmp->r);
				snprintf(key, sizeof(key), "err%d", tid++);
				*ptr = alloc_tree_node(JSMN_STRING, key);
			}
			continue;
		}

		if(i == 5){
			ptr = end_node(&tmp->r);
			snprintf(key, sizeof(key), "array%d", tid++);
			*ptr = alloc_tree_node(JSMN_STRING, key);
			(*ptr)->r = alloc_tree_node(JSMN_ARRAY);

			ptr = end_node(&tmp->r);
			snprintf(key, sizeof(key), "array%d", tid++);
			*ptr = alloc_tree_node(JSMN_STRING, key);
			(*ptr)->r = alloc_tree_node(JSMN_ARRAY);

			for(j = 0; j < i; j++){
				_tree_node ** tmp_ptr;

				tmp_ptr = end_node(&((*ptr)->r->r));
				snprintf(val, sizeof(val), "%d", tid++);
				*tmp_ptr = alloc_tree_node(JSMN_PRIMITIVE, val);
			}

		}
		

		for(j = 0; j < i; j++){
			snprintf(key, sizeof(key), "key%d", tid++);
			snprintf(val, sizeof(val), "val%d", tid++);
			ptr = end_node(&tmp->r);
			*ptr = alloc_tree_node(JSMN_STRING, key);
			(*ptr)->r = alloc_tree_node(JSMN_STRING, val);
			ptr = end_node(&tmp->r);
		}
	}

	
	ret = jstree_read(root->r, &tmp, "[5]", "array11", "[3]");
	printf("ret = %d for [5]->array11->[3]\n", ret );
	ret = jstree_read(root->r, &tmp, "[5]", "[1]", "[3]");
	printf("ret = %d for [5]->[1]->[3]\n", ret );


	

	datalen = tree2json(root, 0, 0);

	tx_buf = malloc(datalen);
	tree2json(root, tx_buf, datalen);

	write(fd, tx_buf, datalen);
	close(fd);
	return 0;
}
