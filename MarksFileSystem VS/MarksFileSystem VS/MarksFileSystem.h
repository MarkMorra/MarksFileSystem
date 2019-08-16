#pragma once
#include "BitArrays.h"
#include <math.h>
#include <stdio.h>   
#include <stdlib.h>


int bitsNeededForFAPPrefix(int size); //FAP = FewAsPossible
int bitsNeededForFAPSuffix(int size);

int intToFAPBitArrayPrefix(unsigned long long int num, BitArray *array);
int intToFAPBitArraySuffix(unsigned long long int num, BitArray *array);

int intToFAPBitArray(unsigned long long int num, BitArray *array);

class MFSDrive
{
public:
	MFSDrive();
	~MFSDrive();
	bool writeToDisk(void *data, long int address) //modify this function to call your function to write to the drive
	{
		int id = id_p;
	}

	bool readFromDisk(void *data, long int address) //modify this function to call your function to read from the drive
	{
		int id = id_p;
	}

	bool formatDrive(unsigned long long int size, unsigned int numberOfClusters);

private:
	int id_p;
	long long int size_p;
	

};

MFSDrive::MFSDrive()
{
}

MFSDrive::~MFSDrive()
{
}

bool MFSDrive::formatDrive(unsigned long long int size, unsigned int numberOfClusters)
{
	size_p = size;
	
	int clusterSize = floor(size / numberOfClusters);
	int clusterAddressSize = ceil(log2(numberOfClusters) / BYTE_SIZE);

	//Generate DIS
	//First must calculate length
	int DISLength = 0;
	
	DISLength += bitsNeededForFAPPrefix(size); //size_length
	DISLength += bitsNeededForFAPSuffix(size);

	DISLength += bitsNeededForFAPSuffix(size); //for disk address of FT1
	DISLength += bitsNeededForFAPSuffix(size); //for disk address of FT2
	DISLength += bitsNeededForFAPSuffix(size); //for disk address of DS

	DISLength += bitsNeededForFAPPrefix(numberOfClusters); //for $cluster_amount
	DISLength += bitsNeededForFAPSuffix(numberOfClusters);

	DISLength += bitsNeededForFAPPrefix(clusterSize); //for $cluster_size
	DISLength += bitsNeededForFAPSuffix(clusterSize);

	DISLength += bitsNeededForFAPPrefix(clusterAddressSize); //for $cluster_address_amount
	DISLength += bitsNeededForFAPSuffix(clusterAddressSize);

	DISLength += bitsNeededForFAPSuffix(clusterAddressSize); //for address of first non-valid cluster


	unsigned int FTSLength = clusterAddressSize * numberOfClusters;

	unsigned int FTS1Start = DISLength;
	unsigned int FTS2Start = FTS1Start + FTSLength;
	unsigned int FFSStart = FTS2Start + FTSLength;

	int bitsPerCluster = (size - FTSLength) / numberOfClusters;

	BitArray DISContents(DISLength);

	BitArray Temp;

	intToFAPBitArray(size, &Temp);
	DISContents.pushBack(&Temp);

	intToFAPBitArray(numberOfClusters, &Temp);
	DISContents.pushBack(&Temp);

	intToFAPBitArray(numberOfClusters, &Temp);
	DISContents.pushBack(&Temp);

	return false;
}

int bitsNeededForFAPPrefix(int num) //FAP = FewAsPossible
{
	return ceil(log2(num) / BYTE_SIZE) + 1;
}

int bitsNeededForFAPSuffix(int num) //FAP = FewAsPossible
{
	return ceil(log2(num));
}

//add function the converts int to FAP BitArray
int intToFAPBitArrayPrefix(unsigned long long int num, BitArray *array)
{
	int bits = bitsNeededForFAPPrefix(num);
	array->resize(bits);

	for (int i = 0; i < bitsNeededForFAPPrefix(num); i++) //size_length
	{
		array->pushBack(true);
	}

	array->pushBack(false);

	return bits;
}

//add function the converts int to FAP BitArray
int intToFAPBitArraySuffix(unsigned long long int num, BitArray *array)
{
	int bits = bitsNeededForFAPSuffix(num);
	array->resize(bits);


	unsigned long long int num_copy = num;

	for (int i = 0; i < bitsNeededForFAPPrefix(num) + bitsNeededForFAPSuffix(num); i++)
	{
		array->pushBack(num_copy & (~(unsigned long long int)0) >> 1);
		num_copy <<= 1;
	}

	return bits;
}

int intToFAPBitArray(unsigned long long int num, BitArray *array)
{
	BitArray Temp;

	array->resize(bitsNeededForFAPPrefix(num) + bitsNeededForFAPSuffix(num));

	intToFAPBitArrayPrefix(num, &Temp);

	array->pushBack(&Temp);

	intToFAPBitArraySuffix(num, &Temp);

	array->pushBack(&Temp);

	return array->length();
}

class MFSFolder
{
public:
	MFSFolder();
	~MFSFolder();

private:

};

MFSFolder::MFSFolder()
{
}

MFSFolder::~MFSFolder()
{
}

class MFSFile
{
public:
	MFSFile();
	~MFSFile();

private:
	int size;
	void *data;
};

MFSFile::MFSFile()
{
}

MFSFile::~MFSFile()
{
}


