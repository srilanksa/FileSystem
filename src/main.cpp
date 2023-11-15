#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define ARR_SIZE(x) (sizeof(x)/sizeof(x[0]))

#define HEAD_DATA_FLAG 0b00000001
#define HEAD_PERM_FLAG 0b00000010

typedef u8 uint8_t;

/*
	head flags
	0b0000_0000
				    >theres data present to be read from
*/	
struct 
DataBlock
{
  DataBlock *inode;
	u8 head; //should only be read at the head
	u8 data[512 - sizeof(head) - sizeof(inode)];
};

DataBlock *find_empty_data_block(DataBlock *arr, int n){
	DataBlock *ret = NULL;
	for(int i = 0; i<n; i++){
		if(((arr+i)->head && HEAD_DATA_FLAG) != 0){
			ret = arr+i;
			break;
		}
	}
	return ret;
}

void
fill_data_into_data_blocks(
		u8 *data, int data_n, DataBlock *arr, int db_n
		){
	
	static u8 *d_ptr=NULL;

}




int main(){
  
  DataBlock db[10]={0};
	
	printf("sizeof db = %ld, %lx\n",sizeof(db), sizeof(db));

	u8 buffer[sizeof(db[0] - sizeof(DataBlock *) - sizeof(u8))]={0};
	

  return 0;
}
