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
#include "../include/gd.h"
#else
#include "..\include\gd.h"
#endif
/*****************************************************************************************/
//******* Classe gd definissant un monome        *********************************************//
/*****************************************************************************************/

namespace mmgd
{

	void gd::affecte(long g1, long d1)
	{
		g = g1;
		d = d1;
	}

	gd::gd(void)  // constructuer 0 : (g,d)=(+00,-00)
	{
		g = infinit;
		d = -infinit;
	}

	gd::gd(const gd & gd1)    // constructeur 1 : par recopie
	{
		affecte(gd1.g, gd1.d);
	}

	gd::gd(long g1, long d1) // constructeur 2 : initialise avec 2 entiers
	{
		affecte(g1, d1);
	}


	gd& gd :: operator=(const gd & gd1)    // initialisation : par recopie
	{
		if (&gd1 != this) affecte(gd1.g, gd1.d);// ne rien faire si c'est le meme objet
		return *this;
	}                   // retourne l'objet courant pour permettre
													   // une affectation successive
	int gd :: operator!=(const gd &gd1) // comparaison d'un monome avec le monome courant
	{
		if (gd1.g == g)
			if (gd1.d == d) return(0);
		return(1);
	}
	int gd :: operator==(const gd &gd1) // comparaison d'un monome avec le monome courant
	{
		if (gd1.g == g)
			if (gd1.d == d) return(1);
		return(0);
	}

	int gd :: operator>=(const gd &gd1) // comparaison d'un monome avec le monome courant
	{
		if (g <= gd1.g)
			if (d >= gd1.d) return(1);
		return(0);
	}



	int gd :: operator<=(const gd &gd1)  // comparaison d'un monome avec le monome courant
	{
		if (g >= gd1.g)
			if (d <= gd1.d) return(1);
		return(0);
	}


	bool gd :: operator<(const gd &gd1) const // comparaison d'un monome avec le monome courant
	{
		if (g < gd1.g) return(true);
		if (g == gd1.g)
			if (d > gd1.d) return(true);

		/*if (g==gd1.g)
					  if (d<gd1.d) return(1);*/
		return(false);
	}


	gd& gd::init(long g1, long d1) //  initialise avec 2  entiers
	{
		affecte(g1, d1);                        // affectation
		return *this;
	}                        // retourne l'objet courant

	gd& gd :: operator ()(long g1, long d1) // initialise avec un tableau de 2 entiers
	{
		affecte(g1, d1);                        // affectation
		return *this;
	}                        // retourne l'objet courant


	gd inf(const gd &gd1, const gd &gd2)
		// inf de 2 monomes, en entree 2 monomes par reference
		// la fonction retourne
		// un monome pour permettre un appel successif
	{
		gd gdtemp(gd1);
		if (gd2.g > gd1.g) gdtemp.g = gd2.g;
		if (gd2.d < gd1.d) gdtemp.d = gd2.d;

		return(gdtemp);
	}


	gd  otimes(const gd &gd1, const gd &gd2)
		// produit de 2 monomes, on traite les cas degeneres
		// en entree 2 monomes par reference
		// la fonction retourne
		// un monome  pour permettre un appel successif
	{
		gd temp;
		if (gd1.g == infinit || gd2.g == infinit) temp.g = infinit;
		else if (gd1.g == _infinit || gd2.g == _infinit)
			temp.g = _infinit;
		else temp.g = gd1.g + gd2.g;
		if (gd1.d == _infinit || gd2.d == _infinit) temp.d = _infinit;
		else  if (gd1.d == infinit || gd2.d == infinit) temp.d = infinit;
		else temp.d = gd1.d + gd2.d;
		return(temp);
	}


	gd frac(const gd & gd1, const gd &gd2)
		// residuation de 2 monomes
		// en entree 2 monomes par reference
		// la fonction retourne
		// un monome pour permettre un appel successif

	{
		gd temp;
		switch (gd1.g)
		{
		case _infinit: temp.g = _infinit;
			break;
		case infinit:  if (gd2.g == infinit) temp.g = _infinit;
					   else temp.g = infinit;
			break;
		default: switch (gd2.g)
		{
		case infinit: temp.g = _infinit;
			break;
		case _infinit: temp.g = infinit;
			break;
		default:  temp.g = gd1.g - gd2.g;
		}

		}
		switch (gd1.d)
		{
		case infinit: temp.d = infinit;
			break;
		case _infinit:  if (gd2.d == _infinit) temp.d = infinit;
						else temp.d = _infinit;
			break;
		default:                         switch (gd2.d)
		{
		case _infinit: temp.d = infinit;
			break;
		case infinit: temp.d = -infinit;
			break;
		default:  temp.d = gd1.d - gd2.d;
		}
		}
		return(temp);
	}
	gd Dualfrac(const gd & gd1, const gd &gd2)
		// residuation de 2 monomes
		// en entree 2 monomes par reference
		// la fonction retourne
		// un monome pour permettre un appel successif

