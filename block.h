//Buffer declaration for data blocks.

#include <iostream>
#include <fstream>
#include "zipcode.h"
#include "deltext.h"
#ifndef block_h
#define block_h

struct BlockHeader {
	public:
	int num_records;
    int next_block;
    int block_index_location;
	int num_bytes; //Total number of bytes currently in the buffer
	int max_bytes; //Number of maximum bytes allowed in the buffer.
};

struct Block {
    //Zipcode records[20];//Limit 20 records per block, since the goal is to allow however many zipcodes fit in a certain amount of bytes. This can change, but I think that this should be enough.
    ///^^^This line, right here. Creating this array causes a segmentation fault and I don't know why.
	BlockHeader header;
	DelimTextBuffer d1;
	
	
	Block();
	
	bool Init(int max_bytes, int block_index_location, int next_block);
	bool Pack(Zipcode & z);//Will pack a Zipcode if the record length does not cause the buffer to exceed max_bytes.
	bool Unpack(Zipcode & z, std::ifstream& i);//Will unpack a Zipcode from the block, if there is one to unpack still.
	bool Clear();
};

#include "block.cpp"
#endif