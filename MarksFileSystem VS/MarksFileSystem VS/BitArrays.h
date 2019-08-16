#pragma once

#include <stdint.h>
#include <math.h>
#include <stdlib.h>

#define BYTE_SIZE 8

typedef unsigned char Byte;
#define BYTE_MAX (Byte)255

class BitArray
{
public:
	BitArray();
	BitArray(int bits);
	~BitArray();

	int resize(int bits)
	{
		if (data != NULL) 
		{ 
			free(data); 
			data == NULL;
		}

		_length = bits;
		numOfBytes = (_length / BYTE_SIZE) + ((_length % BYTE_SIZE) == 0 ? 0 : 1);

		data = (Byte*)malloc(bits);

		for (int i = 0; i < numOfBytes; i++)
		{
			data[i] = 0;
		}

		return _length;
	}

	void setBit(int pos, bool val)
	{
		if (pos >= _length)
		{
			throw "BitArray.setBit() pos was too high";
		}

		int byte = pos / BYTE_SIZE;
		int bit = pos % BYTE_SIZE;

		if (val == false)
		{
			data[byte] = data[byte] & ~(Byte)powf(2, bit);
		}
		else
		{
			data[byte] = data[byte] | (Byte)powf(2, bit);
		}

	}

	bool getBit(int pos)
	{
		if (pos >= _length)
		{
			throw "BitArray.getBit() pos was too high";
		}

		int byte = pos / BYTE_SIZE;
		int bit = pos % BYTE_SIZE;

		return ((int*)data)[byte] & (int)powf(2, bit);

	}

	void seyByte(int pos, Byte val)
	{
		if (pos >= _length / 8)
		{
			throw "BitArray.setByte() pos was too high";
		}

		data[pos] = val;
	}

	Byte getByte(int pos)
	{
		if (pos >= _length / 8)
		{
			throw "BitArray.getByte() pos was too high";
		}

		return data[pos];
	}

	void pushFront(bool val)
	{
		bool push = val, pop = val;
		for (int i = 0; i < numOfBytes; i++)
		{
			push = pop;
			pop = data[i] & (Byte)1;
			data[i] >> 1;
			if (push == true)
			{
				data[i] |= ~(BYTE_MAX >> 1);
			}

		}
	}

	void pushFront(BitArray *vals)
	{
		bool push, pop;
		for (int x = 0; x < vals->length(); x++)
		{
			push = vals->getBit(vals->length() - (x + 1));
			pop = push;

			for (int i = 0; i < numOfBytes; i++)
			{
				push = pop;
				pop = data[i] & (Byte)1;
				data[i] >> 1;
				if (push == true)
				{
					data[i] |= ~(BYTE_MAX >> 1);
				}

			}
		}

	}

	void pushBack(bool val)
	{
		bool push = val, pop = val;
		for (int i = numOfBytes - 1; i >= 0; i--)
		{
			push = pop;
			pop = data[i] & ~(BYTE_MAX >> 1);
			data[i] << 1;
			if (push == true)
			{
				data[i] |= (Byte)1;
			}

		}
	}

	void pushBack(BitArray *vals)
	{
		bool push, pop;
		for (int x = 0; x < vals->length(); x++)
		{
			push = vals->getBit(x);
			pop = push;

			for (int i = numOfBytes - 1; i >= 0; i--)
			{
				push = pop;
				pop = data[i] & ~(BYTE_MAX >> 1);
				data[i] << 1;
				if (push == true)
				{
					data[i] |= (Byte)1;
				}

			}
		}
	}

	int length()
	{
		return _length;
	}

private:
	Byte *data;
	int _length;
	int numOfBytes;
};

BitArray::BitArray()
{
	_length = 0;
}

BitArray::BitArray(int bits)
{
	resize(bits);
}

BitArray::~BitArray()
{
	if (data != NULL) 
	{ 
		free(data); 
		data = NULL;
	}

	
}
