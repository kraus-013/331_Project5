//Buffer implementation for data blocks.

#include "block.h"

Block::Block(){
	Clear();
};
	
bool Block::Pack(Zipcode & z){
	
};//Will pack a Zipcode (into this block) if the record length does not cause the block to exceed max_bytes.

bool Block::Unpack(Zipcode & z, std::ifstream& i){
	//Add some validation to this, so it doesn't allow it to unpack beyond this current block.
	d1.Read(i);
	z.Unpack(d1);
};//Will unpack a Zipcode from the block, if there is one to unpack still.

bool Block::Clear(){
	header.num_records=0;
	header.next_block=0;
	header.block_index_location=0;
	header.num_bytes=0;
	header.max_bytes=0;
	
};

bool Block::Init(int max_bytes, int block_index_location, int next_block){
	header.next_block=next_block;
	header.block_index_location=block_index_location;
	header.max_bytes=max_bytes;
};