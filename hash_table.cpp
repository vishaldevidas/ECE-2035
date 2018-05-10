/*
 Student Name: Vishal Devidas
 Date: 31 March 2018

=======================
ECE 2035 Project 2-1:
=======================
This file provides definition for the structs and functions declared in the
header file. It also contains helper functions that are not accessible from
outside of the file.

FOR FULL CREDIT, BE SURE TO TRY MULTIPLE TEST CASES and DOCUMENT YOUR CODE.

===================================
Naming conventions in this file:
===================================
1. All struct names use camel case where the first letter is capitalized.
  e.g. "HashTable", or "HashTableEntry"

2. Variable names with a preceding underscore "_" will not be called directly.
  e.g. "_HashTable", "_HashTableEntry"

  Recall that in C, we have to type "struct" together with the name of the struct
  in order to initialize a new variable. To avoid this, in hash_table.h
  we use typedef to provide new "nicknames" for "struct _HashTable" and
  "struct _HashTableEntry". As a result, we can create new struct variables
  by just using:
    - "HashTable myNewTable;"
     or
    - "HashTableEntry myNewHashTableEntry;"

  The preceding underscore "_" simply provides a distinction between the names
  of the actual struct defition and the "nicknames" that we use to initialize
  new structs.
  [See Hidden Definitions section for more information.]

3. Functions, their local variables and arguments are named with camel case, where
  the first letter is lower-case.
  e.g. "createHashTable" is a function. One of its arguments is "numBuckets".
       It also has a local variable called "newTable".

4. The name of a struct member is divided by using underscores "_". This serves
  as a distinction between function local variables and struct members.
  e.g. "num_buckets" is a member of "HashTable".

*/

/****************************************************************************
* Include the Public Interface
*
* By including the public interface at the top of the file, the compiler can
* enforce that the function declarations in the the header are not in
* conflict with the definitions in the file. This is not a guarantee of
* correctness, but it is better than nothing!
***************************************************************************/
#include "hash_table.h"


/****************************************************************************
* Include other private dependencies
*
* These other modules are used in the implementation of the hash table module,
* but are not required by users of the hash table.
***************************************************************************/
#include <stdlib.h>   // For malloc and free
#include <stdio.h>    // For printf


/****************************************************************************
* Hidden Definitions
*
* These definitions are not available outside of this file. However, because
* the are forward declared in hash_table.h, the type names are
* available everywhere and user code can hold pointers to these structs.
***************************************************************************/
/**
 * This structure represents an a hash table.
 * Use "HashTable" instead when you are creating a new variable. [See top comments]
 */
struct _HashTable {
  /** The array of pointers to the head of a singly linked list, whose nodes
      are HashTableEntry objects */
  HashTableEntry** buckets;

  /** The hash function pointer */
  HashFunction hash;

  /** The number of buckets in the hash table */
  unsigned int num_buckets;
};

/**
 * This structure represents a hash table entry.
 * Use "HashTableEntry" instead when you are creating a new variable. [See top comments]
 */
struct _HashTableEntry {
  /** The key for the hash table entry */
  unsigned int key;

  /** The value associated with this hash table entry */
  void* value;

  /**
  * A pointer pointing to the next hash table entry
  * NULL means there is no next entry (i.e. this is the tail)
  */
  HashTableEntry* next;
};


/****************************************************************************
* Private Functions
*
* These functions are not available outside of this file, since they are not
* declared in hash_table.h.
***************************************************************************/
/**
* createHashTableEntry
*
* Helper function that creates a hash table entry by allocating memory for it on
* the heap. It initializes the entry with key and value, initialize pointer to
* the next entry as NULL, and return the pointer to this hash table entry.
*
* @param key The key corresponds to the hash table entry
* @param value The value stored in the hash table entry
* @return The pointer to the hash table entry
*/
static HashTableEntry* createHashTableEntry(unsigned int key, void* value) {

    HashTableEntry* newEntry = (HashTableEntry*)malloc(sizeof(HashTableEntry)); // allocate space for elements of the _HashTableEntry elements

    newEntry->key = key; // initilize the key 
    newEntry->value = value; // initialize the pointer
    newEntry->next = NULL; // point next to NULL

    return newEntry; // retrun the pointer to this HashTableEntry
}

