#include<stdlib.h>
#include "CSA.h"
#include<cstdio>
#include<cmath>
#include"ds_ssort.h"
#include<iostream>
using namespace std;
#define SearchKind 2


i32 CSA::Save(const char * indexfile)
{
	savekit s(indexfile);
	
	s.writeu64(198909102510);
	s.writei32(n);
	s.writei32(alphabetsize);
	
	s.writei32(SL);
	s.writei32(L);
	s.writei32(D);
	s.writei32(RD);
	
	//sal
	SAL->write(s);
	
	//ranl
	RankL->write(s);

	//code
	s.writei32(256);
	s.writei32array(code,256);
	//start
	s.writei32(alphabetsize+1);
	s.writei32array(start,alphabetsize+1);
	//incode
	s.writei32(alphabetsize);
	s.writei32array(incode,alphabetsize);
	
	//phi0
	Phi0->write(s);
	s.close();
	return 0;
}
void CSA::Load(loadkit &s)
{

	s.loadi32(this->n);
	s.loadi32(this->alphabetsize);
	
	s.loadi32(SL);
	s.loadi32(L);
	s.loadi32(D);
	s.loadi32(RD);

	SAL=new InArray();
	SAL->load(s);

	RankL=new InArray();
	RankL->load(s);
	
	//code
	i32 len=0;
	s.loadi32(len);
	this->code=new i32[len];
	s.loadi32array(this->code,len);
	//start
	s.loadi32(len);
	this->start=new i32[len];
	s.loadi32array(this->start,len);
	//incode
	s.loadi32(len);
	this->incode=new i32[len];
	s.loadi32array(this->incode,len);

	Phi0=new Phi();
	Phi0->load(s);
	s.close();
}
CSA::CSA(const char * sourcefile,i32 L,i32 D,i32 phitype)
{
	loadkit s(sourcefile);
	u64 magicnum;
	s.loadu64(magicnum);
	if(magicnum==198909102510)
	{
		Load(s);
	}
	else
	{
		s.close();
		this->phitype=phitype;
		this->SL=L*18;
		this->L =L;
		this->D =D;
		this->RD=D*16;
		this->code =new i32[256];
		for(i32 i=0;i<256;i++)
			code[i]=0;
	
		this->alphabetsize =0;
		Getfile(sourcefile);
		statics();
		this->SA=new i32[n];

		//TestTime::Start();
		ds_ssort(this->T,this->SA,this->n);
		CreateSupportStructer();
		//TestTime::End ();

		//	cout<<"Building time: "<<TestTime::TimeUsed_us()<<"us"<<endl;
		//cout<<"Creat SupportStructer is done   "<<TestTime::TimeUsed_us()<<endl;
		if(SA!=NULL)
			delete [] SA;
		if(T!=NULL)
			delete [] T;
		SA=NULL;
		T=NULL;
		cout<<"CSA  is done"<<endl;
	}
}
i32 CSA::GetN()
{
	return n;
}
i32 CSA::Getalphabetsize()
{
	return this->alphabetsize;
}
CSA::~CSA(void)
{
	delete SAL;
	delete RankL;
	delete [] start;
	delete Phi0;
	delete [] code;
	delete [] incode;
}

bool CSA::Existential(const char *Pattern) 
{
	i32 L=0;
	i32 R=0;
	Search2(Pattern,L,R);

	if(R>=L)
		return true;
	else
		return false;
}
void CSA::Counting(const char *Pattern,int &num) 
{
	i32 L=0;
	i32 R=0;

	Search2(Pattern,L,R);
	num=R-L+1;
}

