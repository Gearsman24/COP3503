#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Weapon
{
private:
	string weaponName;
	int weaponPower = 0;
	float weaponConsumption = 0;

public:
	//Weapon Constructor
	Weapon(string pName, int pPower, float pConsumption)
	{
		weaponName = pName;
		weaponPower = pPower;
		weaponConsumption = pConsumption;
	}

	string getWeaponName()
	{
		return weaponName;
	}
	int getWeaponPower()
	{
		return weaponPower;
	}
	float getWeaponConsumption()
	{
		return weaponConsumption;
	}
};

class Ship
{
private:
	string shipName;
	string shipClass;
	short shipLength = 0;
	int shipShield = 0;
	float shipWarp = 0;
	int weaponCount = 0;
	vector<Weapon> weapons;

public:
	//Ship Constructor
	Ship(string pName, string pType, short pLength, int pShield, float pWarp, int pWeaponCount, vector<Weapon> pWeapons)
	{
		shipName = pName;
		shipClass = pType;
		shipLength = pLength;
		shipShield = pShield;
		shipWarp = pWarp;
		weaponCount = pWeaponCount;
		weapons = pWeapons;

	}

	string getShipName()
	{
		return shipName;
	}
	string getShipClass()
	{
		return shipClass;
	}
	short getShipLength()
	{
		return shipLength;
	}
	int getShipShield()
	{
		return shipShield;
	}
	float getShipWarp()
	{
		return shipWarp;
	}
	int getShipWeaponCount()
	{
		return weaponCount;
	}
	vector<Weapon> getShipWeapons()
	{
		return weapons;
	}


	int getShipPower()
	{
		int shipPower = 0;
		for (int i = 0; i < weaponCount; i++)
		{
			shipPower = shipPower + weapons.at(i).getWeaponPower();
		}
		return shipPower;
	}
	Weapon getHighestPowerWeapon()
	{
		Weapon highestPower = weapons.at(0);
		for (int i = 1; i < weaponCount; i++)
		{
			if (highestPower.getWeaponPower() < weapons.at(i).getWeaponPower())
			{
				highestPower = weapons.at(i);
			}
		}

		return highestPower;
	}

	void printShip()
	{
		cout << "Name: " << shipName << endl;
		cout << "Class: " << shipClass << endl;
		cout << "Length: " << shipLength << endl;
		cout << "Shield capacity: " << shipShield << endl;
		cout << "Maximum Warp: " << shipWarp << endl;
		cout << "Armaments:" << endl;

		if (weaponCount == 0)
		{
			cout << "Unarmed" << endl;
		}
		else
		{
			for (int i = 0; i < weaponCount; i++)
			{
				cout << weapons.at(i).getWeaponName() << ", ";
				cout << weapons.at(i).getWeaponPower() << ", ";
				cout << weapons.at(i).getWeaponConsumption() << endl;
			}
			cout << "Total firepower: " << getShipPower() << endl;
		}
		cout << endl;
	}
};




//Open File
void openFile(ifstream& file, int fileOption)
{
	if (fileOption == 1)
	{
		file.open("friendlyships.shp", ios::in | ios::binary);
	}
	else if (fileOption == 2)
	{
		file.open("enemyships.shp", ios::in | ios::binary);
	}
}


