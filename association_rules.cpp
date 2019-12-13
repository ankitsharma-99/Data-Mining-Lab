#include<bits/stdc++.h>
#include<fstream>
using namespace std;
map< set<int> ,int > ht;
//int hc[7]={0};
double min_conf=0;
map< pair<int,int> ,int> fr;

double min_sup=3;
int t=9;
int n=5;
map< set<int>, int> cnt;
//int fr[10][6];
set< set<int> > mp,ans,ans1,ans2;
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
	for(int i=0;i<v.size();i++)
	{
		set<int> st=v[i];
		if(ans.find(st)!=ans.end())
		continue;
		ans.insert(st);
		for(it=st.begin();it!=st.end();it++)
		cout<<*it<<" ";
		cout<<":"<<cnt[st]<<"\n";
	}
}
void printl(vector< set<int> > v)
{
	set<int> ::iterator it;
	for(int i=0;i<v.size();i++)
	{
		set<int> st=v[i];
		if(ans1.find(st)!=ans1.end())
		continue;
		ans1.insert(st);
		for(it=st.begin();it!=st.end();it++)
		cout<<*it<<" ";
		cout<<":"<<cnt[st]<<"\n";
	}
}
/*void print(vector< set<int> > v)
{
	set<int> ::iterator it;
	for(int i=0;i<v.size();i++)
	{
		set<int> st=v[i];
		if(ans2.find(st)!=ans2.end())
		continue;
		ans2.insert(st);
		for(it=st.begin();it!=st.end();it++)
		cout<<*it<<" ";
		cout<<"\n";
	}
	
}*/
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
			if(fr[{i,*it}]==0)
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
/*void hashit(set<int> st)
{
	int v=0;
	set<int> ::iterator it;
	for(it=st.begin();it!=st.end();it++)
	{
		int x=*it;
		v=(v*10)+x;
		
	}
	int y=v%7;
	cout<<"hey:"<<y<<"\n";
//	cout<<"__"<<cnt[st]<<"\n";
	for(int u=0;u<cnt[st];u++)
	ht[y].push_back(st);
	
	
}*/
void generate(vector< set<int> > v)
{
		set<int> ::iterator it;
	for(int i=0;i<v.size();i++)
	{
		if(ans2.find(v[i])!=ans2.end())
		continue;
		ans2.insert(v[i]);
		//cout<<">>";
		set<int> st=v[i];
	//	if(ans2.find(st)!=ans2.end())
	//	continue;
	//	ans2.insert(st);
		//for(it=st.begin();it!=st.end();it++)
		//cout<<*it<<" ";
		
		vector<int> a;
		for(it=st.begin();it!=st.end();it++)
		a.push_back(*it);
		
		int nn=a.size();
	
		for(int j=0;j<(1<<nn);j++)
		{
				set<int> sub1,sub2;
			for(int k=0;k<nn;k++)
			{
				if(j&(1<<k))
				{
					sub1.insert(a[k]);
				}
			}
			if(sub1.size()!=0)
			{
			//	cout<<"HR";
				set<int> ::iterator it;
				for(int y=0;y<nn;y++)
				{
					if(sub1.find(a[y])==sub1.end())
					sub2.insert(a[y]);
				}
				if(sub2.size()!=0)
				{
				
					int tt1=0;
						for(int kk=1;kk<=t;kk++)
						{
						int cc=0;
						for(it=sub1.begin();it!=sub1.end();it++)
						{
							if(fr[{kk,*it}]==1)
							cc++;
						} 
						if(cc==sub1.size())
						tt1++;
				     	}
				     	//cout<<tt1<<" ";
				    int tt2=0;
						for(int kk=1;kk<=t;kk++)
						{
						int cc=0;
						for(it=sub2.begin();it!=sub2.end();it++)
						{
							if(fr[{kk,*it}]==1)
							cc++;
						} 
						if(cc==sub2.size())
						tt2++;
				     	}
				     	set<int> mo;
						  	for(it=sub2.begin();it!=sub2.end();it++)
						{
						//	if(fr[{kk,*it}]==1)
						//	cc++;
						mo.insert(*it);
						} 
							  	for(it=sub1.begin();it!=sub1.end();it++)
						{
						//	if(fr[{kk,*it}]==1)
						//	cc++;
						mo.insert(*it);
						}
						
				     	//cout<<tt2<<" ";
				     	
				     	int tt3=0;
				     	
				     		for(int kk=1;kk<=t;kk++)
						{
						int cc=0;
						for(it=mo.begin();it!=mo.end();it++)
						{
							if(fr[{kk,*it}]==1)
							cc++;
						} 
						if(cc==mo.size())
						tt3++;
				     	}
				     	
				     	
				     	//int ry=tt1+tt2;
				     	double ra=(double) tt3/tt1;
				     	
				     	if(ra>=min_conf)
				     	{
				     		cout<<"{";
				     			for(it=sub1.begin();it!=sub1.end();it++)
						     {
						     	cout<<*it<<" ";
						     }
						     cout<<" } ->";
						     	cout<<"{";
				     			for(it=sub2.begin();it!=sub2.end();it++)
						     {
						     	cout<<*it<<" ";
						     }
						     cout<<"}";
						     cout<<"___"<<ra;
						     cout<<"\n";
				     	}
				     }
				     	
					
					 	
			}
		}
		
	//	cout<<"\n";
	}
}
int main()
{
	vector< set<int> > prev,cur,can,asso;
	for(int i=1;i<=n;i++)
	{
		set<int> st;
		st.insert(i);
		prev.push_back(st);
	}
	for(int i=0;i<=t;i++)
	for(int j=0;j<=n;j++)
	fr[{i,j}]=0;
	
/*	ofstream fout;
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
	int z;*/
//	cout<<"op";
		ifstream fin;
	fin.open("bookeg.txt");
	int tn=1;
	string s;
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
					fr[{tn,v}]=1;
					set<int> st;
					st.insert(v);
					cnt[st]++;
					v=0;
				}
				i++;
			}
		
		set<int> st;
		st.insert(v);
		fr[{tn,v}]=1;
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
					/*if(l==2)
					{
						set<int> ::iterator it;
						int vv=0;
						for(it=st3.begin();it!=st3.end();it++)
						{
							int xx=*it;
							vv=(vv*10)+xx;
						}
						vv%=7;
						int tt=0;
						for(int kk=1;kk<=t;kk++)
						{
						int cc=0;
						for(it=st3.begin();it!=st3.end();it++)
						{
							if(fr[{kk,*it}]==1)
							cc++;
						} 
						if(cc==st3.size())
						tt++;
				     	}
						 ht[st3]=vv;
						 hc[vv]+=tt; 
					}*/
				//	else
				//	{
					
					if(allsub(st3))
					{
						//cout<<"op";
						can.push_back(st3);
					
					//	set<int> st4;
					    // hashit(st3);
					    // cout<<"ipu"<<cnt[st3]<<" ";
						if(isfreq(st3))
						{
						//	cout<<"iu";
							cur.push_back(st3);
							mp.insert(st3);
						}
					}
			//	}
				}
			}
		}
	/*	if(l==2)
		{
		
			for(int kk=0;kk<7;kk++)
			{
					double yy=hc[kk];
					if(yy>=min_sup)
					{
					
				map< set<int> ,int> ::iterator it;
				for(it=ht.begin();it!=ht.end();it++)
				{
					set<int> st4=(*it).first;
					int yu=(*it).second;
					if(yu==kk)
					{
					//	cout<<"io";
				     can.push_back(st4);
				     if(isfreq(st4))
						{
						//	cout<<"iu";
							cur.push_back(st4);
							mp.insert(st4);
						}
				 }
				}
			     }
			}
		}*/
		
		if(cur.size()==0||can.size()==0)
		break;
		
		/*for(int uu=0;uu<7;uu++)
		{
		double ji=(double) ht[uu].size();
		cout<<ji<<" ";
			if(ji>=min_sup)
			{
		   for(int pp=0;pp<ht[uu].size();pp++)
		   {	
			can.push_back(ht[uu][pp]);
		}
		}*/
	
		cout<<"C:\n";
		printc(can);
			cout<<"L:\n";
		printl(cur);
   prev.clear();
   prev=cur;
   generate(cur);
   /*if(l==3)
    {
    
    asso=cur;
     
    }*/
   l++;	
   }
   
 //print(asso);
    
//generate(asso);
	//	cout<<"hi";
}
	


