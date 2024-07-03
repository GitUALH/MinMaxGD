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
/* all the libray is compiled, you can create a library */
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

/**************************************************************************************/
/* this example present the main function of the library
   and the different manner to declare monomial polynom serie and matrix */
/**************************************************************************************/
using namespace mmgd;

int main(void)
{
try{
 smatrix a(7,7);
 smatrix as(7,7), b(7,1), c(1,7), asb(7,1), h(1,1), cas(1,7);

  a(1,0) = gd(0,2);
  a(1,2) = gd(1,1);
  a(2,1) = gd(0,3);
  a(3,0) = gd(0,2);
  a(3,4) = gd(2,1);
  a(4,3) = gd(0,1);
  a(5,2) = gd(0,1);
  a(5,6) = gd(1,2);
  a(6,2) =e;
  a(6,4) = gd(1,1);
  a(6,5) = gd(1,8);

  b(0,0) = e;
  c(0,6) = e;


  as = star(a);
  asb = otimes(as,b);
  h = otimes(c,asb);
  cas = otimes(c,as);


cout<<"Initial state-matrix: A"<<a<<endl;

cout<<"Initial transfer function matrix: H"<<h<<endl;

 smatrix aM(7,7), aopt(7,7), aopts(7,7), caopts(1,7), hopt(1,1);

 aM = lfrac(cas,cas);
 aopt = prga(a,aM);
 aopts = star(aopt);
 caopts = otimes (c,aopts);
 hopt = otimes(caopts,b);

 cout<<"Modified state-matrix: Aopts"<<aopts<<endl;
 cout<<"CAS\\CAS "<<aM<<endl;

 cout<<"Modified transfer function matrix: Hopt = CAopt*B"<<hopt<<endl;

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
