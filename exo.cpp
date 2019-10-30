#include <bits/stdc++.h>
using namespace std;

typedef struct sparse_table
{
	vector<vector<int>> tab;
	bool estMax;
	int mm(int a, int b){estMax?return max(a,b):return min(a,b);}
	void build(vector<int> debut)
	{
		int taille = debut.size();
		tab.push_back(debut);
		for(int i = 1; i <= 20; i++)
		{
			if(1 << i <= taille)
			{
				vector<int> v;
				tab.push_back(v);
				for(int j = 0; j <= taille - (1 << i); j++)
				{
					tab[i].push_back(mm(tab[i - 1][j],tab[i - 1][j + (1 << (i - 1))], estMax));
				}
			}
		}
	}

	int query(int debut, int fin)
	{
		int i = 0;
		while( 1 << i <= fin-debut)
		{
			i++;
		}
		i--;
		if(debut == fin){i=0;}
		return mm(tab[i][debut],tab[i][fin-(1<<i)+1/***/],estMax);
	}
}sparse_table;


typedef struct event
{
	int cool;
	int id;
	bool operator< (const event & other) const
	{
		return cool > other.cool;
	}
}event;

int nTrack;
vector<int> track;
vector<event> suite;
sparse_table minimum;
sparse_table maximum;

bool init()
{
	scanf("%d", &nTrack);
	int maxi = 0;
	int mini = 100000;
	for(int iTrack = 0; iTrack < nTrack; iTrack++)
	{
		int in;
		scanf("%d", &in);
		maxi = max(maxi,in);
		mini = min(mini,in);
		track.push_back(in);
		suite.push_back({in,iTrack});
	}
	if(mini * 2 >= maxi)
	{
		for(int i = 0; i < nTrack; i++)
		{
			printf("-1 ");
		}
		return false;
	}
	sort(suite.begin(), suite.end());
	minimum.estMax = false;
	maximum.estMax = true;
	minimum.build(track);
	maximum.build(track);
	return true;
}

int main()
{
	if(init()==false){return 0;}

	for(int iT = 0; iT < nTrack; iT++)
	{	
		pair<int,int> interMax = make_pair(suite[iT].id + 1,nTrack - 1);
		pair<int,int> interMin = make_pair(suite[iT].id + 1,nTrack - 1);
		int posinf = 10000000;
		int possup = 10000000;
		if(suite[iT].id != nTrack - 1)
		{
			if(minimum.query(interMin.first, interMin.second) * 2 < suite[iT].cool)
			{
				while(interMin.first != interMin.second)
				{
					int mid = (interMin.first + interMin.second)/2;
					if(minimum.query(interMin.first, mid) * 2 < suite[iT].cool)
					{
						interMin.second = mid;
					}
					else
					{
						interMin.first = mid + 1;
					}
				}
				posinf = interMin.first - suite[iT].id;
			}

			if(maximum.query(interMax.first, interMax.second) > suite[iT].cool)
			{
				while(interMax.first != interMax.second)
				{
					int mid = (interMax.first + interMax.second)/2;
					if(maximum.query(interMax.first, mid) > suite[iT].cool)
					{
						interMax.second = mid;
					}
					else
					{
						interMax.first = mid + 1;
					}
				}
				possup = interMax.first - suite[iT].id;
			}
			/*****************************************************************************/
			if(posinf == 10000000)
			{
				interMin = make_pair(0,suite[iT].id - 1);
				if(minimum.query(interMin.first, interMin.second) * 2 < suite[iT].cool)
				{
					while(interMin.first != interMin.second)
					{
						int mid = (interMin.first + interMin.second)/2;
						if(minimum.query(interMin.first, mid) * 2 < suite[iT].cool)
						{
							interMin.second = mid;
						}
						else
						{
							interMin.first = mid + 1;
						}
					}
					posinf = nTrack - suite[iT].id + interMin.debut;
				}
			}
			if(possup == 10000000)
			{
				interMax = make_pair(0,suite[iT].id - 1);
				if(maximum.query(interMax.first, interMax.second) > suite[iT].cool)
				{
					while(interMax.first != interMax.second)
					{
						int mid = (interMax.first + interMax.second)/2;
						if(maximum.query(interMax.first, mid) > suite[iT].cool)
						{
							interMax.second = mid;
						}
						else
						{
							interMax.first = mid + 1;
						}
					}
					possup = nTrack - suite[iT].id + interMax.debut;
				}
			}
		}
	}
}