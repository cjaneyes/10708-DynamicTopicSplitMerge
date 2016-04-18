#include<cstdlib>
#include<cstdio>
#include<cassert>
#include<string>
#include<fstream>
#include<iostream>
#include<vector>

using namespace std;

#define EST_FILE_SIZE 925281338

int main(int argc, char* argv[])
{
	string filename(argv[1]), outfolder(argv[2]);
	ifstream ifs(filename);
	if (!ifs)
		return 0;
	string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	ifs.close();
	int year, yearl = atoi(argv[3]), yearr = atoi(argv[4]);
	size_t ny = yearr - yearl + 1;
	size_t prealloc = EST_FILE_SIZE / ny;
	vector<string> extract(ny);
	for (auto &ey : extract)
		ey.reserve(prealloc);
	size_t pos = 0, posn, posnn;
	posn = content.find("\n", pos);
	int ndoc = atoi(content.substr(pos, posn - pos).c_str());
	size_t cdoc = 0;
	while (1)
	{
		if (cdoc == 10000)
			break;
		posn = content.find("#year", pos);
		if (posn == string::npos)
			break;
		pos = posn + 9;
		cdoc++;
		bool bWant = false;
		year = atoi(content.substr(posn + 5, 4).c_str());
		if (year >= yearl && year <= yearr)
		{
			posn = content.find("#!", pos);
			posnn = content.find("\n\n", pos);
			if (posn != string::npos && posn < posnn)
				// find wanted document
				extract[year - yearl].append(content.substr(posn + 2, posnn - posn - 2) + '\n');
			pos = __max(posn, posnn) + 2;
		}
		if (!(cdoc % 1000))
			cout << double (cdoc) / ndoc * 100 << "%\n";
	}
	assert(cdoc == ndoc);
	for (size_t i = 0; i < ny; i++)
	{
		char fname[20];
		sprintf(fname, "/%u.txt", i + yearl);
		ofstream out(outfolder + fname);
		out << extract[i];
		out.close();
	}

	return 0;
}