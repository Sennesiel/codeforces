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