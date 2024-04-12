#include <stdio.h>
#include <stdlib.h>


struct RecordType
{
int id;
char name;
int order;
};

//Node for separate chaining
struct Node
{
   struct RecordType data;
   struct Node* next;
};

struct HashType
{
struct Node* head;
};

//Computes hash function
int hash(int x, int hashSz)
{
return x % hashSz;
}

//Function inserts new record 
void insertRecord(struct HashType* pHashArray, int hashSz, struct RecordType record)
{
int index = hash(record.id, hashSz);
struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
newNode->data = record;
newNode->next = pHashArray[index].head;
pHashArray[index].head = newNode;
}
//Function displays records
void displayRecordsInHash(struct HashType* pHashArray, int hashSz)
{
for (int i = 0; i < hashSz; ++i)
{
printf("index %d -> ", i);
struct Node* current = pHashArray[i].head;
   while (current != NULL)
{
	printf("%d %c %d -> ", current->data.id, current->data.name, current->data.order);
	current = current->next;
}

printf("NULL\n");
}
}

//Function that frees memory
void freeHashTable(struct HashType* pHashArray, int hashSz)
{
	for (int i = 0; i < hashSz; ++i)
{
	struct Node* current = pHashArray[i].head;

	while (current != NULL)
{
	struct Node* temp = current;
	current = current->next;
	free(temp);
}
}
free(pHashArray);
}

//Function that parses input file to array
int parseData(char* inputFileName, struct RecordType** ppData)
{
FILE* inFile = fopen(inputFileName, "r");
int dataSz = 0;
int i, n;
char c;
struct RecordType *pRecord;
*ppData = NULL;

if (inFile)
{
fscanf(inFile, "%d\n", &dataSz);
*ppData = (struct RecordType*)malloc(sizeof(struct RecordType) * dataSz);
if (*ppData == NULL)
{
	printf("Cannot allocate memory\n");
	exit(-1);
}
for (i = 0; i < dataSz; ++i)
{
pRecord = *ppData + i;
fscanf(inFile, "%d ", &n);

pRecord->id = n;
fscanf(inFile, "%c ", &c);

pRecord->name = c;
fscanf(inFile, "%d ", &n);

pRecord->order = n;
}

fclose(inFile);
}

return dataSz;
}

//Function that prints records
void printRecords(struct RecordType pData[], int dataSz)
{
printf("\nRecords:\n");

for (int i = 0; i < dataSz; ++i)
{
	printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
}
printf("\n\n");
}

int main(void)
{
struct RecordType* pRecords;
int recordSz = 0;
int hashSz = 10; 

recordSz = parseData("input.txt", &pRecords);
printRecords(pRecords, recordSz);

//Initializes hash table
struct HashType* pHashArray = (struct HashType*)malloc(sizeof(struct HashType) * hashSz);
for (int i = 0; i < hashSz; ++i)
{
	pHashArray[i].head = NULL;
}

//Inserts records into hash table
for (int i = 0; i < recordSz; ++i)
{
	insertRecord(pHashArray, hashSz, pRecords[i]);
}

//Displays records in hash table
displayRecordsInHash(pHashArray, hashSz);

//Frees memory used by hash table
freeHashTable(pHashArray, hashSz);

//Frees memory for parsed array
free(pRecords);
return 0;
}
