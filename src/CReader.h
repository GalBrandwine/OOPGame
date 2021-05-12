#pragma once
#include <iostream>
#include <cstdio>
#include <list>
#include <stdio.h>

using namespace std;


class CReader
{
public:
	CReader();

	int ReadUnitProperties(const char* fileName, list<list<int>*>* properties);
	int ReadUnit(const char* fileName, list<list<int>*>* units);

private:
	FILE* OpenFile(const char* fileName);
};

