#define MAXL	5
#define MAXF	10
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
using namespace std;

vector<unordered_set<int>> friends_list;
bool compare(const pair<int,int> &a, const pair<int,int> &b){
	if(a.second != b.second) return a.second > b.second;
	return a.first < b.first;
}

void init(int N)
{
	friends_list.clear();
	friends_list.resize(N+1);
}

void add(int id, int F, int ids[MAXF])
{
	int cnt = 0;
	while(cnt != F){
		friends_list[id].insert(ids[cnt]);
		friends_list[ids[cnt]].insert(id);
		cnt++;
	}
}

void del(int id1, int id2)
{
	friends_list[id1].erase(id2);
	friends_list[id2].erase(id1);

}

int recommend(int id, int list[MAXL])
{
	unordered_map<int,int> count;
	for(auto fi : friends_list[id]){
		for(auto fifi : friends_list[fi]){
			if(fifi == id || friends_list[id].count(fifi)) continue; // 친구의 친구가 나 or 이미 내 친구면 추천받지 않는다.
			count[fifi]++;
		}
	}

	vector<pair<int,int>> friends_count(count.begin(),count.end());
	sort(friends_count.begin(),friends_count.end(),compare);
	int cnt = 0;
	for(auto e : friends_count){
		if(cnt >= 5) break;
		list[cnt] = e.first;
		cnt++;
	}
	return cnt;
}