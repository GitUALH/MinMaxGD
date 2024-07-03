/**
MINMAXGD
Copyright (C) {{ 2007 }}  {{ Univeristy of Angers, L. Hardouin }}

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
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
#endif
/////////////////////////////////////////////////////////////////////
/* Example : HOW to define a trajectory an compute the optimal control
// you must link with a library which contains all source files given in folder src
// gd.cpp poly.cpp serie.cpp smatrix.cpp tools.cpp interf.cpp
// or add these files in your project
// or alternatively you can include the following files
//
*/


/////////////////////////////////////////////////////////////////////
using namespace mmgd;

int main()
{
try
{

	smatrix A(1,1);	// state Matrix
	smatrix H(1,1); // input/output transfer CA*B

	smatrix CA(1,1); // observability matrix
    smatrix AB(1,1); // controllability matrix

	A(0,0)=gd(3,15);//(1,2)

	smatrix B(1,1),C(1,1);	// Input and output matrices

	C(0,0)=gd(0,0);

	B(0,0)=gd(0,15);


	smatrix As=star(A);
	CA=otimes(C,As);  // CA* observability matrix
    cout << "CA* :" << CA << endl;
    AB=otimes(As,B); // controllability matrix
    cout << "A*B :" << AB << endl;
	H=otimes(CA,B); // input/output transfer CA*B
	cout << "H :" << H << endl;

	smatrix u;
	smatrix z(1,1);
	poly p;
	gd m;
	p.init(0,20)(3,22)(5,32)(6,infinit); //at least 3 part at time 20, 5 parts at time 22, 6 parts at time 32, 7 never

	z(0,0).init(epsilon,p,m.init(0,0));

    u=lfrac(z,H); // Optimal input

    cout<<"z"<<z<<endl; // Reference output, trajectory to track
    cout<<"u"<<u<<endl; // Optimal input







	smatrix x;
	smatrix y;



    y=otimes(H,u);

    x=otimes(AB,u); // optimal state
    y=otimes(C,x);  // optimal output

    cout<<"xopt"<<x<<endl;
    cout<<"yopt"<<y<<endl;

	return(0);
}

 catch(mem_limite l)
 {
	 cout<<"Exception : too many coefficent in polynom "<<l.memoire<<endl;
	 return(1);
 }

 catch(taille_incorrecte obj)
 { // 0 : r non causal
   // 1 : tentative d'accès à un element d'une matrice avec un indice incorrect
   // 2 : matrice de taille incompatible pour oplus, inf, otimes, rfrac, lfrac
   // 3 : etoile de matrice carré uniquement
	 cout<<"Exception  "<<obj.erreur<<endl;
	 return(1);
 }
}
