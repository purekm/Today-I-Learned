#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
#include <iostream>
#include <queue>
#include <vector>
#include <unordered_set>

using namespace std;

int xblank,yblank;
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

extern bool swap(int dir);
struct State{
    int x,y;
    vector<int> path;
    int g,h;
    bool operator>(const State& other) const {
        return cost + estimate > other.cost + other.estimate;
    }
}
void solve(int board[5][5], int pattern[3][3], int callCntLimit) {
    
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if(board[i][j]==0){
                xblank = i;
                yblank = j;
            }
        }
    }
    priority_queue<State, vector<State>, greater<State>> pq;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i+1][j+1]==pattern[i][j]) continue;
            int manhattan_distance = abs(xblank-(i+1))+ abs(yblank-(j+1));
            pq.push({xblank,yblank,{},0,manhattan_distance});
            while(!pq.empty() && callCntLimit > 0){
                State cur = pq.top();
                pq.pop();
                if(cur.x == i && cur.y == j){
                    for(auto dir : cur.path){
                        swap(dir);
                        callCntLimit--;
                    }
                    break;
                }
                for(int k=0;k<4;k++){
                    int nx = cur.x + dx[k];
                    int ny = cur.y + dy[k];
                    int new_distance = abs(nx-(i+1))+ abs(ny-(j+1));
                    if (ny < 0 || ny >= 5 || nx < 0 || nx >= 5) continue;
                    vector<int> newpath = cur.path;
                    newpath.push_back(k);
                    pq.push({nx,ny,newpath,cur.g+1,new_distance});
                }
            } 
        }
    }
}