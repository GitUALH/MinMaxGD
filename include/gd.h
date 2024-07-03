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
#ifndef __GD_H__
#define __GD_H__

#include "tools.h"
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <iostream>
//#include<climits>


namespace mmgd
{
	/*****************************************************************************************/
	/********* Classe pour exception  ******************************************************************/
	/*****************************************************************************************/
	class mem_limite
	{
	public:
		int memoire;
		mem_limite(int i)
		{
			memoire = i;
		}

	};
	class taille_incorrecte
	{
	public:
		int erreur;
		taille_incorrecte(int i)
		{
			erreur = i;
		}

	};


#define infinit 2147483647
#define _infinit -2147483647

	/*****************************************************************************************/
	//******* Classe gd definissant un monome        *********************************************//
	/*****************************************************************************************/

	class gd {
	protected:  long g;
			  long d;
			  void affecte(long, long);

	public:   gd(void);   // constructuer 0 : (g,d)=(+00,-00)
			  gd(const gd&);    // constructeur 1 : par recopie
			  gd(long, long); // constructeur 2 : initialise avec 2 entiers

			   // surdefinition de l'operateur egal
			  gd& operator=(const gd &); // initialise avec un objet gd ,
			  int operator!=(const gd &); // comparaison d'un monome avec le monome courant
			  int operator==(const gd &); // comparaison d'un monome avec le monome courant
			  int operator>=(const gd &); // comparaison d'un monome avec le monome courant
			  int operator<=(const gd &); // comparaison d'un monome avec le monome courant
			  bool operator<(const gd &) const; // comparaison d'un monome avec le monome courant

			  gd& init(long, long); // initialise avec un tableau de 2 entiers
			  gd& operator ()(long, long); // initialise avec un tableau de 2 entiers
	 // void identifie();
			  friend std::ostream& operator<<(std::ostream&, gd&); //redefinition de l'operateur <<
			  friend std::fstream& operator<<(std::fstream&, gd&); //redefinition de l'operateur << pour fichier

			  long getg(void) { return g; }     // retourne g
			  long getd(void) { return d; }    // retourne d pour acces de l'exterieur

			  friend gd inf(const gd &gd1, const gd &gd2);
			  // inf de 2 monomes, en entree 2 monomes par reference
			  // la fonction retourne
			  // un monome pour permettre un appel successif

			  friend gd otimes(const gd &gd1, const  gd &gd2);
			  // produit de 2 monomes, on traite les cas degeneres
			  // en entree 2 monomes par reference
			  // la fonction retourne
			  // un monome pour permettre un appel successif

			  friend gd frac(const gd & gd1, const  gd &gd2);
			  // residuation de 2 monomes
			  // en entree 2 monomes par reference
			 // la fonction retourne
			 // un monome pour permettre un appel successif

			  friend gd Dualfrac(const gd & gd1, const gd &gd2);


			  // Append from 17/04/2015 for Soraia
			  friend gd  odot(const gd &gd1, const gd &gd2);
			  // produit d'hadamard de 2 monomes, on traite les cas degeneres
			  // en entree 2 monomes par reference
			  // la fonction retourne
			  // un monome  pour permettre un appel successif

			  friend gd  fracodotsharp(const gd &gd1, const gd &gd2);
			  // residue d'hadamard de 2 monomes,  gd1-gd2
			  // on traite les cas degeneres
			  // en entree 2 monomes par reference
			  // la fonction retourne
			  // un monome  pour permettre un appel successif

			  friend gd  fracodotflat(const gd &gd1, const gd &gd2);
			  // residue d'hadamard (flat=bemol) de 2 monomes, gd1-gd2, i.e. odot(gd2,temp) >= gd1
			  //	on traite les cas degeneres
			  // en entree 2 monomes par reference
			  // la fonction retourne
			  // un monome  pour permettre un appel successif


	}; // fin de la definition de class gd



} // fin de namespace mmgd
#endif

