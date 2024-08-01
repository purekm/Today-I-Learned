#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <queue>

using namespace std;
bool visit[51];
int candidate[51];
vector<unordered_set<int>> vec(51);

int n,m,person;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> person;
    vector<int> vec(person);
    for(int i=0;i<person;i++) cin >> vec[i];

    for(int i=0;i<m;i++){
        int participant = 0;
        cin >> participant;
        vector<int> party(participant);
        for(int j=1;j<participant;j++) cin >> party[j];
        for(auto e : vec) cout << e << " ";
        cout << '\n';
    }

    return 0;
}