void CSA::statics()
{
	for(i32 i=0;i<n;i++)
		code[T[i]]++;
	
	for(i32 i=0;i<256;i++)
		if(code[i]!=0)
			this->alphabetsize ++;
	this->start =new i32[this->alphabetsize +1];
	this->start [this->alphabetsize ]=n;
	this->start [0]=0;
	i32 k=1;
	i32 pre=0;
	for(i32 i=0;i<256;i++)
		if(code[i]!=0)
		{   
			start[k]=pre+code[i];
			pre=start[k];
			k++;
		}
	this->incode =new i32[this->alphabetsize];
	k=0;
	for(i32 i=0;i<256;i++)
		if(code[i]!=0)
		{
			code[i]=k;
			incode[k]=i;
			k++;
		}
		else
			code[i]=-1;
	lastchar=T[n-1];

}


void CSA::Getfile(const char * filename) 
{
	
	FILE *fp=fopen(filename,"r+");
	if(fp==NULL)
	{
		cout<<"Fopen error"<<endl;
		exit(0);
	}
    i32 currentfileposition = ftell(fp);  //获取读写指针当前位置。
	fseek(fp , 0, SEEK_END);       //置读写指针为文件末尾
    this->n = ftell(fp);                      //返回读写指针偏移量，单位字节，与上布配合求出文件数据的字节数。
	fseek(fp ,  currentfileposition, SEEK_SET); //重置读写指针为操作前的位置。
	int overshot=init_ds_ssort(500,2000);
	T=new unsigned char[n+overshot];
	fseek(fp , 0, SEEK_SET);

	i32 e=0;
	i32 num=0;
	while((e=fread(T+num,sizeof(uchar),n-num,fp))!=0)
		num=num+e;
	if(num!=n)
		exit(0);
	fclose(fp);
}
double CSA::Size()
{
	return (SAL->GetMemorySize ()+Phi0->Size()+RankL->GetMemorySize ())/(1.0*n);
}


