#include <stdio.h>
#include "Point.h"

void SetPointPos(Point *ppos, int xpos,int ypos){ //Point 변수의 xpos, ypos 값 설정
    ppos->xpos = xpos;
    ppos->ypos = ypos;
}
void ShowPointPos(Point *ppos){ // Point 변수의 xpos,ypos 정보 출력
    printf("[%d, %d]\n",ppos->xpos , ppos->ypos);
}
int PointComp(Point *pos1, Point* pos2){ // 두 변수의 비교
    if(pos1->xpos == pos2->xpos && pos1->ypos == pos2->ypos) return 0;
    else if(pos1->xpos == pos2->xpos) return 1;
    else if(pos1->ypos == pos2->ypos) return 2;
    else return -1;
}