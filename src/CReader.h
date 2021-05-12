#pragma once
#include <iostream>
#include <cstdio>
#include <list>
#include <vector>
#include <stdio.h>
#include "utils/utils.h"
#include <string.h>

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