void CSA::CreateSupportStructer() 
{
	i32 i=0;
	i32 j=0;
	i32 step1=D;
	i32 step2=RD;
	SAL=new InArray(n/step1+1,blog(n));
	RankL=new InArray(n/step2+1,blog(n));
	for(i=0,j=0;i<n;i=i+step1,j++)
	{
		SAL->SetValue (j,SA[i]);
	}
	
	for(i=0;i<n;i++)
	{
		if(SA[i]%step2==0)
			RankL->SetValue (SA[i]/step2,i);
	}
//	cout<<"SA sampling is done"<<endl;
	parmaters p={alphabetsize,n,SL,L,start,lastchar,SA,T,code,phitype};
	Phi0=new Phi(&p);
//	cout<<"Phi0 is done "<<endl;
	
	
}
void CSA::Search2(const char *Pattern, i32 &L, i32 &R)
{
	//cout<<"Search 2"<<endl;
	i32 len=strlen(Pattern);
	if(len==0)
	{
		L=1;
		R=0;
		return;
	}
	unsigned char c=Pattern[len-1];
	i32 coding=code[c];
	if(coding>alphabetsize-1||coding<0)
	{
		L=1;
		R=0;
		return ;
	}
	i32 Left=start[coding];
	i32 Right=start[coding+1]-1;
	i32 l0=0;
	i32 r0=0;
	//cout<<Left<<"  "<<Right<<endl;
	start[code[lastchar]]++;
	for(i32 i=len-2;i>=0;i--)
	{
		c=Pattern[i];
		coding=code[c];
		if(coding<0)
		{
			Left=1;
			Right=0;
			break;
		}
		l0=start[coding];
		//if(coding==code[lastchar])
		//	l0=l0+1;
		r0=start[coding+1]-1;
		Right=Phi0->RightBoundary(Right,l0,r0);
		Left=Phi0->LeftBoundary(Left,l0,r0);
		if(Left>Right)
		{
			Left=1;
			Right=0;
			break;
		}
		//cout<<Left<<"  "<<Right<<endl;
	}
	start[code[lastchar]]--;
	L=Left;
	R=Right;
	return ;


}
void CSA::Search(const char *Pattern, i32 &L, i32 &R) 
{
	//cout<<"Search 1"<<endl;
	i32 templeft;
	i32 tempright;
	i32 jj;
	i32 mleft;
	i32 mright;
	i32 middle;
	i32 Right;
	i32 left;
	i32 right;
	i32 Left;
	i32 i;
	i32 len=strlen(Pattern);
	unsigned char c=Pattern[len-1];
	i32 coding=code[c];
	if(coding>alphabetsize-1)
	{
		L=1;
		R=0;
		return ;
	}
	
	Left=start[coding];
	Right=start[coding+1]-1;//start数组的大小为alphabetsize+1，实际有用的为alphabetsize个，最后一个是为了防止coding+1越界的，
	                                     //所以start[alphabetsize]，即start数组的最后一个职位n。相见Phi0类的构造函数。
	for(i=len-2;i>=0;i--)
	{
		c=Pattern[i];
		coding =code[c];
		if(coding>alphabetsize-1)
		{
			L=1;
			R=0;
			return ;
		}
		left=start[coding];
		right=start[coding+1]-1;
		if(coding==code[lastchar])
			left=left+1;
		if(left>right || Phi0->GetValue (left)>Right || Phi0->GetValue (right)<Left)
		{
 			L=1;
			R=0;
			return ;
		}
		else
		{
			mleft=left;
			mright=right;
			while(mright-mleft>1)
			{
				middle=(mleft+mright)/2;
				jj=Phi0->GetValue (middle);
				if(jj<Left)
					mleft=middle;
				else
					mright=middle;
			}
			jj=Phi0->GetValue (mleft);
			if(jj>=Left && jj<=Right)
				templeft=mleft;
			else
				templeft=mright;
			mleft=left;
			mright=right;
			while(mright-mleft>1)
			{
				middle=(mleft+mright)/2;
				jj=Phi0->GetValue (middle);
				if(jj>Right)
					mright=middle;
				else
					mleft=middle;
			}
			jj=Phi0->GetValue (mright);
			if(jj>=Left && jj<=Right)
				tempright=mright;
			else
				tempright=mleft;
			Left=templeft;
			Right=tempright;
		    if(Left>Right)
			{
				L=1;
				R=0;
				return;
			}
		}
	}
	if(Left>Right)
		L=1,R=0;
	else
		L=Left,R=Right;
}
//phi0的实现和字典的rank操作的实现可以改进。
i32 CSA::lookup(i32 i) 
{   
	/*
	i32 step1=0;
	i32 step2=0;
	i32 r1=0;
	i32 r2=0;
	while(D0->GetOneBit (i)==0)
	{
		step1++;
		i=Phi0->GetValue (i);
	}
	r1=D0->Rank (i)-1;
	i=r1;
	while(Dm->GetOneBit (i)==0)
	{
		step2++;
		i=Phim->GetValue (i);
	}
	r2=Dm->Rank (i)-1;
	if(step1!=0 && step2==0 && SAL->GetValue (r2)==0)
		return n-step1;
	else if(step2!=0 &&SAL->GetValue (r2)==0)
		return n-(n-1-i32((n-1)/(1<<level1))*(1<<level1)+(step2-1)*(1<<level1)+step1+1);
	else

		return (SAL->GetValue (r2))*(1<<level2)-step2*(1<<level1)-step1;
		*/
	/*
	i32 r1=0;
	i32 step1=0;
	while(D0->GetOneBit(i)==0)
	{
		step1++;
		i=Phi0->GetValue (i);
	}
	r1=D0->Rank (i)-1;
	return ((SAL->GetValue (r1))*D-step1)%n;
	*/
	i32 D=this->D;
	i32 step=0;
	while(i%D!=0)
	{
		i=Phi0->GetValue(i);
		step++;
	}
	i=i/D;
	return (n+SAL->GetValue (i)-step)%n;
}
void CSA::SelfTesting() 
{
	cout<<"CSA is Selftesting..."<<endl;
	i32 k=0;
	i32 value=0;
	for(i32 i=0;i<n;i++)
	{
		value=lookup(i);
		if(SA[i]!=value)
			k++;
	}
	if(k!=0)

		cout<<"CSA is wrong     "<<k<<endl;
	else
		cout<<"CSA is right"<<endl;
}

