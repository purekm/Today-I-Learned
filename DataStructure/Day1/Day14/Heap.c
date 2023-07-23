#include "Heap.h"

void HeapInit(Heap *ph,PriorityComp pc){
    ph->numOfData = 0;
    ph->comp = pc;
}

int HIsEmpty(Heap *ph){
    if(ph->numOfData ==0){
        return TRUE;
    }else{
        return FALSE;
    }
}

int GetParentIDX(int idx){
    return idx/2;
}

int GetLChildIDX(int idx){
    return idx*2;
}

int GetRChildIDX(int idx){
    return GetLChildIDX(idx)+1;
}

int GetHiPriChildIDX(Heap *ph, int idx){ //우선순위가 높은 자식 노드 인덱스 반환
    if(GetLChildIDX(idx) > ph-> numOfData){
        return GetLChildIDX(idx);
    }else if(GetLChildIDX(idx== ph->numOfData)){
        return GetLChildIDX(idx);
    }else{
        if(ph->comp(ph->heapArr[GetLChildIDX(idx)], ph->heapArr[GetRChildIDX(idx)])<0){
            return GetRChildIDX(idx);
        }else{
            return GetLChildIDX(idx);
        }
    }
}

void HInsert(Heap *ph,HData data){
    int idx= ph->numOfData;
    while (idx !=1){
        if(ph->comp(data,ph->heapArr[GetParentIDX(idx)])>0){
            ph->heapArr[idx]=ph->heapArr[GetParentIDX(idx)];
            idx = GetParentIDX(idx);
        }else{
            break;
        }
    }
    ph->heapArr[idx]=data;
    ph->numOfData +=1;
}

HData HDelete(Heap *ph){
    HData retData = ph->heapArr[1];
    HData lastElem = ph->heapArr[ph->numOfData];

    int parentIdx = 1;
    int childIdx;
    while(childIdx=GetHiPriChildIDX(ph,parentIdx)){ //루트 노드의 우선순위가 높은 자식노드를 시작으로 반복문 시작
        if(ph->comp(lastElem,ph->heapArr[childIdx])>=0){ //마지막 노드와 우선순위 비교
            break;
        }
        ph->heapArr[parentIdx]=ph->heapArr[childIdx]; //마지막 노드보다 우선순위 높으므로, 비교대상의 노드위치 한 레벨 올림
        parentIdx = childIdx; //마지막 노드가 저장될 위치 정보를 갱신
    }

    ph->heapArr[parentIdx] = lastElem; // 마지막 노드가 있어야할 위치를 parentIdx에 저장
    ph->numOfData -=1;
    return retData;
}