#include<iostream>
#include<graphics.h>
#include<cmath>

using namespace std;

class transform
{      int tx,ty,sx,sy;
	float deg,theta,b[20][20];
	public:
		int n,a[20][20],c[20][20];
		int i,j,k;
		void object(), getdata(),translate(), rotate(), scale();
			     
		void operator *(float b[20][20])
		{
			for(int i=0;i<n;i++)
			{
				for(int j=0;j<n;j++)
				{
					c[i][j]=0;
					for(int k=0;k<n;k++)
					{
						c[i][j]=c[i][j]+(a[i][k]*b[k][j]);
					}
				}
			}
		}
};   transform t;

void transform::object()
{
	 int gd=DETECT,gm;
	 initgraph(&gd,&gm,NULL); 
	//initwindow(1366,768);
   line(300,0,300,600);
   line(0,300,600,300);
    for( i=0;i<n-1;i++)
    	{
    		line(300+a[i][0],300-a[i][1],300+a[i+1][0],300-a[i+1][1]);
    	}
	//line(300+a[0][0],300-a[0][1],300+a[i][0],300-a[i][1]);
    for( i=0;i<n-1;i++)
	{
		line(300+c[i][0],300-c[i][1],300+c[i+1][0],300-c[i+1][1]);
	}
	//line(300+c[0][0],300-c[0][1],300+c[i][0],300-c[i][1]);
}
	
void transform::getdata()
{	
    cout<<"\nEnter the nos. Of edges in your shape:";
    cin>>n;
    cout<<"\nEnter The Coordinates :";
    for(int i=0;i<n;i++)
    {
    	for(int j=0;j<3;j++)
    	{   	int k=1+i;
    		if(j>=2)
    		 {a[i][j]=1;}
    		else
    		{cout<<"\nVertex "<<k<<": ";
    		cin>>a[i][j];}
		}
	}
}
void transform::translate()
{
cout<<"\n*TRANSLATION*\n";
		    cout<<"Enter value for tx and ty:";
		    cin>>tx>>ty;
		    b[0][0]=b[2][2]=b[1][1]=1;
			b[0][1]=b[0][2]=b[1][0]=b[1][2]=0;
			b[2][0]=tx;
			b[2][1]=ty;
			t * b;
			t.object();
}

void transform::scale()
{
cout<<"\n*SCALING*\n";
		    cout<<"Enter value for sx,sy:";
		    cin>>sx>>sy;
		    b[0][0]=sx;
		    b[1][1]=sy;
		    b[0][1]=b[0][2]=b[1][0]=b[1][2]=0;
		    b[2][0]=b[2][1]=0;
			b[2][2] = 1;
			t * b;
			t.object();
}

void transform::rotate()
{
cout<<"\n*ROTATION*\n";
		    cout<<"Enter value for angle:";
		    cin>>deg;
			theta=deg*(3.14/180);
			b[0][0]=b[1][1]=cos(theta);
			b[0][1]=sin(theta);
			b[1][0]=sin(-theta);
			b[0][2]=b[1][2]=b[2][0]=b[2][1]=0;
			b[2][2]=1;
			t * b;
			t.object();
}

int main()
{      
	int ch;
	t.getdata();
	    here:                                                               //if error is detected, goto here
	    cout<<"\nEnter your choice\n1.Translation\n2.Rotation\n3.Scaling\n";
	    cin>>ch;
	    if(ch==1)
	    {t.translate();goto here;}
	    if(ch==2)
	    {t.rotate();goto here;}
	    if(ch==3)
	    {t.scale();goto here;}
	    if(ch!=1 && ch!= 2 && ch!=3) 
	    { cout<<"Enter the options 1-3 only."; 
	      goto here;
	    }
	
   getch();
   return 0;    
}
