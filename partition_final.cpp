#include<bits/stdc++.h>
#include<fstream>
using namespace std;
#define pb push_back
int t=100;
int n=10;
int part_sz=20;
double min_sup_per=0.4;//min support percentage

map< set<int>,int > support; 

set< set<int> > glob_can,freq;


bool allsub(set<int> st,set< set<int> > loc_prev)
{
	set<int> st1=st;
	set<int> ::iterator it;
	it=st1.begin();
	for(int i=0;i<st.size();i++)
	{
		st.clear();
		st=st1;
		st.erase(st.find(*it));
		if(loc_prev.find(st)==loc_prev.end())
		return false;
	 } 
	 return true;
}


int count(set<int> st,vector< vector<int> > fr ,int sz)
{
/*	cout<<"hi\n";
	for(int i=1;i<=part_sz;i++)
	 {
	 
 for(int j=1;j<=n;j++)
 {
 cout<<fr[i][j]<<" ";
}
cout<<"\n";}*/

	int s=0;
	for(int i=1;i<=sz;i++)
	{
		vector<int> v=fr[i];
	    set<int> ::iterator it;
	    it=st.begin();
	    int f=0;
	    for(;it!=st.end();it++)
	    {
	    	if(v[*it]==0)
	    	{
	    		f=1;
	    		break;
			}
		}
		if(f==0)
		s++;
		
	}
	support[st]=s;
	return s;
}



void print(set< set<int> > v)
{
	set< set<int> > ::iterator it1;
	it1=v.begin();
	set<int> st2;
	set<int> ::iterator it2;
	for(;it1!=v.end();it1++)
	{
		set<int> st=*it1;
		it2=st.begin();
		for(;it2!=st.end();it2++)
		cout<<*it2<<" ";
		cout<<"______"<<support[st];
		cout<<"\n";
	}
}
void apriori(map< int,set<int> > tran,int sz)
{
 set< set<int> > loc_can,loc_prev,loc_freq;
 
 vector< vector<int> > fr(sz+1);
 for(int i=0;i<=sz;i++)
 {
 	fr[i]=vector<int> (n+1);
 	
 }
 for(int i=0;i<=sz;i++)
 for(int j=0;j<=n;j++)
 fr[i][j]=0;
// int fr[sz+1][n+1]={{0}};
 int on[n+1]={0};	//to check which 1 items are present in given tranactions
 map< int,set<int> > ::iterator it;
 it=tran.begin();
 double th=(double)sz;
 double min_sup=ceil(min_sup_per*th);

 //cout<<"_________"<<min_sup<<"\n";
 
 for(;it!=tran.end();it++)
 {
 	set<int> st=(*it).second;
 	int tn=(*it).first;
 	set<int> ::iterator it1;
 	it1=st.begin();
 	for(;it1!=st.end();it1++)
 	{
 		fr[tn][*it1]=1;
 		on[*it1]=1;
	 }
  }
  
   /*for(int i=1;i<=part_sz;i++)
	 {
	 
 for(int j=1;j<=n;j++)
 {
 cout<<fr[i][j]<<" ";
}
cout<<"\n";}*/
  
  for(int i=1;i<=n;i++)
  {
  	if(on[i]==1)
  	{
  		set<int> st;
  		st.insert(i);
  		loc_can.insert(st);
  		
  		if(count(st,fr,part_sz)>=min_sup)
  		{
  			glob_can.insert(st);
  			loc_prev.insert(st);
	    }
	  }
  }
    cout<<"local freq of sz "<<1<<"\n";
  print(loc_prev);
  int l=2;
  set< set<int> > ::iterator it1,it2;
  while(1)
  {
  	loc_can.clear();
  	loc_freq.clear();
  	it1=loc_prev.begin();
  	for(;it1!=loc_prev.end();it1++)
  	{
  		it2=it1;
  		it2++;
  		for(;it2!=loc_prev.end();it2++)
  		{
  			set<int> st1=*it1;
  			set<int> st2=*it2;
  			set<int> st3;
  			set<int> ::iterator i1,i2;
  			for(i1=st1.begin();i1!=st1.end();i1++)
  			st3.insert(*i1);
  				for(i2=st2.begin();i2!=st2.end();i2++)
  			st3.insert(*i2);
  			if(st3.size()==l)
  			{
  				if(allsub(st3,loc_prev))
  				{
  					loc_can.insert(st3);
  					if(count(st3,fr,part_sz)>=min_sup)
  					{
  						loc_freq.insert(st3);
  						glob_can.insert(st3);
					  }
				  }
			  }
		  }
  		
	  }
	  if(loc_freq.size()==0||loc_can.size()==0)
	  break;
	
	  cout<<"local freq of sz "<<l<<"\n";
	  print(loc_freq);
	  loc_prev.clear();
	  //glob_can.insert(loc_freq);
	  loc_prev=loc_freq;
	  l++;
  }
  
  
}

void apriori_2(map< int,set<int> > tran)
{
	 vector< vector<int> > fr(t+1);
 for(int i=0;i<=t;i++)
 {
 	fr[i]=vector<int> (n+1);
 	
 }
 for(int i=0;i<=t;i++)
 for(int j=0;j<=n;j++)
 fr[i][j]=0;
 
  map< int,set<int> > ::iterator it;
 it=tran.begin();
 
 for(;it!=tran.end();it++)
 {
 	set<int> st=(*it).second;
 	int tn=(*it).first;
 	set<int> ::iterator it1;
 	it1=st.begin();
 	for(;it1!=st.end();it1++)
 	{
 		fr[tn][*it1]=1;
 		
	 }
  }
  
   double th=(double)t;
 double min_sup=ceil(min_sup_per*th);
  
  
  set< set<int> >:: iterator itt;
  for(itt=glob_can.begin();itt!=glob_can.end();itt++)
  {
  	set<int> st=*itt;
  	if(count(st,fr,t)>=min_sup)
  	freq.insert(st);
  }
  
  
}




int main()
{
	ifstream fin;
	ofstream fout;
	string s;
	fin.open("ap2.txt");
	map< int,set<int> > tran;
	int tn=1;
	while(fin)
	{
		getline(fin,s);
		if(s[0]>='0'&&s[0]<='9'&&tn<=t)
		{
			int i=0,v=0;
				set<int> st;
			while(i<s.length())
			{
				if(s[i]==' ')
				{
				
					st.insert(v);
					//tran[tn]=st;
					v=0;
				
				}
				else
				v=(v*10)+(s[i]-'0');
				i++;
			}
			st.insert(v);
			tran[tn]=st;
			tn++;
		}
	}
	/*	map< int,set<int> > ::iterator it;
		it=tran.begin();
		for(;it!=tran.end();it++)
		{
			set<int> st;
			st=(*it).second;
			set<int> ::iterator it1;
			it1=st.begin();
			for(;it1!=st.end();it1++)
			cout<<*it1<<" ";
			cout<<"\n";
		}*/

  map< int,set<int> > ::iterator it;
  it=tran.begin();
  int c=0;
  
 
  
  
  while(it!=tran.end())
  {
  	c=0;
  	map< int,set<int> > temp_tran;
  	
  	
  	
  	while(c<part_sz)
  	{
  		int tnn=c+1;
  		set<int> st=(*it).second;
  		temp_tran[tnn]=st;
  		c++;
  		it++;
	}
	
	//applying apriori on temp_tran
	apriori(temp_tran,part_sz);
//	it++;
  }
cout<<"global candidates are:\n";
print(glob_can);

apriori_2(tran);

cout<<"finally frequent items are:\n";
print(freq);
	
}
