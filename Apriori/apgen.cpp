#include<bits/stdc++.h>
#include<fstream>
using namespace std;
ofstream fout;
double min_sup=38;
int t=100;
int n=10;
map< set<int>, int> cnt;
int fr[101][11];
set< set<int> > mp,ans,ans1;
string tostring(int n)
{
	string s="";
	char ch;
	int d;
	while(n)
	{
		d=n%10;
		ch=d+'0';
		s=ch+s;
		n/=10;
	}
	return s;
}
void printc(vector< set<int> > v)
{
	set<int> ::iterator it;
		string s;
	fout<<"C:"<<endl;
	for(int i=0;i<v.size();i++)
	{
		set<int> st=v[i];
		if(ans.find(st)!=ans.end())
		continue;
		ans.insert(st);
		for(it=st.begin();it!=st.end();it++)
		{
		s=tostring(*it);
		fout<<s<<" ";	
		cout<<*it<<" ";
	}
			fout<<":"<<cnt[st]<<endl;
		cout<<":"<<cnt[st]<<"\n";
	}
}
void printl(vector< set<int> > v)
{
	set<int> ::iterator it;
		string s;
	fout<<"L:"<<endl;
	for(int i=0;i<v.size();i++)
	{
		set<int> st=v[i];
		if(ans1.find(st)!=ans1.end())
		continue;
		ans1.insert(st);
		for(it=st.begin();it!=st.end();it++)
		{
				s=tostring(*it);
		fout<<s<<" ";
		cout<<*it<<" ";
	}
		fout<<":"<<cnt[st]<<endl;
		cout<<":"<<cnt[st]<<"\n";
	}
}
bool allsub(set<int> st)
{
	vector<int> v;
	set<int> ::iterator it;
	for(it=st.begin();it!=st.end();it++)
	v.push_back(*it);
	int nn=v.size();
	for(int i=0;i<(1<<nn);i++)
	{
		set<int> st1;
		for(int j=0;j<nn;j++)
		{
			if(i&(1<<j))
			st1.insert(v[j]);
		}
		if(st1.size()!=0&&st1.size()!=nn)
		{
			if(mp.find(st1)==mp.end())
			return false;
		}
	}
	return true;
}
bool isfreq(set<int> st)
{
	set<int> ::iterator it;
	int c=0;
	for(int i=1;i<=t;i++)
	{
		int f=0;
		for(it=st.begin();it!=st.end();it++)
		{
			if(fr[i][*it]==0)
			{
				f=1;
				break;
			}
		}
		if(f==0)
		c++;
	}
	cnt[st]=c;
	c=(double) c;
	if(c>=min_sup)
	return true;
	return false;
	
}
int main()
{
		fout.open("genaprio.txt");
	vector< set<int> > prev,cur,can;
	for(int i=1;i<=n;i++)
	{
		set<int> st;
		st.insert(i);
		prev.push_back(st);
	}
	for(int i=0;i<=t;i++)
	for(int j=0;j<=n;j++)
	fr[i][j]=0;
	
	ofstream fout;
	fout.open("ap2.txt");
	string s;
	for(int i=0;i<t;i++)
	{
		set<int> st;
		set<int> ::iterator it;
		int y=(rand()%n)+1;
		s=tostring(i+1);
		
		fout<<"Transaction "<<s<<endl;
		int c=0,x;
		while(c<y)
		{
			x=(rand()%n)+1;
			while(st.find(x)!=st.end())
				x=(rand()%n)+1;
				if(st.find(x)==st.end())
				{
					st.insert(x);
					c++;
				}
		}
		for(it=st.begin();it!=st.end();it++)
		{
			x=*it;
			s=tostring(x);
			fout<<s<<" ";
		}
		 fout<<endl;
		 
	}
	fout.close();
	int z;
//	cout<<"op";
		ifstream fin;
	fin.open("ap2.txt");
	int tn=1;
	   
	string s1="";
	while(fin)
	{
		getline(fin,s);
		int v;
		if(s[0]>='0'&&s[0]<='9'&&tn<=t)
		{
			int i=0;
			v=0;
			while(i<s.length())
			{
				if(s[i]>='0'&&s[i]<='9')
				v=(v*10)+(s[i]-'0');
				else if(s[i]==' ')
				{
					fr[tn][v]=1;
					set<int> st;
					st.insert(v);
					cnt[st]++;
					v=0;
				}
				i++;
			}
		
		set<int> st;
		st.insert(v);
		fr[tn][v]=1;
		cnt[st]++;
		tn++;
	}
		//cout<<"p";
	}
	fin.close();
	
	cout<<"c1:\n";
	printc(prev);
	for(int i=0;i<prev.size();i++)
	{
		set<int> st=prev[i];
		if(cnt[st]>=min_sup)
		{
			mp.insert(st);
			cur.push_back(st);
		}
	}
	cout<<"l1:\n";
	printl(cur);
	prev.clear();
	prev=cur;
	set<int> ::iterator it;
	int l=2;
	while(1)
	{
		cur.clear();
		can.clear();
		for(int i=0;i<prev.size()-1;i++)
		{
			set<int> st1=prev[i];
			for(int j=i+1;j<prev.size();j++)
			{
				set<int> st2=prev[j];
				set<int> st3;
				for(it=st1.begin();it!=st1.end();it++)
				st3.insert(*it);
					for(it=st2.begin();it!=st2.end();it++)
				st3.insert(*it);
				if(st3.size()==l)
				{
					//cout<<"hi";
					
					if(allsub(st3))
					{
						//cout<<"op";
						can.push_back(st3);
					//	cout<<"hey"<<cnt[st3]<<"**";
						if(isfreq(st3))
						{
						//	cout<<"iu";
							cur.push_back(st3);
							mp.insert(st3);
						}
					}
				}
			}
		}
		if(can.size()==0||cur.size()==0)
		break;
		cout<<"C:\n";
		printc(can);
			cout<<"L:\n";
		printl(cur);
   prev.clear();
   prev=cur;
   l++;		
	//	cout<<"hi";
	}
	
}

