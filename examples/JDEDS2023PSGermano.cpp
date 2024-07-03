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
	double min(double a,double b)
{
		if(a>b) return b;
		else return a;
}
#include "..\include\lminmaxgd.h"
#include "..\src\gd.cpp"
#include "..\src\poly.cpp"
#include "..\src\serie.cpp"
#include "..\src\smatrix.cpp"
#include "..\src\tools.cpp"
using namespace std;
#endif

/////////////////////////////////////////////////////////////////////
/* Example :  Hardouin L., Cottenceau B., Lagrange S., Le Corronc E.

Performance analysis of linear systems over idempotent semiring with additive inputs
Wodes 2008, Goteborg, Sweden
	*/
/////////////////////////////////////////////////////////////////////
using namespace mmgd;

int main()
{
	smatrix A(3,3);
	smatrix AS;
	smatrix B(3,2);
	smatrix C(1,3);
	smatrix AB(3,2);
	smatrix CAB(1,2);
smatrix F2(1,2);
		poly pho;
		poly z;
		serie alpha;
		smatrix Z;
		smatrix uopt;
		smatrix yopt;
	serie CABpoly;

	serie beta1,beta2,beta3;
	serie Alpha1,Alpha2,Alpha3;
	serie Alpha11,Alpha12,Alpha13,Alpha14;
	serie Alpha11bis,Alpha12bis,Alpha13bis,Alpha14bis;
	serie OutAlpha2,OutAlpha3,OutAlpha1,OutAlpha4;
	serie u1,u2,u3;
	serie y1,y2,y3;
	serie y1bis,y2bis,y3bis;
	serie u1bis,u2bis,u3bis;
	serie bb1,bb2,bb3;
	poly epoly;

	poly  pAlpha2,pAlpha3,pAlpha1,pAlpha4;
	poly p1;
	poly p2;
	poly p;

	gd a;
	gd m;
	gd r;


	// System of figure 1, Wodes 2008 About maximal flow for linear systems over semiring

	A(0,1).init(epsilon,m.init(2,1),e);
	A(1,0).init(epsilon,m.init(0,3),e);
   	A(1,2).init(epsilon,m.init(1,2),e);
	A(2,1).init(epsilon,m.init(0,4),e);

	B(0,0).init(epsilon,m.init(0,0),e);
	B(1,1).init(epsilon,m.init(0,0),e);
	C(0,2).init(epsilon,m.init(0,0),e);


	AS=star(A);

	AB=otimes(AS,B);
	CAB=otimes(C,AB);
	std::cout << " A :" << std::endl << A<< std::endl;
	std::cout << " AS :" << std::endl << AS<< std::endl;
	std::cout << " AB :" << std::endl << AB<< std::endl;
    std::cout << " CAB :" << std::endl << CAB<< std::endl;

    pho.init(0,3)(1,4)(2,5)(3,9)(4,10)(5,11)(6,17)(7,18)(8,23)(9,24)(10,25)(11,26)(12,30)(13,31)(14,infinit);
        std::cout << " pho :" << std::endl << pho<< std::endl;
   // RHO(0,0).init(epsilon,pho,e);
    pho=otimes(m.init(0,1),pho);
        std::cout << " alpha :" << std::endl << pho<< std::endl;
   // ALPHA=


    z.init(0,14)(1,23)(3,29)(4,infinit);
    Z(0,0).init(epsilon,z,e);
     std::cout << " Z :" << std::endl << Z<< std::endl;
	// system of figure 5, Wodes 2008 About maximal flow for linear systems over semiring

	uopt=lfrac(Z,CAB);
     std::cout << " uopt :" << std::endl << uopt<< std::endl;

    yopt=otimes(CAB,uopt);
     std::cout << " yopt :" << std::endl << yopt<< std::endl;

    F2(0,0)=CAB(0,0);
    F2(0,1)=CAB(0,1);









}

