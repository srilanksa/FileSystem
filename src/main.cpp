#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>




struct DataBlock{
  DataBlock *inode;
  union{
    uint8_t group; //should only be read at the head
    uint8_t data[512 - sizeof(group) - sizeof(inode)];
  }

  void fill_block(FILE *f, ){
    
  }

}



int main(){
  
  DataBlock db[10];
  

  return 0;
}
