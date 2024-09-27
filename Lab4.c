/*******************************************************************************
* File Name:		Lab4.c
* Description:		Implementation of a hash
*
*  Instructions:
*	- Use the skelton code in this file to implement a hash table.
*	- Implement the following functions:
*		hash_AddDataIntoHashTable()
*		hash_SearchForDataInHashTable()
*		hash_HashingFunction()
*	- After implemeting the above functions, the program should be able to ask the user for input values
*	  to add to the hash table. The program should be able of generating hash values for the inputs and
	  handle collisions. The program will then let the user check for values entered into the hash table and
	  provide its location in the table (if a match was found).

* Student Name: Amar Singh
* Student Number: 8935727
******************************************************************************
*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define INPUT_BUFFER_SIZE	200	// Local buffer used for adding data to the hash table
#define HASH_SIZE		    10  // Size of hash table to be used (this value is set small for testing purposes)

/**
 *  @brief Data structure used to keep track of hashed data
 */
typedef struct node {
	char* data;                 // Pointer to data stored in hash (you will need to malloc space for string to be stored)
	struct node* nextHashData;  // Pointer to next item in this hash bucket (or NULL if no more)
}node_t;

node_t* hashTable[HASH_SIZE];   // Empty hash table structure (note this is basically an arrary of linked list heads)

uint8_t hash_AddDataIntoHashTable(char* dataToAdd, uint8_t inputLength);
uint8_t hash_SearchForDataInHashTable(char* dataToSearch, uint8_t inputLength);
uint8_t hash_HashingFunction(char* input);

int main()
{
	char inputBuffer[INPUT_BUFFER_SIZE];
	uint8_t hashValue;
	// Initialize hash table
	for (int i = 0; i < HASH_SIZE; i++)
	{
		hashTable[i] = NULL;
	}

	while (1)
	{
		printf("Enter data to be added to the hash table, or type 'done' to break\n");
		scanf("%s", inputBuffer);

		if (strcmp(inputBuffer, "done") == 0)
		{
			break;
		}

		hashValue = hash_AddDataIntoHashTable(inputBuffer, strlen(inputBuffer));
		if (hashValue == HASH_SIZE)
		{
			printf("Error inserting into the hash table\n");
		}
		else
		{
			printf("Hash value: %u\n", hashValue);
		}

	}

	// Check if data is in the hash table
	while (1)
	{
		printf("Enter data to find, type 'exit' to break\n");
		scanf("%s", inputBuffer);

		if (strcmp(inputBuffer, "exit") == 0)
		{
			break;
		}

        	hashValue = hash_SearchForDataInHashTable(inputBuffer, strlen(inputBuffer));

        	if (hashValue == HASH_SIZE)
        	{
            		printf("%s not found in the hash table\n", inputBuffer);
        	}
        	else
        	{
            		printf("%s found in the hash table at index %u\n", inputBuffer, hashValue);
        	}
	}

	return 0;
}

/**
 * @brief Function to calculate a hash value to use for storing the data into the hash table
 * @param[in] input - a pointer to the data to be put into the hash table
 * @return HASH_SIZE on failure, otherwise hash value calculated
 */

uint8_t hash_HashingFunction(char* input)
{
	// Add code to create a hashed value here
	// Make sure if hash value is bigger than the table size, the value wraps around
       if(input == NULL)
          return HASH_SIZE;
       
    	uint8_t hashValue = 81;
    	int c;
    	
		while (c = *input++)
		{
		   hashValue = ((hashValue << 4) + hashValue) + c; 
		}

		hashValue = hashValue%HASH_SIZE;
		
		return hashValue;
	    
}

/**
 * @brief: Function to add a new entry to the hash table
 * @param[in] dataToAdd     - Pointer to the data to be added into the hash table
 * @param[in] inputLength   - Number of characters in the buffer being put into the hash table
 * @return HASH_SIZE on failure, otherwise hash value calculated
 */
uint8_t hash_AddDataIntoHashTable(char* dataToAdd, uint8_t inputLength)
{
	// Add code to put data into the hash table
	// Check if the value is already in the hash table
	if(dataToAdd == NULL || inputLength > INPUT_BUFFER_SIZE || inputLength == 0)
	    return HASH_SIZE;

	uint8_t index = hash_HashingFunction(dataToAdd);

    // Duplicate checking
	node_t *T = hashTable[index];
	node_t *Prev = NULL;
			while(T != NULL)
			{
				if((strcmp(T->data, dataToAdd) == 0))
				{
					printf("Duplicates are not allowed\n");
					return HASH_SIZE;
				}
                
				Prev = T;
				T = T->nextHashData;
			}
    
    
	// Memory Allocation for Node 
        node_t* temp = (node_t*)malloc(sizeof(node_t));
    
    	if(temp == NULL)
    	{
    		printf("\nMemory Allocation failed\n");
    		return HASH_SIZE;
    	}
    	
    // Memory Allocation for data which is a string   
    	char* currentData = (char*)malloc(sizeof(inputLength));
    
    	if(currentData == NULL)
    	{
    		printf("\nMemory Allocation failed\n");
			free(temp);
    		return HASH_SIZE;
    	}
    	strcpy(currentData,dataToAdd);
    	temp->data = currentData;
    	temp->nextHashData = NULL;
    	
		if(hashTable[index] == NULL)
    	   hashTable[index] = temp;
		
		//collision handling
		else
			Prev->nextHashData = temp; 
		 
    	return index;    
}

/**
 * @brief Function to search for data in the hash table
 * @param[in] dataToSearch  - Pointer to data to search for in the hash table
 * @param[in] inputLength   - Maxiumum number of characters that can be read
 * @return HASH_SIZE on failure, otherwise hash value calculated
 */
uint8_t hash_SearchForDataInHashTable(char* dataToSearch, uint8_t inputLength)
{
	// Add your code here
	if(dataToSearch == NULL || inputLength > INPUT_BUFFER_SIZE || inputLength == 0)
	   return HASH_SIZE;

	uint8_t index = hash_HashingFunction(dataToSearch);
	
	
	
	node_t *temp = hashTable[index];
	int count = 0;
	
	while(temp != NULL)
	{
		count++;
	    if((strcmp(temp->data, dataToSearch) == 0))
		{
           printf("%dth element of the list ", count);
	       return index;
		}
	    
	    temp = temp->nextHashData;
	}

    return HASH_SIZE;
}
