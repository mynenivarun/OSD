#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char buf [1024];

void tail (int fd, char *name, int line) {
  int i, n;  //here the size of the read chunk is defined by n, and i is used to keep a track of the chunk index
  int l; // here total lines are defined by l, and the character count in the string is defined by c
  int count = 0;

  int temp = open ("temporary", O_CREATE | O_RDWR);     // creating a temporary file to store the data/ user input in it then print it

  while((n = read(fd, buf, sizeof(buf))) > 0 )
  {
    write (temp, buf, n);                               // writing the n chunks of data from buffer to the temp file

    for(i=0;i<=n ;i++)
    {
      if(buf[i] != '\n')                                // checking for end of line, if so then conitnue
      {
        continue;
      }
      else                                              // else count the number of lines in the file
      {
        l++;
      }
    }
  }

  close (temp);

  if (n < 0)
  {
    printf(1, "tail: read error\n");
    exit();
  }

  temp = open ("temporary", 0);                       // opening the file reading the file from the beginning
  
  while((n = read(temp, buf, sizeof(buf))) > 0 )
  {
    for (i = 0; i<n; i++) 
    {
      if (count >= (l - line))          // to check if the counter value exceeds the last n lines to be printed or not, if yes then print those lines
      {
        printf(1,"%c",buf[i]);
      }
      else if (l < line)                // to check i fthe total number of lines in the file are less than the requested number of lines
      {
        printf(1,"%c",buf[i]);
      }
      else if (buf[i] == '\n')          // to check for end of line in the buffer, to increase the count value
      {
        count++;
      }
    }
  }
  close (temp);
  
  unlink("temporary");                  // delete the file before closing the function
}


int 
main(int argc, char *argv[]) {
  int i;
  int fd = 0;	// when the file is not specified, then it will take input from the user
  int x = 10;	// will read the last 10 lines by default
  char *file;	// pointer to the name of the file
  char a;

  file = ""; // in the case when no file name is specified, it will take input from the user
     
  if (argc <= 1) 
  {	
    tail(0, "", 10);	// handles the default case of taking input from user and printing only last 10 lines
    exit();
  }

  else {
    for (i = 1; i < argc; i++) 
    {
		  a = *argv[i];	// assigns the char value of the argv to the var a
				
      if (a == '-') 
      {             // it means that -NUM is provided, hence limited number of lines are to be printed
        argv[i]++;
        x = atoi(argv[i]++);
      }
				
      else 
      {	// if a !='-' then it implies that number of lines are not defined and hence default lines will print
        if ((fd = open(argv[i], 0)) < 0) 
        {// this will execute if the file is unable to open
          printf(1, "tail: cannot open %s\n", argv[i]);
          exit();
        }
      }
    }
		 
  tail(fd,file, x);
  close(fd);
  exit();    

  }
}
