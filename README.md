# jstree
a super lightweight json library

# Quality
[![CodeFactor](https://www.codefactor.io/repository/github/saurontech/jstree/badge)](https://www.codefactor.io/repository/github/saurontech/jstree)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/d1f5fa3ce3f7406ba76cfa581915f210)](https://www.codacy.com/gh/saurontech/jstree/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=saurontech/jstree&amp;utm_campaign=Badge_Grade)

# parse json file
```c
jsmn_parser p;
jsmntok_t *tok;

tokcount = 2;
tok = malloc(sizeof(*tok) * tokcount);

ret = 0;

do{
	ret = jsmn_parse(&p, filedata, filelen, tok, tokcount);
	if(ret == JSMN_ERROR_NOMEM){
		tokcount = tokcount * 2;
		tok = realloc_it(tok, sizeof(*tok) * tokcount);
		if(tok == NULL){
			return -1;
		}
		continue;
	}else if(ret < 0){
		printf("failed ret = %d\n", ret);
	}
	break;
}while(1);

```
# convert jsmntok to jstree
```c
#include "jstree.h"

typedef struct{
  int ret; //number of tokens
  _tree_node * node; // pointer to the root node
}jstreeret;

jstreeret js2tree(const char *js, jsmntok_t *t, size_t count);
```
```c
int jstree_read(_tree_node * root, _tree_node * return, ...); // returns number of tokens matched
```
```c
jstreeret result;

result = js2tree(filedata, tok, p.toknext);

if(jstree_read(result.node->r, &rnode, "serials") == 1){
  ...
}
```
# create a jstree
```c
_tree_node * root;

root = alloc_tree_node(JSMN_ARRAY);
```

# jstree to json

```c
int datalen;
char * tx_buf;

datalen = tree2json(root, 0, 0);

tx_buf = malloc(datalen);
tree2json(root, tx_buf, datalen);

```
