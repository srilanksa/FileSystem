#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

struct Group{
  bool root;
}

struct DataBlock{
  DataBlock *inode;
  Group g;
  uint8_t data[512 - sizeof(Group) - sizeof(DataBlock *)];

  void 

}



int main(){
  
  DataBlock db[10];
  

  return 0;
}
