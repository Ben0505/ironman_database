// Specification file for the Armor class
// IDE: Visual Studio

#include <string>
#include <vector>

#ifndef ARMOR_H
#define ARMOR_H

using namespace std;

class Armors
{
private:
	string codename;	// Codename (name of armor) (unique key)
	string armorType;	// Type (amor type) (secondary key)
	string creator;	// Creator 
	int yearMade;	// Year Made - int (year of creation)
	string users;	// Users - vector of string (multiple users)
	string movieAppeared;	// movieAppeared - string (Name of the movies appeared)
	string currStats;	// Current Status (active, damaged, destroyed)
	string capabilities;	// Capabilities - vector of string (multiple capabilities)
	string weapons;	// Weapons - vector of string (multiple weapons)
	string precede;	// Precede - string (precede model)
	string succeed;	// Succeed - string (succeeding model)

public:
	// Constructors
	Armors()
	{
		codename = "";
		armorType = "";
		creator = "";
		yearMade = 0;
		users = "";
		movieAppeared = "";
		currStats = "";
		capabilities = "";
		weapons = "";
		precede = "";
		succeed = "";
	};

	Armors(string coden, string type, string inventor, int yearmade, 
		string user, string movieShown, string currStat, string capbl, 
		string weap, string precedeModel, string succeedModel) : codename(coden), 
																	armorType(type), 
																	creator(inventor),
																	yearMade(yearmade),
																	users(user),
																	movieAppeared(movieShown),
																	currStats(currStat),
																	capabilities(capbl),
																	weapons(weap),
																	precede(precedeModel),
																	succeed(succeedModel) {};

	// Destructor
	// ~Armor();

	// Setters
	void setCodenmae(string cn) { codename = cn; }

	// Getters
	string getCodename() const { return codename; }

	// Other functions

	// Operator functions
	friend bool operator<(const Armors& a1, const Armors& a2) { return a1.codename < a2.codename; }
	friend bool operator>(const Armors& a1, const Armors& a2) { return a1.codename > a2.codename; }
	friend bool operator==(const Armors& a1, const Armors& a2) { return a1.codename == a2.codename; }
	friend ostream& operator <<(ostream& out, const Armors& armor) {
		cout << "--------------------------------------------------------------------------" << endl;
		out << armor.codename << ":" << armor.armorType << "\nMade by: " << armor.creator << " in " << armor.yearMade 
			<< "\nUsers: " << armor.users << ", appeared in: " << armor.movieAppeared << "\nCurrent Status: " << armor.currStats
			<< "\nArmor Capabilities: " << armor.capabilities << "\nWeapons: " << armor.weapons
			<< "\nPrecede: " << armor.precede << "\tSucceed: " << armor.succeed ;
		cout << "--------------------------------------------------------------------------" << endl;
		return out;
	}
	
	friend istream& getline (istream& in, Armors* armor) {
		getline(in, armor->codename);
		getline(in, armor->armorType);
		getline(in, armor->creator);
		in.ignore();
		in >> armor->yearMade;
		getline(in, armor->users);
		getline(in, armor->movieAppeared);
		getline(in, armor->currStats);
		getline(in, armor->capabilities);
		getline(in, armor->weapons);
		getline(in, armor->precede);
		getline(in, armor->succeed);
		return in;
	}

};

#endif
#pragma once
