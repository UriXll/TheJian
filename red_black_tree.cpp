/*************************************************************************
	> File Name: red_black_tree.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 四  7/16 11:40:14 2020
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
using namespace std;

#define K(n) (n->key)
#define C(n) (n->color)
#define L(n) (n->lchild)
#define R(n) (n->rchild)

typedef struct Node {
    int key;
    int color; // 0 red, 1 black, 2 double black
    struct Node *lchild, *rchild;
} Node;


Node __NIL;
#define NIL (&__NIL)
__attribute__((constructor))
void init_NIL() {
    NIL->key = 0;
    NIL->color = 1;
    NIL->lchild = NIL->rchild = NIL;
    return ;
}

Node *getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->color = 0;
    p->lchild = p->rchild = NIL;
    return p;
}


int hasRed(Node *root) {
    return C(L(root)) == 0 || C(R(root)) == 0;
}

Node *left_rotate(Node *root) {
    Node *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    return temp;
}
Node *right_rotate(Node *root) {
    Node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    return temp;
}

Node *insert_maintain(Node *root) {
    if (!hasRed(root)) return root;
    int flag = 0;
    if (C(L(root)) == 0 && hasRed(L(root))) flag = 1;
    else if (C(R(root)) == 0 && hasRed(R(root))) flag = 2;
    if (flag == 0) return root;
   
    if (flag == 1 && C(R(root)) == 1) {
        if (C(R(L(root))) == 0) {
            root->lchild = left_rotate(root->lchild);
        }
        root = right_rotate(root);
    } else if (flag == 2 && C(L(root)) == 1) {
        if (C(L(R(root))) == 0) {
            root->rchild = right_rotate(root->rchild);
        }
        root = left_rotate(root);
    } 
    root->color = 0;
    C(L(root)) = C(R(root)) = 1;
    return root;
}

Node *predecessor(Node *root) {
    Node *temp = root->lchild;
    while (temp->rchild != NIL) temp = temp->rchild;
    return temp;
}

Node *erase_maintain(Node *root) {
    if (C(L(root)) != 2 && C(R(root)) != 2) return root;
    if (hasRed(root)) {
        int flag = 0;
        root->color = 0;
        if (C(L(root)) == 0) root = right_rotate(root), flag = 1;
        else if (C(R(root)) == 0) root = left_rotate(root), flag = 2;
        root->color = 1;
        if (flag == 1) root->rchild = erase_maintain(root->rchild);
        else root->lchild = erase_maintain(root->lchild);
        return root;
    }
    if (C(L(root)) == 1) {
        C(R(root)) = 1;
        if (!hasRed(L(root))) {
            C(root) += 1;
            C(L(root)) -= 1;
            return root;
        }
        if (C(L(L(root))) != 0) {
            C(L(root)) = 0;
            root->lchild = left_rotate(root->lchild);
            C(L(root)) = 1;
        }
        C(L(root)) = C(root);
        root = right_rotate(root);
        C(L(root)) = C(R(root)) = 1;
    } else {
        C(L(root)) = 1;
        if (!hasRed(R(root))) {
            C(root) += 1;
            C(R(root)) -= 1;
            return root;
        }
        if (C(R(R(root))) != 0) {
            C(R(root)) = 0;
            root->rchild = right_rotate(root->rchild);
            C(R(root)) = 1;
        }
        C(R(root)) = C(root);
        root = left_rotate(root);
        C(L(root)) = C(R(root)) = 1;
    }
    return root;
}

Node *__erase(Node *root, int key) {
    if (root == NIL) return root;
    if (key < root->key) {
        root->lchild = __erase(root->lchild, key);
    } else if (key > root->key) {
        root->rchild = __erase(root->rchild, key);
    } else {
        if (root->lchild == NIL || root->rchild == NIL) {
            Node *temp = root->lchild == NIL ? root->rchild : root->lchild;
            temp->color += root->color;
            free(root);
            return temp;
        } else {
            Node *temp = predecessor(root);
            root->key = temp->key;
            root->lchild = __erase(root->lchild, temp->key);
        }
    }
    return erase_maintain(root);
}

Node *erase(Node *root, int key) {
    root = __erase(root, key);
    root->color = 1;
    return root;
}


Node *__insert(Node *root, int key) {
    if (root == NIL) return getNewNode(key);
    if (root->key == key) return root;
    if (key < root->key) root->lchild = __insert(root->lchild, key);
    else root->rchild = __insert(root->rchild, key);
    return insert_maintain(root);
}

Node *insert(Node *root, int key) {
    root = __insert(root, key);
    root->color = 1;
    return root;
}

void clear(Node *root) {
    if (root == NIL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

void output(Node *root) {
    if (root == NIL) return ;
    printf("(%d(%d) | %d, %d)\n", K(root), C(root), K(L(root)), K(R(root)));
    output(L(root));
    output(R(root));
    return ;
}

void in_order(Node *root) {
    if (root == NIL) return ;
    in_order(root->lchild);
    printf("%d ", K(root));
    in_order(root->rchild);
    return ;
}

int main() {
    int op, val;
    Node *root = NIL;
    while (~scanf("%d%d", &op, &val)) {
        switch (op) {
            case 1: root = insert(root, val); break;
            case 2: root = erase(root, val); break;
        }
        printf("\n======= red black tree =======\n");
        output(root);
        in_order(root), printf("\n");
        printf("======= red black tree end =======\n");
    }
    return 0;
}
