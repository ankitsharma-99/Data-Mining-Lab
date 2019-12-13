#include<bits/stdc++.h>
#include<fstream>
using namespace std;
#define g 7

int t=14; 
map< string,set<string> > out_split;//possible outcomes of all criterias 
 
typedef 
struct node
{
	string _atr;
	string _class;
	bool isleaf;
//	node *branch[g];
  map< string,node* > branch;
	node()
	{
	//	branch=new node[g];
	    _atr="";
		_class="";
		isleaf=false;
		/*for(int i=0;i<g;i++)
		branch[i]=NULL;*/
	}
}*BTPTR; 
 
 
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
 
string majority(map< int,vector<string> > D)
{
	map< int,vector<string> > ::iterator it;
it=D.begin();
map< string,int > maj; 
for(;it!=D.end();it++)
{
	vector<string> v=(*it).second;
	string s=v[4];
	maj[s]++;
}

map< string,int > ::iterator it1;
int mx=0;
string ss;
for(it1=maj.begin();it1!=maj.end();it1++)
{
	int ff=(*it1).second;
    if(ff>mx)
    {
    	mx=ff;
    	ss=(*it1).first;
	}
}
return ss;


} 
 

double info(map< int,vector<string> > D) 
{
	map< int,vector<string> > ::iterator it;
  map< string,double > cnt;
   map< string,double > ::iterator it1;
  double d=0;

  for(it=D.begin();it!=D.end();it++)
  {
       	vector<string> vv=(*it).second;
       	int nn=vv.size();
       	//cout<<"\n"<<nn<<"____\n";
       	cnt[vv[nn-1]]++;
       	d++;
  }
  double infod=0;
  for(it1=cnt.begin();it1!=cnt.end();it1++)
  {
  	double pi=(*it1).second;
  	pi/=d;
  	double logpi=log2(pi);
  	infod+=(pi*logpi);
  }
  infod*=-1;
  return infod;
}

string attribute_selection(map< int,vector<string> > D,vector<string> attr)
{
	map< int,vector<string> > ::iterator it;
	double infod=info(D);
	
 // cout<<infod<<" ";
  
  map< int,vector<string> > atl;
  int nn=attr.size();

  for(it=D.begin();it!=D.end();it++)
  {
	vector<string> v=(*it).second;
	for(int i=0;i<v.size();i++)
	atl[i].push_back(v[i]);	
  }
  
    int ee=atl[0].size();
  
  double mxgain=-1;
  
  string s_attr;
  
  for(int i=0;i<attr.size()-1;i++)
  {
  	it=D.begin();
  	vector<string> vv;
  	map< string,int > mp;
  	
	map< string,int > ::iterator it1;
	
  	map< string,vector< pair< int,vector<string> > > > d;
  	
  	
  	
  	double gain,info_a=0;
  	vv=atl[i];
  	for(int j=0;j<vv.size();j++)
  	{
  	  mp[vv[j]]++;
  	  vector<string> rr,pp;
  	  pp=(*it).second;
  	  
  	  for(int k=0;k<nn;k++)
  	  {
    if(k!=i)		
  	  rr.push_back(pp[k]);
  }
  	  
		d[vv[j]].push_back(make_pair(mp[vv[j]],rr));	
		it++;
	  }
	int ix=0;
	for(it1=mp.begin();it1!=mp.end();it1++)
	{
		int y=(*it1).second;
		string ss=(*it1).first;
		double x=(double)y;
		 double gh=(double)ee;
		vector< pair< int,vector<string> > > op=d[ss];
		
		map< int,vector<string> > dp;
		for(int uu=0;uu<op.size();uu++)
		{
			 pair< int,vector<string> > pi=op[uu];
			 dp[pi.first]=pi.second;
		}
		
		info_a+=(x/gh)*info(dp);
	 }  
	 
   gain=infod-info_a;
   if(gain>mxgain)
   {
   	mxgain=gain;
   	s_attr=attr[i];
		 }	  
  	//cout<<"__&__"<<gain<<"\n";
  }
  return s_attr;
  
  
} 


