/**
\file State.h
\author Steven Kraus
\author Emily Yang
\author Tyler Knudtson
\author Ashesh Nepal
\brief Declaration file for State class
*/
#ifndef STATE_H
#define STATE_H

class State
{
    //Data members set as public for easy access 
public:
    State();
    /** Data members */
	char stateName [5]; //State name abbriviation 
	char easternZipcode [10]; //Easternmost Zipcode
	char westernZipcode [10]; // Westernmost Zipcode
	char northernZipcode [10]; //Northernmost Zipcode
	char southernZipcode [10]; //Southernmost Zipcode
	char largestLong [10]; //Largest longitude
	char smallestLong [10]; // Smallest longitude
	char largestLat [10]; //Largest Latitude
	char smallestLat [10]; // Smallest Latitude
};


State::State()
{
    // Set each field to an empty string
	 stateName[0]  = 0;
	 easternZipcode[0]  = 0;
	 westernZipcode[0]  = 0;
	 northernZipcode[0]  = 0;
	 southernZipcode[0]  = 0;
	 largestLong[0]  = 0;
	 smallestLong[0]  = 0;
	 largestLat[0]  = 0;
	 smallestLat[0]  = 0;
}
#endif