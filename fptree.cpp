#include<bits/stdc++.h>
#include<fstream>
using namespace std;
#define pb push_back
#define num_items 5
int num_tran=9;
int min_sup=2;
map< int,int > cnt;



typedef 
struct node
{
	int item;
	int cnt;
	node *branch[num_items+1];
	node(int ii)
	{
		item=ii;
		cnt=0;
		for(int i=0;i<num_items+1;i++)
		branch[i]=NULL;
	}
}*BTPTR;

map< int,vector<BTPTR> > lev;//stores level order of fp tree



bool cmp(int a,int b)
{
	int x,y;
	x=cnt[a];
	y=cnt[b];
	if(x>y)
	return true;
	return false;
}


void level_p(BTPTR T,int l)
{
	if(T!=NULL)
	{
		lev[l].pb(T);
		for(int i=1;i<num_items+1;i++)
		{
		//	if(T->branch[i]!=NULL)
			level_p(T->branch[i],l+1);
		}
	}
}

int main()
{
	//ord_item stores ordered itemsets corresponding to each transaction 
	map< int,vector<int> > tran,ord_item; 
	ifstream fin;
	ofstream fout;
	string s;
	int tn=1;
	fin.open("ap1.txt");
	while(fin)
	{
		getline(fin,s);
		if(s[0]>='0'&&s[0]<='9'&&tn<=num_tran)
		{
			int i=0,v=0;
			vector<int> vv;
			while(i<s.length())
			{
				if(s[i]==' ')
				{
					vv.pb(v);
					cnt[v]++;
					v=0;
				}
				else
				{
					v=(v*10)+(s[i]-'0');
				}
				i++;
			}
			vv.pb(v);
			tran[tn]=vv;
		    cnt[v]++;
		    tn++;
		}
	}
		map< int,vector<int> > ::iterator it;
		it=tran.begin();
		for(;it!=tran.end();it++)
		{
			int x=(*it).first;
			vector<int> v=(*it).second;
			vector<int> v1;
			for(int i=0;i<v.size();i++)
			{
		   if(cnt[v[i]]>=min_sup)	
			v1.pb(v[i]);
		}
			sort(v1.begin(),v1.end(),cmp);
			ord_item[x]=v1;
		}
		
		
		it=ord_item.begin();
	
		//construct fp_tree
		BTPTR root=new node(-1);
		BTPTR T=root,p;
		for(;it!=ord_item.end();it++)
		{
			p=root;
	
			vector<int> v=(*it).second;
			for(int i=0;i<v.size();i++)
			{
		
				if(p->branch[v[i]]==NULL)
				p->branch[v[i]]=new node(v[i]);
	
				p->branch[v[i]]->cnt++;
				p=p->branch[v[i]];
			}
		}
		cout<<"\n";

		//printing fp tree level wise
		level_p(T,0);
		map< int,vector<BTPTR> > ::iterator it1;
		for(it1=lev.begin();it1!=lev.end();it1++)
		{
				int x=(*it1).first;
			
			vector<BTPTR> v=(*it1).second;
			for(int i=0;i<v.size();i++)
			cout<<v[i]->item<<":"<<v[i]->cnt<<"       ";
			cout<<"\n";
			
		}
		

}