/**
* findItem
*
* Helper function that checks whether there exists the hash table entry that
* contains a specific key.
*
* @param hashTable The pointer to the hash table.
* @param key The key corresponds to the hash table entry
* @return The pointer to the hash table entry, or NULL if key does not exist
*/
static HashTableEntry* findItem(HashTable* hashTable, unsigned int key) {
    
    unsigned int bucket; 
    bucket = hashTable->hash(key); // get which bucket the key is in
    
    HashTableEntry* thisNode = hashTable->buckets[bucket]; 

    while(thisNode){ // while the head isnt null
      if(thisNode->key == key) // walk the list to find the key
        return thisNode; // return the pointer to the Node with the key
      thisNode = thisNode->next;
    }
    
    return thisNode; // if it come this far that its NULL
}

/****************************************************************************
* Public Interface Functions
*
* These functions implement the public interface as specified in the header
* file, and make use of the private functions and hidden definitions in the
* above sections.
****************************************************************************/
// The createHashTable is provided for you as a starting point.
HashTable* createHashTable(HashFunction hashFunction, unsigned int numBuckets) {
  // The hash table has to contain at least one bucket. Exit gracefully if
  // this condition is not met.
  if (numBuckets==0) {
    printf("Hash table has to contain at least 1 bucket...\n");
    exit(1);
  }

  // Allocate memory for the new HashTable struct on heap.
  HashTable* newTable = (HashTable*)malloc(sizeof(HashTable));

  // Initialize the components of the new HashTable struct.
  newTable->hash = hashFunction;
  newTable->num_buckets = numBuckets;
  newTable->buckets = (HashTableEntry**)malloc(numBuckets*sizeof(HashTableEntry*));

  // As the new buckets are empty, init each bucket as NULL.
  unsigned int i;
  for(i=0; i<numBuckets; ++i) {
    newTable->buckets[i] = NULL;
  }

  // Return the new HashTable struct.
  return newTable;
}

void destroyHashTable(HashTable* hashTable) {

    unsigned int numBuckets = hashTable->num_buckets; // get the number of bucktes
    HashTableEntry*  tempNode; 
    unsigned int i;
    for(i=0; i<numBuckets; ++i){ // loop through the buckets
      
      while(hashTable->buckets[i]){ // loop until you hit null

        tempNode = hashTable->buckets[i]; 
        hashTable->buckets[i] = tempNode->next; // make the next the new head

        free(tempNode->value); // free the old head value 
        free(tempNode); // free the old head node
      }

    } 
    
    free(hashTable->buckets); // free the buckets 
    free(hashTable); // free the point to the enitre table  
}

void* insertItem(HashTable* hashTable, unsigned int key, void* value) {
 
        HashTableEntry* thisNode; 
    if((thisNode = findItem(hashTable,key))){ // if the key is found
      void* temp = thisNode->value; // store the old  value
      thisNode->value = value; // overwritte the old value with the new value
      return temp; // return the old value
    }
    
    thisNode = createHashTableEntry(key, value); // Create a new node
    unsigned int bucket; 
    bucket = hashTable->hash(key); // get the bucket in the key is located

    thisNode->next = hashTable->buckets[bucket]; // point the next to the head
    hashTable->buckets[bucket] = thisNode; // point the head to the new node

    return NULL; // return null since the key was not found
}

void* getItem(HashTable* hashTable, unsigned int key) {
    
    HashTableEntry* thisNode; 
    
    if((thisNode = findItem(hashTable,key))) return thisNode->value; // if key found than return value
    return NULL; // if key not found return null
    
}

void* removeItem(HashTable* hashTable, unsigned int key) {
    
    unsigned int bucket;
    bucket = hashTable->hash(key); // the the bucket where the key is located
    
    HashTableEntry* thisNode = hashTable->buckets[bucket]; // thisNode is the head of the Linked list
    HashTableEntry* removeNode; 
    void* DeletedValue;

    if(!thisNode) return NULL; // if the head is null retrun null
    
    if(thisNode->key == key){ // if the head the desired key
      DeletedValue = thisNode->value; // save the value for later 
      hashTable->buckets[bucket] =  thisNode->next; // make the next node the head  
      free (thisNode); // free the old head 
      return DeletedValue; // return the saved value
    }

    while(thisNode->next){ // if the head is not the desired key, walk the list
      if(thisNode->next->key == key){ // look for the node which is before the desired node
         
        removeNode = thisNode->next; // save the desired node for later
        DeletedValue = removeNode->value; // save the value for later
        thisNode->next = thisNode->next->next; // point the next to the node after next because next will be freed
        
        free(removeNode); // free the desired node
        return DeletedValue; // return the saved value
      }
      
      thisNode = thisNode->next; // walk the list
    }
    
    return NULL; // if the key is not found return null
    
}

void deleteItem(HashTable* hashTable, unsigned int key) {
    
    void* removedValue = removeItem(hashTable,key); // remove frees the space and returns the value 
    free(removedValue); // freeing the value also completely "deletes" the node 
            
}
