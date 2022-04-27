#include "Symbol.h"
#include <stdlib.h>
#include <iostream>

bool SymbolTableClass::Exists(const std::string& s)
{
	int size = this->varVector.size();
	for (int i = 0; i < size; i++)
	{
		if(this->varVector[i].label == s)
		{
			return true;
		}
	}
	return false;
}
bool SymbolTableClass::Exists(const std::string& s, int& index)
{
	int size = this->varVector.size();
	for (int i = 0; i < size; i++)
	{
		if(this->varVector[i].label == s)
		{
			index = i;
			return true;
		}
	}
	return false;
}
void SymbolTableClass::AddEntry(const std::string& s)
{
	if(!this->Exists(s))
	{
		Variable newVar;
		newVar.label = s;
		this->varVector.push_back(newVar);
	}
	else
	{
		std::cout << "Symbol " << s << " Already exists!\nQuitting..." << std::endl;
		exit(0);
	}
}
int SymbolTableClass::GetValue(const std::string& s)
{
	
	int index = 0;
	if(this->Exists(s,index))
	{
		
		return this->varVector[index].value;
	}
	else
	{
		std::cout << "Could not get value of Variable with label " << s << ".\n Probably does not exist, or was put in wrong." << std::endl; 
		exit(0);
	}

}
void SymbolTableClass::SetValue(const std::string& s, int v)
{
	int index = 0;
	if(this->Exists(s,index))
	{
		this->varVector[index].value = v;
	}
	else
	{
		std::cout << "Variable with label " << s << " could not be set to " << v <<".\nProbably does not exist, or was put in wrong." << std::endl;
		exit(0);
	}
}
int SymbolTableClass::GetIndex(const std::string& s)
{
	int index = 0;
	if(this->Exists(s,index))
	{
		
		return index;
	}
	std::cout << "Variable with label " << s << " could not be found, and therefore I am unable to get the index." << std::endl;
	return -1;
}
int SymbolTableClass::GetCount()
{
	return this->varVector.size();
}

