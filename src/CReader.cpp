#pragma warning (disable : 4996)
#include "CReader.h"


CReader::CReader()
{
}

int CReader::ReadUnit(const char* fileName, list<list<int>*>* units)
{
	FILE* pFile;
	char tempStr[2000];
	char* temp;

	pFile = OpenFile(fileName);

	if (pFile == nullptr)
	{
		return 0;
	}

	while (fgets(tempStr, 2000, pFile) != NULL)
	{
		if (tempStr[0] != '#' && tempStr[0] != '\0' && tempStr[0] != '\n')
		{
			list<int>* unit = new list<int>();

			temp = strtok(tempStr, ",:");
			while (temp != NULL)
			{
				int attribute = atoi(temp);
				unit->push_back(attribute),
				temp = strtok(NULL, ",:");
			}

			units->push_back(unit);
		}
	}

	fclose(pFile);

	return 1;
}

int CReader::ReadUnitProperties(const char* fileName, list<list<int>*>* properties)
{
	FILE* pFile;
	char tempStr[2000];
	char* temp;

	pFile = OpenFile(fileName);

	if (pFile == nullptr)
	{
		return 0;
	}

	while (fgets(tempStr, 2000, pFile) != NULL)
	{
		if (tempStr[0] != '#' && tempStr[0] != '\0' && tempStr[0] != '\n')
		{
			list<int>* property = new list<int>();

			temp = strtok(tempStr, ",");
			while (temp != NULL)
			{
				int attribute = atoi(temp);
				property->push_back(attribute),
				temp = strtok(NULL, ",");
			}

			properties->push_back(property);
		}
	}

	fclose(pFile);

	return 1;
}


FILE* CReader::OpenFile(const char* fileName)
{
	FILE* pFile = fopen(fileName, "r");
	if (pFile == NULL)
	{
		cout << "File Openning Failed!" << endl;
		return nullptr;
	}

	return pFile;
}
