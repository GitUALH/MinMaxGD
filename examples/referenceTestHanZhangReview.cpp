
#include<exception>
#include<chrono>


#ifndef _WIN32
#include "../include/lminmaxgd.h"
#include "../src/gd.cpp"
#include "../src/poly.cpp"
#include "../src/serie.cpp"
#include "../src/smatrix.cpp"
#include "../src/tools.cpp"
#else
#include "..\include\lminmaxgd.h"
#include "..\src\gd.cpp"
#include "..\src\poly.cpp"
#include "..\src\serie.cpp"
#include "..\src\smatrix.cpp"
#include "..\src\tools.cpp"
using namespace std;
/////////////////////////////////////////////////////////////////////
using namespace mmgd;
#endif

void iteration();
smatrix Phi(smatrix  H, serie P, serie beta,serie xA,smatrix Pt,smatrix u,serie xR);
int main()
{
	iteration();
}



//Optimal input of tracking the given reference output signal
void iteration()
{
	//the first subsystem
	smatrix A1(4, 4), B1(4, 1), C1(1, 4);
	A1(0, 1) = gd(2, 3);
	A1(1, 0) = gd(0, 5);
	A1(2, 1) = gd(0, 1);
	A1(2, 3) = gd(1, 1);
	A1(3, 2) = gd(0, 3);

	B1(0, 0) = gd(0, 0);
	C1(0, 3) = gd(0, 0);

    smatrix A1S= star(A1);


	smatrix H1 = otimes(A1S, B1);
	cout << "input-state transfer matrix for the subsystem 1:" << endl;
	cout << "H1= " << H1 << endl;

  smatrix G1 = otimes(C1,H1);
	cout << "input-output transfer matrix for the subsystem 1:" << endl;
	cout << "G1= " << G1 << endl;

	//the given reference output z1
	smatrix z1(1,1);
	gd m,r;
    poly p;

	z1(0,0).init(epsilon,m.init(0,9),r.init(1,14));
    cout<<" z1 "<<z1<<endl;getchar();

	smatrix uopt1 = lfrac(z1,G1);
	cout << "the optimal control input of subsystem 1:" << endl;
	cout << "uopt1= " << uopt1 << endl;


	smatrix X1(4, 1);

    X1=otimes(H1,uopt1);

	smatrix y1 = otimes( G1,uopt1);
	cout << "the output of the subsystem 1 with optimal inputs:" << endl;
	cout << "y1= " << y1 << endl;


	//the second subsystem
	smatrix A2(4, 4), B2(4, 1), C2(1, 4);
	A2(0, 1) = gd(2, 3);
	A2(1, 0) = gd(0, 7);
	A2(2, 1) = gd(0, 2);
	A2(2, 3) = gd(1, 1);
	A2(3, 2) = gd(0, 4);

	B2(0, 0) = gd(0, 0);
	C2(0, 3) = gd(0, 0);

    smatrix A2S=star(A2);
    smatrix A2B=otimes(A2S,B2);
	smatrix G2 = otimes(C2, A2S);
	cout << "input-output transfer matrix for the subsystem 2:" << endl;
	cout << "G2= " << G2 << endl;


	smatrix H2 = A2B;
	cout << "input-state transfer matrix for the subsystem 2:" << endl;
	cout << "H2= " << H2 << endl;
cout << "G1(0,0) " <<G1(0,0) << endl;getchar();
cout << "G2(0,0) " <<G2(0,0) << endl;getchar();



	//the given reference output z2
	smatrix z2;

    z2(0,0).init(epsilon,m.init(0,15),r.init(1,8));

    cout << "z2 :" <<z2 << endl;
    getchar();
	smatrix ustar = lfrac(z2,G2);
	cout << "the optimal input of subsystem 2 without shared resources " << endl;
	cout << "ustar=" << ustar << endl;
    smatrix X2(4, 1);
	X2=otimes(H2,ustar);

	smatrix y2 = otimes( G2,ustar);
	cout << "the state of the subsystem 2 without shared resources :" << endl;
	cout << "X2= " << X2 << endl;

	//the shared resources
	smatrix beta1;
	beta1(0,0)= gd(2, 3);
	smatrix  beta2;
	beta2(0,0) = gd(1, 1);



	//// Definition in an standard way of the system

	serie P11, H11, P12, H12, P13;
	P11=gd(0,0);
	H11=gd(0,5);
	P12=gd(0,1);
	H12=gd(0,3);
	P13=gd(0,0);
	serie xA11,xR11,xA12,xR12;

	xA11=X1(0,0);
	xR11=X1(1,0);
	xA12=X1(2,0);
	xR12=X1(3,0);

	smatrix u1(3,1);
	u1(0,0)=uopt1(0,0);
	u1(1,0)=X1(0,0);
	u1(2,0)=X1(2,0);

	serie P21, H21, P22, H22, P23;
	P21=gd(0,0);
	H21=gd(0,7);
	//H21.init(epsilon,m.init(0,7),r.init(2,10));
	P22=gd(0,2);
	H22=gd(0,4 );
	//H22.init(epsilon,m.init(0,4),r.init(1,5));
	P23=gd(0,0);

	smatrix Pt21(1,3),Pt22(1,3);
	Pt21(0,0)=P21;
	Pt21(0,1)=gd(0,0);

	Pt22(0,0)=otimes(H21,P21);
	Pt22(0,0)=otimes( P22,Pt22(0,0));
	Pt22(0,1)=otimes(P22,H21);
	Pt22(0,2)=gd(0,0);

	smatrix u2(3,1);
	u2(0,0)=ustar(0,0);
	u2(1,0)=X2(0,0);
	u2(2,0)=X2(2,0);

cout << "u2 without resource sharing " << u2 << endl;





//iteration - calculate the greatest fixed point

	unsigned int iteration = 0;
	smatrix Phi21,Phi22;
	smatrix u2init(3,1); // to memorize initial value
   smatrix u2opt(3,1);
	u2opt=u2;
	u2init=u2opt;
cout << "Subsystem " << (2) << ", Iteration " << ++iteration << ": " << u2opt << endl;

   do {
   u2=u2opt;
   Phi21=Phi(H21,P21,beta1(0,0),xA11,Pt21,u2,xR11);
   u2opt=inf(Phi21,u2);
   Phi22=Phi(H22,P22,beta2(0,0),xA12,Pt22,u2,xR12);

   u2opt=inf(Phi22,u2opt);

   u2opt=inf(u2opt,u2);
   X2=otimes(Pt22,u2opt);
   X1=otimes(Pt21,u2opt);
   cout << "Subsystem " << (2) << ", Iteration " << ++iteration << ": " << u2opt(0,0) << endl;
   cout<<" u2opt "<<u2opt<<endl;
   cout<<" X1 "<<X1<<endl;
   cout<<" X2 "<<X2<<endl;
		getchar();
	}while(!(u2opt==u2));




}

