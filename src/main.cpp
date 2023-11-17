#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define ARR_SIZE(x) (sizeof(x)/sizeof(x[0]))

#define HEAD_DATA_FLAG 0b00000001
#define HEAD_PERM_FLAG 0b00000010

typedef uint8_t u8;

/*
	head flags
	0b0000_0000
				    >theres data present to be read from
*/
struct DataBlock
{
  DataBlock *inode;
  u8 head;			//should only be read at the head
  u8 data[512 - sizeof (head) - sizeof (inode)];
};
	
int
get_filled_blocks (DataBlock * arr, int n)
{
  int ret = 0;
  for (int i = 0; i < n; i++)
  {
    if (((arr + i)->head & HEAD_DATA_FLAG) > 0)
    {
      ret++;
    }
  }
  return ret;
}

DataBlock *
find_empty_data_block (DataBlock * arr, int n)
{
  DataBlock *ret = NULL;
  for (int i = 0; i < n; i++)
  {
    if (((arr + i)->head & HEAD_DATA_FLAG) == 0)
    {
      ret = arr + i;
      break;
    }
  }
  return ret;
}

void
fill_data_into_data_blocks (char *filename, DataBlock * arr, int db_n)
{

  FILE *fd = fopen (filename, "rb");

  DataBlock *current = find_empty_data_block (arr, db_n);
  if (current == NULL)
    {
      puts ("FAILED, NO DATABLOCKS AVAILABLE");
      return;
    }

  current->head |= HEAD_DATA_FLAG;

  int c = 0;

  //fgetc() returns an int and EOF is -1
  int i = 0;
  while ((c = fgetc (fd)) != EOF)
  {
    current->data[i] = (u8) c;
    i++;
    if (i >= ARR_SIZE (current->data))
    {
			puts("ALLOCATING ANOTHER DATA BLOCK");
      DataBlock *tmp = current;
      current = find_empty_data_block (arr, db_n);
			if(current == NULL) 
			{
				puts("ERROR, NO MORE MEMORY, ABORTING");
				return;
			}

			current->head |= HEAD_DATA_FLAG;
			i=0;
    }
  }

  fclose (fd);
}

int
main (int argc, char **argv)
{


  DataBlock db[10] = { 0 };
  DataBlock *ptr = db;

  printf ("%lu\n", ARR_SIZE (ptr->data));

  fill_data_into_data_blocks (argv[1], db, ARR_SIZE (db));
	printf("%d\n",get_filled_blocks(db, ARR_SIZE(db)));

  return 0;
}
