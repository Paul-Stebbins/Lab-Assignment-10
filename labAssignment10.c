#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
 int isWord;
 int count;
 struct Trie *children[26];
};

struct Trie *createTrie();

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
  int k=0;
  if(k==strlen(word)){
    pTrie->isWord=1;
    pTrie->count++;
    return;
  }
  int nextIndex=word[k]-'a';
  if(pTrie->children[nextIndex]==NULL){
    pTrie->children[nextIndex]=createTrie();
  }
  insert(pTrie->children[nextIndex],word);
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
  if (pTrie==NULL)
    return 0;
  int k=0;
  while(k<strlen(word)){
    int nextIndex=word[k]-'a';
    if(pTrie->children[nextIndex]==NULL){
      return 0;
    }
    pTrie=pTrie->children[nextIndex];
    k++;
  }
  if(pTrie->isWord==1){
    return pTrie->count;
  }else{
    return 0;
  }
  
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
  int i;
  for(i=0;i<26;i++){
    if(pTrie->children[i]!=NULL){
      deallocateTrie(pTrie->children[i]);
    }
  }
  free(pTrie);
}

// Initializes a trie structure
struct Trie *createTrie()
{
  struct Trie *temp;
  temp=malloc(sizeof(struct Trie));
  temp->isWord=0;
  for(int i=0;i<26;i++){
    temp->children[i]=NULL;
  }
  return temp;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
  FILE *filePtr=fopen(filename,"r");
  char input[100];
  int n;
  int count=0;

  fscanf(filePtr,"%d",&n);

  while(fscanf(filePtr,"%s",input)!=EOF){
    pInWords[count] = strdup(input);
    count++;
  }
  return count;
}

int main(void)
{
  char *inWords[256];

  //read the number of the words in the dictionary
  int numWords = readDictionary("dictionary.txt", inWords);
  for (int i=0;i<numWords;++i)
  {
    printf("%s\n",inWords[i]);
  }

  struct Trie *pTrie = createTrie();
  for (int i=0;i<numWords;i++)
  {
    insert(pTrie, inWords[i]);
  }
  // parse lineby line, and insert each word to the trie data structure
  char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
  for (int i=0;i<5;i++)
  {
    printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
  }
  pTrie = deallocateTrie(pTrie);
  if (pTrie != NULL)
    printf("There is an error in this program\n");
  return 0;
}