BTPTR create(map< int,vector<string> > D,vector<string> attr)
{
//	cout<<"hi\n";
	/*	map< int,vector<string> > ::iterator itt;
		for(itt=D.begin();itt!=D.end();itt++)
		{
			int x=(*itt).first;
			cout<<x<<"__";
			vector<string> v=(*itt).second;
			for(int i=0;i<v.size();i++)
			cout<<v[i]<<" ";
			cout<<"\n";
		}*/
	//	cout<<"####";
	BTPTR T= new node();
	//checking if tuples in D are of same class
map< int,vector<string> > ::iterator it;
it=D.begin();
int f=0;
int nn=attr.size();
//cout<<"+++_"<<nn<<"\n";
vector<string> v1=(*it).second;
it++;
//cout<<v1[nn-1]<<"{{{\n";
for(;it!=D.end();it++)
{
//	cout<<"_";
	vector<string> v=(*it).second;
//	cout<<v[nn-1]<<"^^^";
	if(v[nn-1]==v1[nn-1])
	{
		
	}
	else
	{
	//	cout<<"0000";
		f=1;
		break;
	}
}
//cout<<"$";
if(f==0)
{//cout<<"3";
	T->isleaf=true;
	T->_class=v1[nn-1];
	return T;
}
//cout<<"4";
//if attribute list is empty
if(attr.size()==0)
{
//	cout<<"5";
	T->isleaf=true;
	T->_class=majority(D);
	return T;
}
//cout<<"6";
string ss=attribute_selection(D,attr);
//cout<<ss<<" ";
//best attribute selected
T->_atr=ss;
vector<string> attr1;

int ix;
for(int i=0;i<attr.size();i++)
{
	if(attr[i]==ss)
	{
	ix=i;	
		
	}

}


it=D.begin();
	map< string,int > mp;
  	map< string,vector< pair< int,vector<string> > > > d;
	map< string,int > ::iterator it1;
	
for(;it!=D.end();it++)
{
	vector<string> vv=(*it).second,rr;
   string s1=vv[ix];
   mp[s1]++;
	
  
  	for(int i=0;i<vv.size();i++)
  	{
  		if(i!=ix)
  		rr.push_back(vv[i]);
	  }
   d[s1].push_back(make_pair(mp[s1],rr));
   
}



/*for(int i=0;i<attr1.size();i++)
{
cout<<attr1[i]<<" ";
} */



// checking if any dj is empty
//map< string,set<string> > ::iterator it2;
//int bix=0;
vector<string> new_attr;
for(int kk=0;kk<attr.size();kk++)
{
	if(kk!=ix)
	new_attr.push_back(attr[kk]);
}


set<string> ::iterator it2;
//set<string> st=out_split[attr[ix]];
set<string> st;
map< string,set<string> > ::iterator iy;
//cout<<attr[ix]<<"_^_\n";
for(iy=out_split.begin();iy!=out_split.end();iy++)
{
	string gh=(*iy).first;
//	cout<<"*"<<gh<<"\n";
	
	if(gh==attr[ix])
	st=(*iy).second;
	
}

for(it2=st.begin();it2!=st.end();it2++)
{
	string s2=*it2;
//	cout<<s2<<"__";
	if(mp[s2]==0)
	{
	T->branch[s2]=new node();
	T->branch[s2]->isleaf=true;
	T->branch[s2]->_class=majority(D);
	
	}
	else
	{
			map< int,vector<string> > dd;
		vector< pair< int,vector<string> > > vv=d[s2];
		for(int i=0;i<vv.size();i++)
		{
			pair< int,vector<string> > pi=vv[i];
			dd[pi.first]=pi.second;
		}
		
	
	//	cout<<"pp";
		
		T->branch[s2]=create(dd,new_attr);
	}
}
return T;

 
}
 
 set< pair< string,string > > ::iterator it9;
string traverse(BTPTR T,map< string,string >  inp)
{
 /* 	for(it9=inp.begin();it9!=inp.end();it9++)
  	{
  		
	  }*/
	 while(T!=NULL&&T->isleaf==false)
	 {
	 	T=T->branch[inp[T->_atr]];
	 	
	  } 
	  if(T->isleaf==true)
	  return T->_class;
	  
} 
 
 
 
 
 
 
 
