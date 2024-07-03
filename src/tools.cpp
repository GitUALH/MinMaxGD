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
#include "../include/tools.h"
#else
#include "..\include\tools.h"
#endif

namespace mmgd
{

	int gcd(int a, int b)
	{
		int r;

		while (b > 0)
		{
			r = a % b;
			a = b;
			b = r;
		}
		return(a);
	}

	int lcm(int a, int b)
	{

		int a_sauve, b_sauve;

		a_sauve = a;
		b_sauve = b;

		a = gcd(a, b);

		return((a_sauve*b_sauve) / a);

	}

}
