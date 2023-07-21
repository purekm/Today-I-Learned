#include <stdio.h>
#include <stdlib.h>
#include "BinaryTree.h"
BTreeNode *MakeBTreeNode(void){ //노드 초기화
    BTreeNode *node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node -> left = NULL;
    node -> right = NULL;
    return node;
}

BTData GetData(BTreeNode *bt){ //노드 데이터 가져오기
    return bt->data; 
}

void SetData(BTreeNode *bt, BTData data){ //데이터 넣기
    bt->data = data; 
}
BTreeNode * GetLeftSubTree(BTreeNode *bt){
    return bt -> left;
}
BTreeNode * GetRightSubTree(BTreeNode *bt){
    return bt -> right;
}
// 왼쪽 혹은 오른쪽 서브 트리가 존재하면, 트리 삭제 후 새로운 트리를 연결해준다
void MakeLeftSubTree(BTreeNode *main, BTreeNode *sub){ 
    if(main->left != NULL){
        free(main->left);
    }
    main -> left = sub;
}
void MakeRightSubTree(BTreeNode *main, BTreeNode *sub){
    if(main->right != NULL){
        free(main->right);
    }
    main -> right = sub;
}
/*이상태에서 free(main-> right or left)를 하면 해당 노드가 1개이면 상관없지만
 그렇지 않으면 메모리 누수로 이어진다. 
-> 모든 노드를 방문하면서 없에려면 모든 노드를 순회하며 삭제시켜줘야함
-> 노드를 삭제할때 자기자신을 젤 마지막에 지워야 left와 right를 갈 수 있으므로
후위순회를 통해서 모든 노드를 삭제해준다!*/ 
