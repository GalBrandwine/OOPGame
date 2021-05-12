#include <exception>
#include <iostream>

#include "CGameAdmin.h"


int main()
{
	int rc = 0;

	try
	{
		CGameAdmin admin;

		admin.LoadGameConfigurations();

		if (admin.PlaceOnMap() == 1)
		{
			if (admin.Play() == 1)
			{
				cout << "Game Over!" << endl;

				rc = 1;
			}
		}
	}
	catch (exception ex)
	{
		cout << "Something went wrong... " << ex.what() << endl;
	}

	return 0;
}


