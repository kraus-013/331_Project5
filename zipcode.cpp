/**
 * @file Zipcode.cpp
 * @brief Header file for Zipcode class
 * @version 0.1
 * @date 2023-04-10
 * \author Steven Kraus
 * \author Emily Yang
 * \author Tyler Knudtson
 * \author Ashesh Nepal
*/

#include "zipcode.h"
#include <string>
#include <cstring>

Zipcode::Zipcode ()
{
	Clear ();
}

void Zipcode::Clear ()
{
	// set each field to an empty string
	Code [0] = 0;
	Placename [0] = 0;
	State [0] = 0;
	County [0] = 0;
	Lat [0] = 0;
	Long [0] = 0;
}

int Zipcode::Pack (DelimTextBuffer & Buffer) const
{// pack the fields into a DelimTextBuffer, return TRUE if all succeed, FALSE o/w
	int result;
	Buffer . Clear ();
	result = Buffer . Pack (Code);///Set Code to '' if writing the header.
	result = result && Buffer . Pack (Placename);
	result = result && Buffer . Pack (State);
	result = result && Buffer . Pack (County);
	result = result && Buffer . Pack (Lat);
	result = result && Buffer . Pack (Long);
	return result;
}

int Zipcode::Unpack (DelimTextBuffer & Buffer)
{
	int result;
	result = Buffer . Unpack (Code);//remove when removing above multiline comments
	result = result && Buffer . Unpack (Placename);
	result = result && Buffer . Unpack (State);
	result = result && Buffer . Unpack (County);
	result = result && Buffer . Unpack (Lat);
	result = result && Buffer . Unpack (Long);

	return result;
}

int Zipcode::InitBuffer (DelimTextBuffer & Buffer)
// initialize a DelimTextBuffer to be used for Persons
{
	return TRUE;
}

void Zipcode::Print (std::ostream & stream)
{
	stream << "info:"
		<< "\t   ZipCode '"<<Code<<"'\n"
		<< "\t Placename '"<<Placename<<"'\n"
		<< "\t     State '"<<State<<"'\n"
		<< "\t    County '"<<County<<"'\n"
		<< "\t       Lat '"<<Lat<<"'\n"
		<< "\t      Long '"<<Long<<"'\n" <<std::flush;
}

int Zipcode::Size(){
	int zipcodeSize = 0;
	std::string zCode = Code;
	std::string zPlace = Placename;
	std::string zState = State;
	std::string zCounty = County;
	std::string zLat = Lat;
	std::string zLong = Long;
	zipcodeSize += zCode.length()+ zPlace.length() + zState.length() + zCounty.length() + zLat.length() + zLong.length() + 5;

	return zipcodeSize;
}