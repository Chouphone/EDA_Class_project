//simple EDA, Q-X logic simplelify
// chouphone
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<map>
#include<string>
using namespace std;
int n,m;//For max lenth
int cnt_m;
map <int, int>refer;
map <string , int> ans_visit;
struct node
{	
	int one_num;
	int val;
	char bit_num[24];
	bool visit;
	vector <int> contain; //referenced number;
	bool operator<(const node&a) const
	{
		return one_num < a.one_num;
	}
	bool operator>(const node&a) const
	{
		return one_num > a.one_num;
	}
};
int input_data[500];
vector <node> ori;
vector <node> ans;
vector <vector <node> > db, dbt, db2;
int size[500];
bool cmp(const node &a,const node &b)
{
	return a < b;
}

int uni_digital(char s1[], char s2[], int bitnum, int & pos)// find unique number & find its position
{
	int sum=0;
	for(int i = 0; i < bitnum; i++)if(s1[i] != s2[i]) {sum++; pos=i;}
	return sum;
}
void work(int oder)//simplify once
{
	int pos = 0, posn =0;
	vector <node>::iterator iti,itj;
	vector <int>::iterator itk;
	pos = 0;
	vector <node> entry;
	node entru;
	for(int i = 0; i <= oder - 1; i++)
	{
		entry.clear();
		//iti = db[i].begin()
		for(iti = (db[i]).begin(); iti != db[i].end() ; ++iti)
		{
			//printf("CNM!\n");
			for(itj = (db[i+1]).begin(); itj != (db[i+1]).end() ; ++itj)
			{
			//	printf("CNM!\n");
				if(uni_digital((*iti).bit_num, (*itj).bit_num, n, posn) == 1)
				{
					memcpy(entru.bit_num, (*iti).bit_num, n);
					entru.bit_num[posn] = 3;
					entru.one_num = (*iti).one_num;
					entru.visit = 0;
					entru.contain.clear();
					entru.contain.assign((*iti).contain.begin() , (*iti).contain.end());
					for(itk = (*itj).contain.begin() ; itk != (*itj).contain.end() ; itk++)entru.contain.push_back((*itk));
					entry.push_back(entru);
					(*iti).visit = 1; (*itj).visit = 1;
				}	
			}	
		}
		dbt.push_back(entry);
	}
	//int sum =0;
	for(int i = 0; i <= oder; i++)
	{
//		sum += db[i].size();
		for(iti = db[i].begin(); iti != db[i].end() ;iti++)
		{
			string stst;stst="";//stst = (*iti).bit_num;
		//	cout<<"stst="<<stst<<endl;
			for(int i = n-1; i >= 0; i--)
			stst += (char)((*iti).bit_num[i] + '0');
		//	printf("%d",(*iti).bit_num[i]);printf("\n");
	//		cout<<"stst" << stst <<endl;	
			if((*iti).visit == 0 && ans_visit[stst] == 0)
			{ans_visit[stst] = 1;ans.push_back((*iti));}
		}
	}
	//cout<<dbt.size()<<endl;
	db.clear();
//	cpy_db(db , dbt);
	db.assign(dbt.begin(), dbt.end());
	dbt.clear();
}
int ord;
int sp2[50];
int combine_tran(node re)
{
	int mb = 0;
	vector <int>::iterator iti;
	for(iti = re.contain.begin(); iti != re.contain.end(); iti++)
	{
		mb |= sp2[(*iti)];
	}
	return mb;
}
struct BFS_node
{
	int ode;
	int now;
	int select;
};
void output_ans(int control)
{
	int tmp = control;
	bool first = 1;
	vector <node>::iterator iti = ans.begin();
	cout<< " control code:" << control<<endl;
	printf("F = ");
	while(tmp != 0 && iti != ans.end())
	{
		if(tmp % 2 == 0)
		{tmp >>= 1; iti ++; continue;}
		//-------starting------
		if(!first)printf(" + ");
		for(int i = n-1 ; i>=0 ; i--)
		{
			if((*iti).bit_num[i] == 0)
			{printf("%c'", (char)('A' + n - i - 1));}
			if((*iti).bit_num[i] == 1)
			{printf("%c", (char)('A' + n - i - 1));}
		}
		first = 0;
		tmp >>= 1; ++iti;
	}
	printf("\n");
}
void out()
{
	while(db.size()!=0 && ord != -1)
	{
		work(ord);ord -- ;
	}
	printf("ans size:%lu\n", ans.size());
	//simplelify complete, starting combination.
	vector <node>::iterator iti;
	vector <int> resul_num;int tmp;
	vector <int>::iterator itj;
	resul_num.clear();
	int s = 1;
	for(int i = 0; i <= m + 1; i++){sp2[i] = s; s*=2;}
	queue <BFS_node> q;BFS_node vul1, vul2;
	map <int, int> visitor;visitor.clear();
	int pos=0;
	for(iti = ans.begin(); iti!= ans.end(); iti++)
	{
		tmp = combine_tran(*(iti)); 
		resul_num.push_back(tmp);
		vul1.ode = 1;vul1.now = tmp;
		vul1.select = 0 | sp2[pos];
		pos++;
		q.push(vul1);
		for(int i = n-1; i >= 0; i--)
		printf("%d",(*iti).bit_num[i]);printf("\n");
	}
	
	//-----------BFS starting -----------------
	int result = 0;
	while(!q.empty())
	{
		vul1 = q.front();
		q.pop();
		int uu = vul1.now;
		if(uu == sp2[m]-1)//all covered
		{
			result = vul1.select;
			break;
		}
		pos = 0;
		for(itj = resul_num.begin(); itj != resul_num.end(); itj++)
		{
			if((uu | (*itj)) != uu && visitor[(uu | (*itj))] == 0)
			{
				BFS_node entry;
				entry.ode = vul1.ode + 1 ;
				entry.now = (uu | (*itj));
				entry.select =  vul1.select | sp2[pos];
				q.push(entry);
			}
			pos++;
		}
	}
	output_ans(result);
	
}
int main()
{
	cout << "test case number:\n"; cin >> m;
	cout << "Max Input_bit:\n"; cin >> n;
	int tmp,pos = 0, c1;
	cnt_m = m;
	for (int i = 0; i < m; i++)
	{
		cin >> tmp;
		node se;
		refer[tmp] = i ;// refrence of numbers
		input_data[i] = tmp;
		se.val = tmp; se.one_num = 0;se.visit = 0;
		pos = 0;
		for(int i = 0; i < 24 ; i++)se.bit_num[i] = '\0';
		while (tmp != 0)
		{
			se.bit_num[pos++] = tmp % 2;
			if (tmp % 2 == 1)se.one_num++;
			tmp >>= 1;
		}
		se.contain.push_back(i);
		ori.push_back(se);
	}
	sort(ori.begin(), ori.end(), cmp);
	db.resize(n+1);pos=0;
	for(int i = 0; i <= n; i++)//Init Original database
	{
		while(pos < m && ori[pos].one_num == i )
		{
			ord = max(ord, i );
			db[i].push_back(ori[pos]);
			pos++;
		}
		size[i] = pos;
	}
	out();
	return 0;
}
