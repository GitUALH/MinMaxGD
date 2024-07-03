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
#ifndef MATRIXCOO_H
#define MATRIXCOO_H

#include "serie.h"

namespace mmgd
{

	/*************************************************************************************/
	/*************************************************************************************/
	typedef struct
	{
		int i;
		int j;
		serie s;
	} Ttriplet;
	class matrixCOO {
	private:
		int col, row;
		unsigned int size;
		int capacity;

		Ttriplet * Data;

		void affecte(matrixCOO &list);

	public:
		matrixCOO(void);
		matrixCOO(int, int);// constructeur 0 : matrice = epsilon + epsilon.(e)*
		matrixCOO(const matrixCOO &);// constructuer 1 : matrice initialisee avec un objet matrice

		matrixCOO(const serie &);// constructuer 2 : matrice initialisee avec un objet serie
		matrixCOO(poly &);// constructuer 3 : matrice initialisee avec un objet poly
		matrixCOO(gd &);// constructuer 4 : matrice initialisee avec un objet monome


		~matrixCOO(void); // destructeur

		int  getrow(void) { return row; }
		int getcol(void) { return col; }
		int getsize(void) { return size; }
		int find(int, int);
		int geti(int);
		int getj(int);
		int  getcapacity();
		void pushback(Ttriplet &);
		int  comp(int, int, int, int);



		matrixCOO&  operator =(const matrixCOO& a); //surdefinition du =, permet d'initialiser avec une autre matrice

		matrixCOO&  operator =(smatrix& a);

		matrixCOO&  operator =(serie& a); //surdefinition du =, permet d'initialiser avec une serie cast serei matrice
		matrixCOO& operator =(gd& gd1);	  // initialise avec un monome cast monome->matrice
		matrixCOO& operator =(poly& p1);	  // initialise avec un polynome cast polynome->matrice

		serie& operator()(int i, int j);


		int operator==(const matrixCOO & M); // surdefiniton de l'�alit�de matrice
		int operator!=(const matrixCOO & M); // surdefiniton de l'�alit�de matrice

		friend std::ostream &  operator<<(std::ostream &flot, matrixCOO &);//surdef. de <<
		friend std::fstream &  operator<<(std::fstream &flot, matrixCOO &); // surdef de >> pour fichier

		friend matrixCOO oplus(matrixCOO&, matrixCOO&); //somme de 2 matrices de series p�iodiques


		friend matrixCOO transpose(matrixCOO& a);

		friend matrixCOO inf(matrixCOO& a, matrixCOO& b); // inf de 2 matrices de s�ies p�iodiques

		friend matrixCOO otimes(matrixCOO&, matrixCOO&); //produit de 2 matrices de series p�iodiques

		friend matrixCOO lfrac(matrixCOO&, matrixCOO&); //residuation a gauche de 2 matrices de series p�iodiques b\a

		friend matrixCOO rfrac(matrixCOO& a, matrixCOO& b);  // residuation �droite de 2 matrices de series p�iodiques a/b

		friend matrixCOO star(matrixCOO ak_1);

		friend matrixCOO prcaus(matrixCOO &);

		friend int compare_multi(int a, int b);



	};

}
#endif // matrixCOO_H
