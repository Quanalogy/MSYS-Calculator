//
// Created by Munke on 07-01-2016.
//
#include <iostream>
#include <string>


using namespace std;

#pragma once

class Hashing{
public:
	Hashing();
	int Hash(string key);
	void AddItem(string name, string description);
	int NumberOfItemsInIndex(int index);
	void PrintTable();
	void PrintItemsInIndex(int index);
	string FindDescription(string name);
	void RemoveItem(string name);
private:
	static const int tableSize = 40;

	struct item{
		string name;
		string drink;
		item* next;
	};

	item* HashTable[tableSize];


};

