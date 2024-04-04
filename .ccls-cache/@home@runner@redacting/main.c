#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>


void REDACT(char * stringPointer, char *RedWord)
{
  int length = strlen(RedWord);
  if ((isalpha(*(stringPointer + length)) ==0)&(isalpha(*(stringPointer + length)) ==0))
  {
    for (int i = 0; i<length; i++)
      {
        *(stringPointer+i) = '*';
    
      }
  }

}
void removeChar (char * stringPointer)
{
  while ( * stringPointer !=  '\0')
  {
      
    *stringPointer = *(stringPointer + 1);
    stringPointer ++;
  }
}
void getNextWord(char *Line, char*stringPointer)
{
  while (* Line ==  ' ')
  {
    removeChar(Line);
  }
  while (( * Line !=  ' ') & ( * Line !=  '\0'))
  {
    *stringPointer = * Line;
    stringPointer++;
    removeChar(Line);
      
  }
}
void removeNonAlpha (char * stringPointer)
{
   while ( * stringPointer !=  '\0')
  {
      
    if (isalpha(*stringPointer) == 0 )
    {
      removeChar(stringPointer);
    }
    else
    {
      stringPointer++;
    }
      
  }
}
void checkToBeRedacted (char* stringPointer,const char *redact_words_filename)
{
  FILE *RedWords;
  char RedFile[10000];
  char * RedWord;

  RedWords =  fopen(redact_words_filename, "r");
  fgets(RedFile, 10000, RedWords);
  while (feof(RedWords) != true)
  {
    
    RedWord = strtok(RedFile, ",");
    while (RedWord != NULL)
    {
      removeNonAlpha(RedWord);
      
      
      if(strstr(stringPointer, RedWord) != NULL)
      {
        
        REDACT(stringPointer,RedWord);
        
      }
      RedWord = strtok(NULL, ",");
    }
    fgets(RedFile, 10000, RedWords);
    
  }
  fclose(RedWords);
}
void removeTailingSpace (char* stringPointer)
{
  while ( * stringPointer !=  '\n')
  {
      
    stringPointer++;
      
  }
  stringPointer++;
  *stringPointer = '\0';
}

void reset (char* stringPointer)
{
  while ( * stringPointer !=  '\0')
  {
    *stringPointer = '\0';
    stringPointer++;
      
  }
}


void redact_words(const char *text_filename, const char *redact_words_filename){
  FILE *OutText = fopen("result.txt","w");
  fclose(OutText);
  FILE *InText = fopen(text_filename, "r");
  char InputRow[10000];
  char outLine[10000];
  char InWord[10000];
  char* outLineP = &outLine[0];
  char* InputRowP = &InputRow[0];
  char * InWordP = &InWord[0];
  fgets(InputRow, 10000, InText);
  while (feof(InText) != true)
  {
    reset(outLineP);
    
    getNextWord(InputRowP,InWordP );

    while(*InWordP != '\0')
    {
      

      checkToBeRedacted(InWord,redact_words_filename);
      
   
      strcat (outLine, InWord);
      strcat (outLine, " ");

      reset(InWord);
      getNextWord(InputRowP,InWordP );
      
    }
    removeTailingSpace(outLineP);
    
    OutText = fopen("result.txt","a");
    fprintf(OutText, "%s", outLine);
    fclose(OutText);
    fgets(InputRow, 10000, InText);

  }
}
int main(void){
  char * cunt = "Input.txt";
  char * cock = "Redact_Word.txt";
  redact_words(cunt,cock);
  
}