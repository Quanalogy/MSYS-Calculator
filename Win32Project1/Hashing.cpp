//
// Created by Munke on 07-01-2016.
//
#include "stdafx.h"
#include "Hashing.h"

Hashing::Hashing() {

	for (int i = 0; i < tableSize; i++){
		HashTable[i] = new item;
		HashTable[i]->name = "empty";
		HashTable[i]->drink = "empty";
		HashTable[i]->next = NULL;
	}
}

int Hashing::Hash(string key){
	int hash = 0;
	int index;


	for (int i = 0; i < key.length(); i++){
		hash = (hash + (int)key[i]) * 1; //gemmer ascii værdien for bogstavet på pladsen i
	}

	index = hash % tableSize;   //laver modulus, dette sørger for at vi ikke har
	// elementer på plads større end tablesize

	return index;
}


void Hashing::AddItem(string name, string drink) {
	int index = Hash(name);

	if (HashTable[index]->name == "empty"){//it's the first item, the default
		HashTable[index]->name = name;
		HashTable[index]->drink = drink;

	}
	else { // er det et nyt item og vi skal initialisere den
		item* Ptr = HashTable[index];
		item* nPtr = new item;
		nPtr->name = name;
		nPtr->drink = drink;
		nPtr->next = NULL;
		while (Ptr->next != NULL){ // når den er null så er vi ved det sidste element
			Ptr = Ptr->next; // nu peger den til det sidste element
		}
		Ptr->next = nPtr; // nu peger vi på det nyeste element
	}
}

int Hashing::NumberOfItemsInIndex(int index) {
	int count = 0;
	if (HashTable[index]->name == "empty"){ //det er default og får derfor 0 tilbage
		return count;
	}
	else { // det er en vi har givet en værdi
		count++;
		item *Ptr = HashTable[index];
		while (Ptr->next != NULL){ //while we have valid items
			count++;
			Ptr = Ptr->next;
		}
	}
	return count;
}


void Hashing::PrintTable() {
	int number;
	for (int i = 0; i < tableSize; ++i) {
		number = NumberOfItemsInIndex(i);
		cout << "----------------------\n" << "index: " << i << endl;
		cout << "Element: " << HashTable[i]->name << endl;
		cout << "Description: " << HashTable[i]->drink << endl;
		cout << "#items = " << number << endl;
		cout << "----------------------" << endl;
	}
}


void Hashing::PrintItemsInIndex(int index) {
	item* Ptr = HashTable[index];
	if (Ptr->name == "empty"){
		cout << "Bucket: " << index << " is empty" << endl;
	}
	else {
		cout << "index: " << index << " contains the following items:\n" << endl;
		while (Ptr != NULL){
			cout << "----------------------\n" << endl;
			cout << "Element: " << Ptr->name << endl;
			cout << "Description: " << Ptr->drink << endl;
			cout << "----------------------" << endl;
			Ptr = Ptr->next;
		}
	}
}


string Hashing::FindDescription(string name) {
	int index = Hash(name);
	bool foundName = false;
	string drink;
	string response;
	item* Ptr = HashTable[index];
	while (Ptr != NULL){
		if (Ptr->name == name){
			foundName = true;
			drink = Ptr->drink;
		}
		Ptr = Ptr->next;
	}
	if (foundName){
		response = name + "\n" + drink;
		cout << "Description: " << drink << endl;
	}
	else {
		cout << "Didn't find " << name << " in the hashtable!" << endl;
		response = name + " was not found in the database";
	}
	return response;
}


void Hashing::RemoveItem(string name) {
	int index = Hash(name);

	item *delPtr;
	item *Ptr1;
	item *Ptr2;

	//Case 0
	// The bucket we are looking into is empty
	if (HashTable[index]->name == "empty" && HashTable[index]->drink == "empty"){
		cout << "The element: " << name << " was not found in the hashtable";
	}
	else if (HashTable[index]->name == name && HashTable[index]->next == NULL) {    //Case 1
		// Only 1 item contained in the bucket and that item has matching name
		HashTable[index]->name = "empty";
		HashTable[index]->drink = "empty";
		cout << "The element: " << name << " was removed from the hashtable" << endl;

	}
	else if (HashTable[index]->name == name){ //Case 2
		// Match is located in the first item in the bucket, but there are
		// more items in the bucket
		delPtr = HashTable[index];
		HashTable[index] = HashTable[index]->next;
		delete delPtr;

		cout << "The element: " << name << " was removed from the hashtable" << endl;
	}
	else { //Case 3
		// The bucket cointains items but first item is not a match
		Ptr1 = HashTable[index]->next;
		Ptr2 = HashTable[index]; // ptr2 er hele tiden 1 bagved

		while (Ptr1 != NULL && Ptr1->name != name){
			Ptr2 = Ptr1;
			Ptr1 = Ptr1->next;
		} // Case 3.1 - No Match
		if (Ptr1 == NULL){
			cout << "The element: " << name << " was not found in the hashtable";
		}
		else { // Case 3.2 - Match is found
			delPtr = Ptr1;
			Ptr1 = Ptr1->next;
			Ptr2->next = Ptr1;

			delete delPtr;
			cout << "The element: " << name << " was removed from the hashtable" << endl;

		}
	}

}