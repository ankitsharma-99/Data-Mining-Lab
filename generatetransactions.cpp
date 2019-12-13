#include<bits/stdc++.h>
#include<fstream>
using namespace std;
string tostring(int n)
{
	string s="";
	char ch;
	int d;
	while(n)
	{
		d=n%10;
		ch= d+'0';
		s=ch+s;
		n/=10;
	}
	return s;
}
int toint(string s)
{
	int v=0;
	for(int i=0;i<s.length();i++)
	{
		v=(v*10)+(s[i]-'0');
	}
	return v;
}
int main()
{
	int t=100;
	int n=10;
	ofstream fout;
	fout.open("tran.txt");
	
	string s;
	
	int cnt[n+1]={0};
	
	
	for(int i=0;i<t;i++)
	{
		set<int> st;
		set<int> ::iterator it;
		int y=(rand()%n)+1;
		s=tostring(i+1);
		fout<<"Transaction"<<s<<": ";
	

        int c=0,x; 

		while(c<y)
		{
		x=(rand()%n)+1;	
		while(st.find(x)!=st.end())
		{
			x=(rand()%n)+1;
		}
		if(st.find(x)==st.end())
		{
		//	s=tostring(x);
		//	fout<<s<<" ";
		
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
	
	ifstream fin;
	fin.open("tran.txt");
	while(fin)
	{
		getline(fin,s);
		cout<<s<<endl;
     }
	
	fin.close();
	fin.open("tran.txt");
	int z;
	while(fin>>s)
	{
		if(s[0]>='0'&&s[0]<='9')
		{
			z=toint(s);
			cnt[z]++;
		}
	}
	for(int i=1;i<=n;i++)
	{
		cout<<"freq of "<<i<<": "<<cnt[i]<<"\n";
	}
	
	
}