int main()
{
	cout << "Which file(s) to open?\n";
	cout << "1. friendlyships.shp" << endl;
	cout << "2. enemyships.shp" << endl;
	cout << "3. Both files" << endl;
	int option;
	cin >> option;

	/* Load files here */

	vector<Ship> ships;
	vector<Ship> armedShips;
	vector<Ship> unarmedShips;


	ifstream binaryFile;

	for (int i = 1; i <= option; i++)
	{
		if (option < 3)
		{
			//Open File Chosen
			if (option == 1)
			{
				openFile(binaryFile, 1);
			}
			else if (option == 2)
			{
				openFile(binaryFile, 2);
			}
		}
		else if (option == 3)
		{
			//Open All Files
			openFile(binaryFile, i);
		}

		if (binaryFile.is_open())
		{
			//Count of Ships, 4 bytes
			int numShips = 0;
			binaryFile.read(reinterpret_cast<char*>(&numShips), 4);

			//Data for each ship
			for (int i = 0; i < numShips; i++)
			{
				//Length of the ship name, 4 bytes
				int shipNameLength = 0;
				binaryFile.read(reinterpret_cast<char*>(&shipNameLength), 4);
				//String data for the ship name, shipNameLength bytes
				char* name = new char[shipNameLength];
				for (int s = 0; s < shipNameLength; s++)
				{
					binaryFile.read(&name[s], 1);
				}
				string shipName(name);
				delete[] name;

				//Length of the ship class, 4 bytes
				int shipClassLength = 0;
				binaryFile.read(reinterpret_cast<char*>(&shipClassLength), 4);
				//String data for the ship class (type of ship), "shipClassLength bytes
				name = new char[shipClassLength];
				for (int s = 0; s < shipClassLength; s++)
				{
					binaryFile.read(&name[s], 1);
				}
				string shipClass(name);
				delete[] name;

				//Length in meters of the ship, 2 bytes
				short shipLength = 0;
				binaryFile.read(reinterpret_cast<char*>(&shipLength), 2);

				//Shield capacity in terajoules, 4 bytes
				int shipShield = 0;
				binaryFile.read(reinterpret_cast<char*>(&shipShield), 4);

				//Warp speed of the ship, 4 bytes
				float shipWarp = 0;
				binaryFile.read(reinterpret_cast<char*>(&shipWarp), 4);

				//Count of Weapons on the ship, 4 bytes
				int numWeapons = 0;
				binaryFile.read(reinterpret_cast<char*>(&numWeapons), 4);

				//Data for each weapon
				vector<Weapon> shipWeapons;
				for (int j = 0; j < numWeapons; j++)
				{
					//Length of the weapon name, 4 bytes
					int weaponNameLength = 0;
					binaryFile.read(reinterpret_cast<char*>(&weaponNameLength), 4);
					//String data for the weapon name, weaponNameLength bytes
					name = new char[weaponNameLength];
					for (int s = 0; s < weaponNameLength; s++)
					{
						binaryFile.read(&name[s], 1);
					}
					string weaponName(name);
					delete[] name;

					//Power rating integer, 4 bytes
					int weaponPower = 0;
					binaryFile.read(reinterpret_cast<char*>(&weaponPower), 4);

					//Power consumption float, 4 bytes
					float weaponConsumption = 0;
					binaryFile.read(reinterpret_cast<char*>(&weaponConsumption), 4);

					/* ADD WEAPON */
					Weapon newWeapon(weaponName, weaponPower, weaponConsumption);
					shipWeapons.push_back(newWeapon);

				}

				/* ADD SHIP */
				Ship newShip(shipName, shipClass, shipLength, shipShield, shipWarp, numWeapons, shipWeapons);
				ships.push_back(newShip);

				if (numWeapons == 0)
				{
					unarmedShips.push_back(newShip);
				}
				else
				{
					armedShips.push_back(newShip);
				}
			}
		}

		binaryFile.close();

		if (option != 3)
		{
			break;
		}
	}


	cout << "1. Print all ships" << endl;
	cout << "2. Starship with the strongest weapon" << endl;
	cout << "3. Strongest starship overall" << endl;
	cout << "4. Weakest ship (ignoring unarmed)" << endl;
	cout << "5. Unarmed ships" << endl;

	cin >> option;

	/* Work your magic here */
	//Print all ships
	if (option == 1)
	{
		for (unsigned int i = 0; i < ships.size(); i++)
		{
			ships.at(i).printShip();
		}
	}
	//Starship with the strongest weapon
	else if (option == 2)
	{
		Ship strongestWeaponShip = armedShips.at(0);
		for (unsigned int i = 1; i < armedShips.size(); i++)
		{
			if (strongestWeaponShip.getHighestPowerWeapon().getWeaponPower() < armedShips.at(i).getHighestPowerWeapon().getWeaponPower())
			{
				strongestWeaponShip = armedShips.at(i);
			}
		}

		strongestWeaponShip.printShip();
	}
	//Strongest starship overall
	else if (option == 3)
	{
		Ship strongestShip = armedShips.at(0);
		for (unsigned int i = 1; i < armedShips.size(); i++)
		{
			if (strongestShip.getShipPower() < armedShips.at(i).getShipPower())
			{
				strongestShip = armedShips.at(i);
			}
		}
		strongestShip.printShip();
	}
	//Weakest ship
	else if (option == 4)
	{
		Ship weakestShip = armedShips.at(0);
		for (unsigned int i = 1; i < armedShips.size(); i++)
		{
			if (weakestShip.getShipPower() > armedShips.at(i).getShipPower())
			{
				weakestShip = armedShips.at(i);
			}
		}
		weakestShip.printShip();
	}
	else if (option == 5)
	{
		for (unsigned int i = 0; i < unarmedShips.size(); i++)
		{
			unarmedShips.at(i).printShip();
		}
	}

	return 0;
}