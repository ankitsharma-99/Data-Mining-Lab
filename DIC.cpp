#include<bits/stdc++.h>
#include<fstream>
using namespace std;
map< set<int>,int > mp;

map< set<int>,pair<int,int> > ds,dc,temp_dc,temp_ds;
vector< set<int> > ss,sc;
	int num_items=5;
	int num_tran=9;
	int M=3;
	int min_sup=3;


/*int num_items=10;
	int num_tran=100;
	int M=20;
	int min_sup=38;*/
	
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
bool search(set<int> st,set<int> base)
{
	set<int> ::iterator it1,it2;
	it1=st.begin();
	it2=base.begin();
//	cout<<"$$$";
	while(it1!=st.end()&&it2!=base.end())
	{
		if(*it1==*it2)
		{
			//cout<<*it1<<" "<<*it2<<"\n";
			it1++;
			it2++;
		}
		else if(*it1>*it2)
		{
			it2++;
		}
		else
		break;
		
	}
	if(it1==st.end())
	return true;
	return false;
}


int main()
{
	ifstream fin;
	ofstream fout;
fin.open("ap1.txt");
	
   map<int, set<int> > tran;
   
   
   string s;
   int tn=1;
   
   
	while(fin)
	{
		getline(fin,s);
		
//	cout<<s<<endl;
		if(s[0]>='0'&&s[0]<='9'&&tn<=num_tran)
		{
			int i=0,v=0;
			//cout<<s.length();
			while(i<s.length())
			{
			  	if(s[i]>='0'&&s[i]<='9')
			  	v=(v*10)+(s[i]-'0');
			  	else if(s[i]==' ')
			  	{
			  	   //fr[tn][v]=1;
			      ///set<int> st;
			      //st.insert(v);
			    // cout<<v<<" ";
			    tran[tn].insert(v);
			     //	cnt[st]++;
			  		v=0;
				 }
				 i++;
			}
			   //set<int> st;
			      //st.insert(v);
			     // 	   fr[tn][v]=1;
			     //cout<<v<<" ";
			     	//cnt[st]++;
                 tran[tn].insert(v);
			tn++;
	       //cout<<"\n";
		}	
	 
	}

	fin.close();

	map<int, set<int> > ::iterator it_tr;
/*	for(it=tran.begin();it!=tran.end();it++)
	{
		int x=(*it).
	}*/
	
map< set<int>,pair<int,int> > ::iterator it;

for(int i=1;i<=num_items;i++)
{
	set<int> st;
	st.insert(i);
	pair<int,int> pi=make_pair(0,0);
	dc[st]=pi;
	mp[st]=1;
	}	
	//	cout<<tran.size()<<"\n";	
int yy=0;
it_tr=tran.begin();		
//cout<<"hi";
while((dc.size()>0||ds.size()>0))
{
	//cout<<"lo\n";
	if(it_tr==tran.end())
	it_tr=tran.begin();
     	int c=0;
     	vector< set<int> > T;
     	while(c<M&&it_tr!=tran.end())
     	{
     		T.push_back((*it_tr).second);
     		c++;
     		it_tr++;
		 }
		 //cout<<"("<<T.size()<<"\n";
		for(int t=0;t<T.size();t++)
		{
			temp_dc.clear();
			temp_ds.clear();
			
			
			set<int> base=T[t];
			//incrementing dc's counts;
			it=dc.begin();
		
			while(it!=dc.end())
			{
				set<int> st=(*it).first;
					  mp[st]=1;
				
				
				pair<int,int> pi=(*it).second;
				int sup=pi.first;
				int tr=pi.second;
				tr++;
				bool f=search(st,base);
			//	cout<<"+++++"<<f<<" ";
				if(f==1)
				{
					pair<int,int> pi=(*it).second;
				//	int sup=pi.first;
				//	int tr=pi.second;
					sup++;
					//tr++;
				//	pi=make_pair(sup,tr);
				}
				pi=make_pair(sup,tr);
				//temp_dc[st]=pi;
				
				if(tr==num_tran&&sup>=min_sup)
				ss.push_back(st);
				else if(tr==num_tran&&sup<min_sup)
				sc.push_back(st);
				else if(sup>=min_sup)
				ds[st]=pi;
				else
				temp_dc[st]=pi;
				
		/*	  set<int> ::iterator e;
			  e=st.begin();  
		    cout<<*e<<"->"<<sup<<"\n";*/
				
				it++;
			}
			
				
			
			
			
				it=ds.begin();
			while(it!=ds.end())
			{
				set<int> st=(*it).first;
				mp[st]=1;
				pair<int,int> pi=(*it).second;
				int sup=pi.first;
				int tr=pi.second;
				tr++;
				bool f=search(st,base);
				if(f==true)
				{
					pair<int,int> pi=(*it).second;
					int sup=pi.first;
					int tr=pi.second;
					sup++;
					//tr++;
				//	pi=make_pair(sup,tr);
				}
				pi=make_pair(sup,tr);
				
				if(tr==num_tran)
				ss.push_back(st);
				else
				temp_ds[st]=pi;
				it++;
			}
			ds.clear();
			dc.clear();
			ds=temp_ds;
			dc=temp_dc;
			
	//	cout<<ds.size()<<" "<<dc.size()<<"\n";
	
	//generating supersets using ss
	for(int i=0;i<ss.size();i++)
	{
		for(int j=i+1;j<ss.size();j++)
		{
			set<int> st1=ss[i];
			set<int> st2=ss[j];
			if(st1.size()==st2.size())
			{
				set<int> ::iterator e1,e2;
				set<int> st3;
				for(e1=st1.begin();e1!=st1.end();e1++)
				st3.insert(*e1);
				for(e2=st2.begin();e2!=st2.end();e2++)
				st3.insert(*e2);
				if(st3.size()==st1.size()+1&&st3.size()<=num_items&&mp[st3]==0)
				dc[st3]=make_pair(0,0);
			}
		}
	}
	//generating supersets using ds
	//	cout<<"^^:"<<ss.size()<<"\n";
	
	map< set<int>,pair<int,int> > ::iterator uu,vv;
	for(uu=ds.begin();uu!=ds.end();uu++)
	{
		vv=uu;
		vv++;
		for(;vv!=ds.end();vv++)
		{
			set<int> st1=(*uu).first;
			set<int> st2=(*vv).first;
			if(st1.size()==st2.size())
			{
				set<int> ::iterator e1,e2;
				set<int> st3;
				for(e1=st1.begin();e1!=st1.end();e1++)
				st3.insert(*e1);
				for(e2=st2.begin();e2!=st2.end();e2++)
				st3.insert(*e2);
				if(st3.size()==st1.size()+1&&mp[st3]==0)
				dc[st3]=make_pair(0,0);
			}
		}
	}
	
	
	

//	cout<<dc.size()<<" ";
		 } 
		//cout<<"ss.size():"<<ss.size()<<"\n"; 
		yy++;
	}

/*	for(int i=0;i<sc.size();i++)
	{
		set<int> st=sc[i];
		set<int> ::iterator it=st.begin();
		while(it!=st.end())
		{
			cout<<*it<<" ";
			it++;
		}
		cout<<"\n";
	}*/
	cout<<"freq\n";
	for(int i=0;i<ss.size();i++)
	{
		set<int> st=ss[i];
		set<int> ::iterator it=st.begin();
		while(it!=st.end())
		{
			cout<<*it<<" ";
			it++;
		}
	
		cout<<"\n";
	}
	
	
}

