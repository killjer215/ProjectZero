/*
About this program:
- This program counts words.
- The specific words that will be counted are passed in as command-line
  arguments.
- The program reads words (one word per line) from standard input until EOF or
  an input line starting with a dot '.'
- The program prints out a summary of the number of times each word has
  appeared.
- Various command-line options alter the behavior of the program.

E.g., count the number of times 'cat', 'nap' or 'dog' appears.
> ./main cat nap dog
Given input:
 cat
 .
Expected output:
 Looking for 3 words
 Result:
 cat:1
 nap:0
 dog:0
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "smp0_tests.h"

#define LENGTH(s) (sizeof(s) / sizeof(*s))

/* Structures */
typedef struct {
  char *word;
  int counter;
} WordCountEntry;


  int process_stream(WordCountEntry *entries, int entry_count)
{
  short line_count = 0;
  char buffer[30];
  char newBuffer [100][100];


  while (fgets(buffer, sizeof(buffer),stdin) != NULL) {
    if (*buffer == '.')
      break;
      
   //fprintf(stdout, "Void Buffer : %s \n", buffer);
   size_t len = strlen (buffer);
    if (buffer[len - 1] == '\n')
   buffer[--len] = 0;
  // fprintf(stdout, "Void Buffer : %s \n", buffer);
   //fprintf(stdout, "Void Buffer : %s %d %d\n", entries[line_count].word, line_count, entry_count);
    /* Compare against each entry */
    
    int j=0; 
    int ctr=0;
    for(int i=0;i<=(strlen(buffer));i++)
    {
        // if space or NULL found, assign NULL into newString[ctr]
        if(buffer[i]==' '||buffer[i]=='\0')
        {
            newBuffer[ctr][j]='\0';
            ctr++;  //for next word
            j=0;    //for next word, init index to 0
        }
        else
        {
            newBuffer[ctr][j]=buffer[i];
            j++;
        }
    }
     /*fprintf(stdout, "Void Buffer : %s \n", buffer);
     for (int i = 0; i< ctr; i++)
    fprintf(stdout, "Void Buffer test: %s \n", newBuffer[i]);*/
    for(int k =0; k< entry_count; k++)
    {
        for(int l = 0; l < ctr; l++ ) 
        {
            
             if (!strcmp (entries[k].word, newBuffer[l])){
                 //fprintf(stdout, "strcmp test: ;%s; = ;%s; \n", newBuffer[l], entries[k].word);
            entries[k].counter++;
             }
        }    
    }
    
    if (++line_count == entry_count)
    break;
    }
    return line_count;
    }


void print_result(WordCountEntry *entries, int entry_count, FILE *ptr)
{
    int i = 0;
  fprintf(ptr, "Result:\n");
  while (i < entry_count) {
    fprintf(ptr, "%s:%d\n", entries[i].word, entries[i].counter);
    i++;
  }
}


void printHelp(const char *name)
{
  fprintf(stderr, "usage: %s [-h] <word1> ... <wordN>\n", name);
}


int main(int argc, char **argv)
{
    //fprintf(stdout, "%d\n", argc);
  const char *prog_name = *argv;
//fprintf(stdout, "%d\n", argc);
  //WordCountEntry entries[5];
 
    WordCountEntry *entries;
    entries = malloc(sizeof *entries + 100 * sizeof(char));
    //fprintf(stdout, "%d \n", argc);
     int entryCount = 0;

   FILE *ptr = stdout;

  /* Entry point for the testrunner program */
  if (argc > 1 && !strcmp(argv[1], "-test")) {
    run_smp0_tests(argc - 1, argv + 1);
    return EXIT_SUCCESS;
  }
  argv++;
  while (*argv != NULL) {
    if (**argv == '-') {

      switch ((*argv)[1]) {
        case 'h':
          printHelp(prog_name);
          break;
        case 'f':
        argv++;
        ptr = fopen(*argv, "w");
        if (ptr == NULL) {
            fprintf(stderr, "Can't open input file in.list!\n");
            exit(1);
            }
          break;
        default:
          fprintf(stderr, "%s: Invalid option %s. Use -h for help.\n",
                 prog_name, *argv);
      }
    } else {
        
           
          
            entries[entryCount].word = *argv;
           // fprintf(ptr, "%s %d\n",entries[entryCount].word, entryCount);
            entries[entryCount++].counter = 0;
           // fprintf(ptr, "%d\n",entries[entryCount-1].counter);
     
    }
    //fprintf(ptr, "%d\n",entries[2].counter);
    argv++;
  }
/*fprintf(ptr, "%d %s\n",entries[0].counter,entries[0].word);
 fprintf(ptr, "%d %s\n",entries[1].counter,entries[1].word);
 fprintf(ptr, "%d %s\n",entries[2].counter,entries[2].word);
  fprintf(ptr, "%d %s\n",entries[3].counter,entries[3].word);
 fprintf(ptr, "%d %s\n",entries[4].counter,entries[4].word);*/
  if (entryCount == 0) {
    fprintf(stderr, "%s: Please supply at least one word. Use -h for help.\n",
           prog_name);
    return EXIT_FAILURE;
  }
  if (entryCount == 1) {
    fprintf(stderr, "Looking for a single word\n");
  } else {
    fprintf(ptr, "Looking for %d words\n", entryCount);
  }

  process_stream(entries, entryCount);
  print_result(entries, entryCount, ptr);
  
  return EXIT_SUCCESS;
}