i32 CSA::Inverse(i32 i)
{
	//i32 L2=(1<<level2);
	//i32 L1=(1<<level1);
	//i32 m=i/L2;
	//i32 k=i/L1;

	//p=Dm->Select (p+1);
//	i32 num=k-m*(L2/L1);
	//for(i32 j=0;j<num;j++)
	//	p=Phim->GetValue (p);

	/*
	i32 L1=D;
	i32 m=i/L1;
	i32 p=RankL->GetValue (m);
	p=D0->Select (p+1);
	i32 num=i%D;
	for(i32 j=0;j<num;j++)
		p=Phi0->GetValue (p);
	return p;
	*/
	i32 RD=this->RD ;
	i32 anchor=i/RD;
	i32 p=anchor*RD;
	i32 sa=this->RankL ->GetValue (anchor);
	while(p<i)
	{
		sa=Phi0->GetValue(sa);
		p++;
	}
	return sa;
}

void CSA::Decompress(i32 i, i32 len,unsigned char *p)
{
	i32 k=0;
	i=this->Inverse (i);
	for(i32 j=0;j<len;j++)
	{	
		k=this->Phi_list (i);
		p[j]=this->Character (k);
		i=Phi0->GetValue (i);
	}
}

i32 CSA::Phi_list(i32 i)
{
	i32 l=0;
	i32 r=this->alphabetsize ;
	i32 m=0;
	while(l<r)
	{
		m=(l+r)/2;
		if(start[m]<=i)
			l=m+1;
		else
			r=m;
	}
	return r-1;
}
i32 CSA::Character(i32 i)
{
	return incode[i];
}


i32 CSA::blog(i32 x)
{
	i32 ans=0;
	while(x>0)
	{
		ans++;
		x=x>>1;
	}
	return ans;
}
void CSA::Locating(const char *Pattern, i32 &num, i32 *&pos)
{
	i32 L=0;
	i32 R=0;
	this->Search2(Pattern,L,R);
	num=R-L+1;
	if(L>R)
		return ;
	pos=new i32[num];
//	if(num>50)
		Enumerative2(L,R,pos);
//	else
//		Enumerative1(L,R,pos);

	
}

void CSA::Enumerative2(i32 L,i32  R, i32 *&pos)
{
	i32 D=this->D;
	InArray *SAL=this->SAL ;
	i32 * distance=new i32[R-L+1];
	i32 *pred=new i32[R-L+1];
	i32 f=0;
	i32 step=0;
	i32 q=0;
	i32 s=0;
	i32 i=0;
	for(i32 i=0;i<R-L+1;i++)
	{
		pos[i]=0;
		pred[i]=-1;
	}
	for(i32 j=L;j<=R;j++)
	{
		f=0;
		i=j;
		step=0;
		while(i%D!=0)
		{
			i=this->Phi0->GetValue(i);
			step++;
			if(L<=i&&i<=R)
			{
				distance[j-L]=step;
				pred[i-L]=j;
				f=1;
				break;
			}
		}
		if(f==0)
		{
			i=i/D;
			pos[j-L]=SAL->GetValue(i)-step;
		}
	}
	i32 fu=0;
	for(i32 j=L;j<=R;j++)
	{
		if(pos[j-L]!=0)
		{
			q=j;
			while(pred[q-L]!=-1)
			{
				fu++;
				s=pos[q-L];
				i=pred[q-L];
				step=distance[i-L];
				pos[i-L]=s-step;
				pred[q-L]=-1;
				q=i;
			}
		}
	}
	//cout<<"fuck"<<fu<<endl;
	delete [] pred;
	delete [] distance;
}
void CSA::Enumerative1(i32 L,i32 R,i32 *&pos) 
{


	i32 i;
	for(i=L;i<=R;i++)
	{
		pos[i-L]=lookup (i);
	}

}