	{
		gd temp;
		switch (gd1.g)
		{
		case infinit: temp.g = infinit;
			break;
		case _infinit:  if (gd2.g == _infinit) temp.g = infinit;
						else temp.g = _infinit;
			break;
		default: switch (gd2.g)
		{
		case _infinit: temp.g = infinit;
			break;
		case infinit: temp.g = _infinit;
			break;
		default:  temp.g = gd1.g - gd2.g;
		}

		}
		switch (gd1.d)
		{
		case _infinit: temp.d = _infinit;
			break;
		case infinit:  if (gd2.d == infinit) temp.d = _infinit;
					   else temp.d = infinit;
			break;
		default:                         switch (gd2.d)
		{
		case infinit: temp.d = _infinit;
			break;
		case _infinit: temp.d = infinit;
			break;
		default:  temp.d = gd1.d - gd2.d;
		}
		}
		return(temp);
	}
	/*** fonction exterieur*/
	std::ostream& operator<<(std::ostream &flot, gd &gd1)
		// affiche le monome courant, redefinition de l'operateur <<
	{
		flot << " g^" << gd1.getg() << " d^" << gd1.getd();
		return flot;
	}



	std::fstream& operator<<(std::fstream &flot, gd &gd1)
		// affiche le monome courant, redefinition de l'operateur <<
	{
		flot << " g^" << gd1.getg() << " d^" << gd1.getd();
		return flot;
	}

	////// Below Append from 17/04/2015, Hdamard product residuation of the hadamard product and dual residuation  of the hadamard product
	gd   odot(const gd &gd1, const gd &gd2)
		// produit d'hadamard de 2 monomes, on traite les cas degeneres
		// en entree 2 monomes par reference
		// la fonction retourne
		// un monome  pour permettre un appel successif
	{
		gd temp;

		if (gd1.d < gd2.d) temp.d = gd1.d;
		else temp.d = gd2.d;

		if (gd1.g == infinit || gd2.g == infinit) { temp.g = infinit;  return(temp); }
		if (gd1.g == _infinit && gd2.g != infinit) { temp.g = _infinit; return(temp); }
		if (gd2.g == _infinit && gd1.g != infinit) { temp.g = _infinit; return(temp); }
		temp.g = gd1.g + gd2.g;

		return(temp);

	}


	gd  fracodotsharp(const gd &gd1, const gd &gd2)

		// residue d'hadamard (sharp=diese) de 2 monomes, gd1-gd2, i.e. odot(gd2,temp) <= gd1
		//	on traite les cas degeneres
		// en entree 2 monomes par reference
		// la fonction retourne
		// un monome  pour permettre un appel successif
	{
		gd temp;

		if (gd1.d >= gd2.d) temp.d = infinit;
		else temp.d = gd1.d;
		if (gd1.d == _infinit) temp.d = _infinit;

		if (gd1.g == _infinit || gd2.g == infinit) { temp.g = _infinit;  return(temp); }
		if (gd1.g == infinit && gd2.g != infinit) { temp.g = infinit; return(temp); }
		if (gd2.g == _infinit) { temp.g = infinit; return(temp); }
		temp.g = gd1.g - gd2.g;

		return(temp);


	}

	gd  fracodotflat(const gd &gd1, const gd &gd2)

		// residue d'hadamard (flat=bemol) de 2 monomes, gd1-gd2, i.e. odot(gd2,temp) >= gd1
		//	on traite les cas degeneres
		// en entree 2 monomes par reference
		// la fonction retourne
		// un monome  pour permettre un appel successif
	{
		gd temp = gd1;

		if (!(gd1.d <= gd2.d))  // dans un premier temps on se limite à ce cas
		{
			gd temp1 = gd1;
			gd temp2 = gd2;
			std::cout << "not defined fracodotflat(" << temp1 << "," << temp2 << ")" << std::endl;

			temp.g = _infinit;
			temp.d = infinit;
			return(temp);
		}

		temp.d = gd1.d;

		if (gd1.g == infinit) { temp.g = infinit; return(temp); }
		if (gd2.g == _infinit) { temp.g = gd1.g; return(temp); }

		temp.g = gd1.g - gd2.g;
		return(temp);

	}


}//fin de namespace mmgd
