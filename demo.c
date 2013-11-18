/*
 * =====================================================================================
 *
 *       Filename:  demo.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013/10/08 14时23分32秒
 *       Revision:  0.1
 *       Compiler:  clang
 *
 *         Author:  bigdog
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "_c_list.h"

static char *magic_strs[] = {
    "JavaScript is a single threaded language",
    "meaning only one thing can be done at a time in the browser.",
    "When the JavaScript interpreter initially executes code", 
    "it first enters into a global execution context by default.",
    "Each invocation of a function from this point on will result in the creation of a new execution context.",
    "This is where confusion often sets in", 
    "the term is actually for all intents and purposes referring to scope and not context as previously discussed.",
    "It is an unfortunate naming convention", 
    "however it is the terminology as defined by the ECMAScript specification", 
    "so were kinda stuck with it."
};

#define DATA_MAX 128
#define NODE_NUM 5

#pragma pack(push)
#pragma pack(1)
typedef struct _node {
    u16 idx;
    u16 dx;
    struct list_head line;
    int  len;
    char data[0]; // data-bucket.
} node;
#pragma pack(pop)

typedef struct _list_mgt_ {
    struct list_head list;
    int num;
}lmgt;

int node_entry(node *dnode, u16 index ) {
    if (NULL == dnode ) {
        return -1;
    }

    int idx = rand() % 10;
    node *n = dnode;
    n->idx = index;
    n->dx = idx;
    n->len = strlen(magic_strs[idx]);
    memcpy((char *)(n + 1), magic_strs[idx], n->len);
    return n->len;
}

void print(struct list_head *lst) {
    if (NULL == lst) {
        return ;
    }
    struct list_head *p;
    printf ( "------------node------------------\n" );
    list_for_each(p, lst) {
        node *n =  list_entry(p, node, line);
        printf ( "init-idx = %d\ndata-index = %d\tdata-len = %d\tdata = %s\n\n",n->idx, n->dx, n->len, n->data );
    }
}

int main ( int argc, char *argv[] ) 
{
    srand(time(NULL));

    lmgt *lm = malloc(sizeof(lmgt));
    //struct list_head list;
    INIT_LIST_HEAD(&lm->list);

    node *n = NULL;
    char *tmp;

    int total_size = (sizeof(node) + DATA_MAX + 1) * NODE_NUM;
    char *buff = malloc(total_size);
    if (NULL == buff) return -1;

    memset(buff, '\0', total_size);
    tmp = buff;

    for (int i=0, j=0; i<NODE_NUM; j=0,++i) {
        n = (node *)tmp;
        if ( (j = node_entry(n, i)) == -1 ) {
            printf("node entry error : idx [%d]\n", i);
            break;
        }

        tmp[sizeof(node) + j] = '\0';
        tmp += sizeof(node) + j + 1;

        list_add_tail(&n->line, &lm->list);

        if (i == 3) {
            node *c = list_entry(n->line.prev, node, line);
            printf("dd : %d -- %s\n", c->idx, c->data);
        }
    }

    // functional usage
    print(&lm->list);

    free(buff); 
    buff = NULL;
    free(lm);
    lm=NULL;

    return EXIT_SUCCESS;
}