smatrix Phi(smatrix H, serie P, serie beta,serie xA,smatrix Pt,smatrix u,serie xR)
{
    smatrix Ptu=otimes(Pt,u);
    smatrix HP=otimes(H,Pt);
    serie temp,temp1,temp2,temp3;
    gd r;
    smatrix result;

     cout<<"u "<<u<<endl;
     cout<<"Ptu "<<Ptu<<endl;
     cout<<"HPt "<<HP<<endl;
     cout<<"xA "<<xA<<endl;

    temp=hadamard_prod(xA,Ptu(0,0));
     cout<<" xA + Pt u \n"<<temp<<endl;
    temp=frac(temp,beta);
    cout<<" beta \\ xA + Pt u \n"<<temp<<endl;
    cout<<" xR "<<xR<<endl;
     temp=hadamard_res(temp, xR);
    temp3=temp;
   // temp3.init(temp.getp(),temp.getq(), r.init(0,infinit));

    smatrix num=temp3;
    cout<<"  beta \\xA + Pt u - xR \n"<<num<<endl;
   result=lfrac(num,HP);
   cout<<"  HP \\ beta \\xA + Pt u - xR \n"<<result<<endl;

   smatrix HPU=otimes(HP,result);
   cout<<" (HPt ) \n" <<HPU;
   temp1=hadamard_prod(xR,HPU(0,0));
   temp1=otimes(beta,temp1);
   cout<<" beta (HPt u odot xR)\n" <<temp1<<endl;
   Ptu=otimes(Pt,u);
   temp2=hadamard_prod(xA,Ptu(0,0));
    cout<<" Pt u odot xA \n" <<temp2<<endl;
     return result;

}
