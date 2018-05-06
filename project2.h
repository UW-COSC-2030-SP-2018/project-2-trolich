#include<vector>
#include<string>
using namespace std;

int nthHash(unsigned int n, int hash, int filterSize);
int MyHash(const string word);

struct BloomFilter {

public:
	BloomFilter(int size, int num) : bits(size), numHashes(num)
	{
	}

	void add(const string data)
	{
		int hashValue = MyHash(data);

		for (int n = 0; n < numHashes; n++)
		{
			bits[nthHash(n, hashValue, bits.size())] = true;
		}
	}

	bool contains(const string data) const
	{
		int hashValue = MyHash(data);
		for (int n = 0; n < numHashes; n++)
		{
			if (!bits[nthHash(n, hashValue, bits.size())])
				return false;
		}
		return true;
	}


private:
	vector<bool> bits;
	int numHashes;

};

int nthHash(unsigned int n, int hash, int filterSize)
{
	int returnval = (hash * hash / (n+1) % filterSize);
	return returnval;
}

int MyHash(const string word)
{
	int a = 102938213;
	int b = 291829421;

	int hash = 0;
	for (unsigned int i = 0; i < word.length(); i += 2)
	{
		hash += word[i] * a + word[i + 1] * b;
		hash *= a * b;
	}
	return hash;
}