int main()
{
	vector< string > attr;
	map< int,vector<string> > tran;
	ifstream fin;
	ofstream fout;
	string s;
	int tn=1;
	fin.open("decisiontree_inp.txt");
	
int ff=0;
	while(fin)
	{
		getline(fin,s);
		if(ff==0)
		{
			ff=1;
			int i=0;
			string s1="";
			int IU=0;
			while(i<s.length())
			{
				if(s[i]==' '&&IU==0)
				{
					if(s1.compare("RID")!=0)
					attr.push_back(s1);
					s1="";
					IU=1;
				}
				
				else if(s[i]>='A'&&s[i]<='Z')
				{
				
				s1+=s[i];
				IU=0;
			}
				i++;
			}
			
				attr.push_back(s1);
		}
		
	//	vector<string> vv;
		
		if(s[0]>='0'&&s[0]<='9'&&tn<=t)
		{
			int i=0,v=0,f=0;
			
			while(i<s.length()&&s[i]>='0'&&s[i]<='9')
			i++;
			while(i<s.length()&&s[i]==' ')
			i++;
			
			
			string s1="";
			while(i<s.length())
			{
				
			     if(s[i]>='a'&&s[i]<='z')
				{
					f=0;
					s1+=s[i];
				//	cout<<"__#__"<<s1<<"\n";
				}
			
				else
				{
					if(f==0)
					{
					//cout<<"__$__"<<s1<<"\n";
					tran[tn].push_back(s1);
					f=1;
				    }
					s1="";
				}
				i++;
			}
				if(f==0)
					{
				//	cout<<"__$__"<<s1<<"\n";
					tran[tn].push_back(s1);
					f=1;
				    }
			tn++;
		}
	}
	
//	cout<<attr.size();
vector<string> attr1;
	for(int i=0;i<attr.size();i++)
	{
		if(attr[i]!="")
		attr1.push_back(attr[i]);
	}
/*for(int i=0;i<attr1.size();i++)
	{
	cout<<attr1[i]<<" ";
	}*/
//		cout<<attr1.size();

	map< int,vector<string> > ::iterator it;

for(int i=0;i<attr1.size()-1;i++)
{
	it=tran.begin();
   string ss=attr1[i];
	for(;it!=tran.end();it++)
	{
		vector<string> vv=(*it).second;
		out_split[ss].insert(vv[i]);	
	}
	
}
/*	map< string,set<string> > ::iterator itt;
	for(itt=out_split.begin();itt!=out_split.end();itt++)
	{
		cout<<(*itt).first<<"\n";
			set<string> st=(*itt).second;
		set<string> ::iterator yu;
		for(yu=st.begin();yu!=st.end();yu++)
		cout<<*yu<<"__";
		cout<<"\n";	
		}*/


BTPTR root=create(tran,attr1);	

map< string,string >  inp;
string ss;
int  t;
cin>>t;
while(t--)
{

cout<<"Enter your input (consisting of 4 strings__age_income_student_creditrating):\n";
for(int i=0;i<4;i++)
{
	cin>>ss;
	inp[attr1[i]]=ss;
}

/*set<string> ::iterator it2;
it2=inp.begin();
for(;it2!=inp.end();it2++)
{
	pair< string,string > pi=*it2;
	string s1=pi.first;
	string s2=pi.second;
	
	
}*/
cout<<"\nclass of your input:"<<traverse(root,inp)<<"\n";


}
/*cout<<root->_atr<<"\n";
cout<<root->branch["senior"]->branch["fair"]->_class<<"\n";
cout<<root->branch["middleaged"]->_class<<"\n";
cout<<root->branch["youth"]->_atr<<"\n";
cout<<root->branch["youth"]->branch["no"]->_class<<"\n";*/
	// printing each tuple
	
	/*	map< int,vector<string> > ::iterator it;
		for(it=tran.begin();it!=tran.end();it++)
		{
			int x=(*it).first;
			cout<<x<<"__";
			vector<string> v=(*it).second;
			for(int i=0;i<v.size();i++)
			cout<<v[i]<<" ";
			cout<<"\n";
		}*/
     
	 	
}


/*progress......
-->attribute selection correct.
-->tree constructed properly.
*/

