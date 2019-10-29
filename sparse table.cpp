typedef struct sparse_table
{
	vector<vector<int>> tab;
	void build(vector<int> debut)
	{
		int taille = debut.size();
		tab.push_back(debut);
		for(int i = 1; i <= 20; i++)
		{
			if(1 << i <= taille)
			{
				for(int j = 0; j <= taille - (1 << i); j++)
				{
					tab[i][j] = min(tab[i - 1][j],tab[i - 1][j + (1 << (i - 1))]);
				}
			}
		}
	}
	int minimum(int debut, int fin)
	{
		int i = 0;
		while( 1 << i <= fin-debut)
		{
			i++;
		}
		i--;
		if(debut == fin){i=0;}
		return min(tab[i][debut],tab[i][fin-(1<<i)]);
	}
}sparse_table;