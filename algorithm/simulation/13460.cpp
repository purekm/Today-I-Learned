#include <iostream>
#include <queue>
#include <tuple>

using namespace std;

queue<tuple<int, int, int>> redball;
queue<pair<int, int>> blueball;

char arr[11][11];
int dr[4] = {1, 0, -1, 0};
int dc[4] = {0, 1, 0, -1};
bool visit[11][11][11][11] = {};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m, result;
    result = -1;
    cin >> n >> m;
    int rr, rc, br, bc;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
            if (arr[i][j] == 'B') {
                blueball.push({i, j});
                br = i;
                bc = j;
            }
            if (arr[i][j] == 'R') {
                redball.push({i, j, 0});
                rr = i;
                rc = j;
            }
        }
    }
    visit[rr][rc][br][bc] = true;

    while (!redball.empty()) {
        auto rcur = redball.front();
        auto bcur = blueball.front();
        redball.pop();
        blueball.pop();
        int x, y, z;
        tie(x, y, z) = rcur;
        if (z >= 10) break;
        for (int k = 0; k < 4; k++) {
            int rcnt = 0;
            int bcnt = 0;
            int rnr = x + dr[k];
            int rnc = y + dc[k];
            int bnr = bcur.first + dr[k];
            int bnc = bcur.second + dc[k];
            int nd = z + 1;

           
            while (rnr >= 0 && rnr < n && rnc >= 0 && rnc < m && arr[rnr][rnc] != '#' && arr[rnr][rnc] != 'O') {
                rnr += dr[k];
                rnc += dc[k];
                rcnt++;
            }
            if (arr[rnr][rnc] == '#') {
                rnr -= dr[k];
                rnc -= dc[k];
            }

            
            while (bnr >= 0 && bnr < n && bnc >= 0 && bnc < m && arr[bnr][bnc] != '#' && arr[bnr][bnc] != 'O') {
                bnr += dr[k];
                bnc += dc[k];
                bcnt++;
            }
            if (arr[bnr][bnc] == '#') {
                bnr -= dr[k];
                bnc -= dc[k];
            }

            if (arr[bnr][bnc] == 'O') continue;
            if (arr[rnr][rnc] == 'O') {
                result = nd;
                break;
            }

            if (rnr == bnr && rnc == bnc) {
                if (rcnt > bcnt) {
                    rnr -= dr[k];
                    rnc -= dc[k];
                } else {
                    bnr -= dr[k];
                    bnc -= dc[k];
                }
            }

            if (visit[rnr][rnc][bnr][bnc]) continue;

            visit[rnr][rnc][bnr][bnc] = true;
            redball.push({rnr, rnc, nd});
            blueball.push({bnr, bnc});
        }
        if (result != -1) break;
    }

    cout << result;
    return 0;
}
