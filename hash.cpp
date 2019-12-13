#include<bits/stdc++.h>
#include<fstream>
using namespace std;
double min_sup=3;
int t=9;
int n=5;

map< set<int>,int > ht;
int hc[7]={0}; 

map< set<int>,int > cnt;
int fr[10][6];
set< set<int> > mp,ans,ans1;
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
		{
			cout<<*it<<" ";
		}
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
		{
			cout<<*it<<" ";
		}
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
			{
				st1.insert(v[j]);
			}
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
    
	set<int>::iterator it;
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
		 // int gg=c;
		c=(double) c;
		if(c>=min_sup)
		{
	 // cnt[st]=gg;	
		return true;
	}
		return false;
    	
}
int main()
{
	vector< set<int> > prev,cur,can;

    
	
	for(int i=1;i<=n;i++)
	{
		set<int> st;
		st.insert(i);
		prev.push_back(st);
	}
	
	for(int i=0;i<=t;i++)
	{
		for(int j=0;j<=n;j++)
		fr[i][j]=0;
	}
	
    string s;
    int z;
    
	ifstream fin;
	fin.open("ap1.txt");
int tn=1;
string s1="";
	while(fin)
	{
		getline(fin,s);
		
//	cout<<s<<endl;
		if(s[0]>='0'&&s[0]<='9'&&tn<=9)
		{
			int i=0,v=0;
			//cout<<s.length();
			while(i<s.length())
			{
			  	if(s[i]>='0'&&s[i]<='9')
			  	v=(v*10)+(s[i]-'0');
			  	else if(s[i]==' ')
			  	{
			  	   fr[tn][v]=1;
			      set<int> st;
			      st.insert(v);
			    // cout<<v<<" ";
			     	cnt[st]++;
			  		v=0;
				 }
				 i++;
			}
			   set<int> st;
			      st.insert(v);
			      	   fr[tn][v]=1;
			     //cout<<v<<" ";
			     	cnt[st]++;

			tn++;
	       //cout<<"\n";
		}	
		
	}
	fin.close();
   
for(int i=1;i<=t;i++)
{
	for(int j=1;j<=n;j++)
	cout<<fr[i][j]<<" ";
	cout<<"\n";
		}		
		
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
	cout<<prev.size();
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
					
				//	cout<<"1_";
					if(allsub(st3))
					{
					//	cout<<"2_";
					   if(l==2)
					   {
					   	//hashing
				         set<int> ::iterator it;
				         int vv=0;
				         for(it=st3.begin();it!=st3.end();it++)
				         {
				         	int hh=*it;
				         	vv=(vv*10)+hh;
				         	
						 }
						 
						 int yy=0;
						 for(int kk=1;kk<=t;kk++)
						 {
						 	int cc=0;
						 	for(it=st3.begin();it!=st3.end();it++)
						 	{
						 		if(fr[kk][*it]==1)
						 		cc++;
							 }
							 if(cc==st3.size())
							 yy++;
						 }
						 
						 
						 vv=vv%7;
						 ht[st3]=vv;
						 hc[vv]+=yy;
						 
						 
						 //cout<<"__"<<hc[vv]<<"\n";
					   }
					   else
					   {
						can.push_back(st3);
					
						
						if(isfreq(st3))
						{
                       // cout<<"3_";
						cur.push_back(st3); 
						mp.insert(st3);
					   }
				     }
					}
				}
			}
		}
		if(l==2)
		{
			for(int i=0;i<7;i++)
			{
				double rr=(double) hc[i];
				if(rr>=min_sup)
				{
					map< set<int>,int > ::iterator it;
					for(it=ht.begin();it!=ht.end();it++)
					{
						set<int> st4=(*it).first;
							can.push_back(st4);
						if(isfreq(st4))
						{
							cur.push_back(st4); 
						mp.insert(st4);
						}
					}
				}
			}
		}
		
		
		if(can.size()==0||cur.size()==0)
		break;
		cout<<"c:\n";
		printc(can);
		cout<<"l:\n";
    	printl(cur);
		
		prev.clear();
		prev=cur;
	   
		
		
		l++;
	}
	
}
