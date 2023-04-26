/**
\file Proj3_group5.cpp
\author Steven Kraus
\author Emily Yang
\author Tyler Knudtson
\author Ashesh Nepal
\brief Takes a csv file containing US postal codes as inputs and generates an output table consiting of each of the state's
easternmost, westernmost, northernmost and southernmost zipcodes based on latitude and longitude comparisions
*/
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include "deltext.h"
#include "zipcode.h"
#include "State.h"


/**
\fn compareStates (required for sorting)
compares two states to see if they're in alphabetical order
\param An instance of stateStruct
\param An instance of stateStruct
\return true if the state field in the state structs are in alphabetical order*/
bool compareStates(State a, State b){
	if(a.stateName[0] == b.stateName[0])
		return(a.stateName[1] < b.stateName[1]);

	return (a.stateName[0] < b.stateName[0]);
}

/**
\fn constructStateArray;
copies into an array of stateStruct structs given an array of Zipcode objects
\param Array of stateStruct objects
\param Array of Zipcode Objects
\param int Size of stateStruct Array 
\param int Size of Zipcode Array
\post stateStruct Array will be filled with data from Zipcode Array
**/
void constructStateArray(State sArray[], Zipcode zArray[], int zArraySize){
	int count = 0;
	for(int i = 0; i < zArraySize; i++){
		bool found = false;
		for(int j= 0; j < 50; j++){
			if(zArray[i].State[0] == sArray[j].stateName[0]&&zArray[i].State[1] == sArray[j].stateName[1]){
				found = true;
				break;
			}
		}
		if(!found){
			strcpy(sArray[count].stateName,zArray[i].State);
			strcpy(sArray[count].easternZipcode,zArray[i].Code);
			strcpy(sArray[count].westernZipcode,zArray[i].Code);
			strcpy(sArray[count].northernZipcode,zArray[i].Code);
			strcpy(sArray[count].southernZipcode,zArray[i].Code);
			strcpy(sArray[count].largestLong, zArray[i].Long);
			strcpy(sArray[count].smallestLong, zArray[i].Long);
			strcpy(sArray[count].largestLat, zArray[i].Lat);
			strcpy(sArray[count].smallestLat, zArray[i].Lat);
			count++;
			if(count >= 50)
				break;
		}
	}
}

/**
\fn findLargestSmallestLatLong
finds the largest and smallest latitudes and longitues and corresponding Zipcodes from an array of Zipcodes and stores them in an array of stateStruct's
\param Array of stateStruct objects
\param Array of Zipcode Objects
\param int Size of stateStruct Array 
\param int Size of Zipcode Array
\post stateStruct Array will be filled with data corresponding to Zipcodes that are the furthest in each direction*/
void setZipCodes(State sArray[], Zipcode zArray[], int zArraySize){

	for(int i = 0; i < zArraySize; i++){
		for(int j = 0; j < 51; j++){
			if(zArray[i].State[0] == sArray[j].stateName[0]&&zArray[i].State[1] == sArray[j].stateName[1]){
				if(std::stof(zArray[i].Long) > std::stof(sArray[j].largestLong)){
					strcpy(sArray[j].largestLong,zArray[i].Long);
					strcpy(sArray[j].westernZipcode,zArray[i].Code);
				}
				if(std::stof(zArray[i].Long) < std::stof(sArray[j].smallestLong)){
					strcpy(sArray[j].smallestLong,zArray[i].Long);
					strcpy(sArray[j].easternZipcode,zArray[i].Code);
				}
				if(std::stof(zArray[i].Lat) > std::stof(sArray[j].largestLat)){
					strcpy(sArray[j].largestLat,zArray[i].Lat);
					strcpy(sArray[j].northernZipcode,zArray[i].Code);
				}
				if(std::stof(zArray[i].Lat) < std::stof(sArray[j].smallestLat)){
					strcpy(sArray[j].smallestLat,zArray[i].Lat);
					strcpy(sArray[j].southernZipcode,zArray[i].Code);
				}
			}
		}
	}
}

/**
\fn outputTable
\param string The file name to output to
\param the DelimTextBuffer that will be used for output
\param Array of stateStruct objects
\param int Size of stateStruct Array 
\post the stateStruct array is packed into the buffer and written to the specified file*/
void outputTable(std::string outputFileName, DelimTextBuffer OutBuff, State sArray[]){
	std::ofstream OutFile (outputFileName,std::ios::out);
	char state [3] = "ST";
	char easternZipcode [6] = "E-Zip";
	char westernZipcode [6] = "W-Zip";
	char northernZipcode [6] = "N-Zip";
	char southernZipcode [6] = "S-Zip";
	OutBuff.Clear();
	OutBuff.Pack(state);
	OutBuff.Pack(easternZipcode);
	OutBuff.Pack(westernZipcode);
	OutBuff.Pack(northernZipcode);
	OutBuff.Pack(southernZipcode);
	OutBuff.Write(OutFile);

	std::cout << state << "," << easternZipcode << "," << westernZipcode << "," << northernZipcode << "," << southernZipcode << std::endl;

	for(int i = 0;i < 50; i++){
		OutBuff.Clear();
		OutBuff.Pack(sArray[i].stateName);
		OutBuff.Pack(sArray[i].easternZipcode);
		OutBuff.Pack(sArray[i].westernZipcode);
		OutBuff.Pack(sArray[i].northernZipcode);
		OutBuff.Pack(sArray[i].southernZipcode);
		OutBuff.Write(OutFile);
		std::cout << sArray[i].stateName << "," << sArray[i].easternZipcode << "," << sArray[i].westernZipcode << "," << sArray[i].northernZipcode << "," << sArray[i].southernZipcode << std::endl;
	}
	OutFile.close();
}

/**
\fn application
Contains the code for controlling the Zipcode class and generating output file.
\pre specified InFile must be present
\post sorted OutFile with zip codes from each state will be created
*/
void application()
{
	Zipcode ZipcodeArray[41000];
	State StateArray[50];
	int index = 0;
	std::string filename;
	std::cout << "Please enter the file name: ";
	std::cin >> filename;
	std::ifstream InFile(filename, std::ios::in);
	DelimTextBuffer InBuff;
	Zipcode :: InitBuffer (InBuff);
	while(InFile.peek()!=EOF)
	{
	InBuff.Read(InFile);
	ZipcodeArray[index].Unpack(InBuff);
	index++;
	}
	InFile.close();
	constructStateArray(StateArray,ZipcodeArray,index);
	std::sort(StateArray,StateArray+50, compareStates);
	setZipCodes(StateArray,ZipcodeArray,index);
	std::string outputFileName = "output_table.csv";
	DelimTextBuffer OutBuff;
	Zipcode :: InitBuffer (OutBuff);
	outputTable(outputFileName,OutBuff,StateArray);
}

/**
\fn main
Executes the code present in application()
*/
int main()
{
	application();
	return 0;
}
