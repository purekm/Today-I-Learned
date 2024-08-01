#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#define MAXL	5
#define MAXF	10

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <stdio.h>

static int N, M;
#define INIT			1
#define ADD				2
#define DEL				3
#define RECOMMEND		4
#define	MAXL			5
#define MAXF			10

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

static bool run()
{
	int cmd;
	int id, F, ids[MAXF];
	int id1, id2;
	int len, len_a;
	int list[MAXL], list_a[MAXL];
	
	bool okay;

	okay = false;

	scanf("%d", &M);

	for (int k = 0; k < M; ++k)
	{
		scanf("%d", &cmd);
		switch(cmd)
		{
		case INIT:
			scanf("%d", &N);
			init(N);
			okay = true;
			break;
		case ADD:
			scanf("%d %d", &id, &F);
			for (int i = 0; i < F; ++i)
				scanf("%d", &ids[i]);
			if (okay)
				add(id, F, ids);
			break;
		case DEL:
			scanf("%d %d", &id1, &id2);
			if (okay)
				del(id1, id2);
			break;
		case RECOMMEND:
			scanf("%d %d", &id, &len_a);
			for (int i = 0; i < len_a; ++i)
				scanf("%d", &list_a[i]);
			if (okay)
			{
				len = recommend(id, list);
				if (len != len_a)
					okay = false;

				for (int i = 0; okay && i < len_a; ++i)
					if (list[i] != list_a[i])
						okay = false;
			}
			break;
		}
	}
	
	return okay;
}

int main()
{
	int TC, MARK;
	
    //freopen("sample_input.txt", "r", stdin);

	setbuf(stdout, NULL);
    scanf("%d %d", &TC, &MARK);

    for (int testcase = 1; testcase <= TC; ++testcase)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", testcase, score);
    }


    return 0;
}