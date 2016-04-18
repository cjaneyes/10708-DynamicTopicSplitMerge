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
	size_t pos = 0, posn, posnn, len = content.length();
	posn = content.find("\n", pos);
	int ndoc = atoi(content.substr(pos, posn - pos).c_str());
	size_t cdoc = 0;
	while (1)
	{
		posn = content.find("#year", pos);
		if (posn == string::npos)
			break;
		pos = posn + 9;
		cdoc++;
		year = atoi(content.substr(posn + 5, 4).c_str());
		if (year >= yearl && year <= yearr)
		{
			bool bWant = false;
			for (auto p = pos; p < len; p++)
				if (content[p] == '#' && p + 1 < len && content[p + 1] == '!')
				{
					// find wanted document
					bWant = true;
					posn = p + 2;
				}
				else if (content[p] == '\n' && p + 1 < len && content[p + 1] == '\n')
				{
					posnn = p;
					break;
				}
			if (bWant)
				extract[year - yearl].append(content.substr(posn, posnn - posn) + '\n');
			pos = posnn + 2;
		}
		if (!(cdoc % 1000))
			cout << double (cdoc) / ndoc * 100 << "%\n";
	}
	assert(cdoc == ndoc);
	for (size_t i = 0; i < ny; i++)
	{
		char fname[20];
		sprintf(fname, "/%u.txt", i + yearl);
		ofstream ofs(outfolder + fname);
		ofs << extract[i];
		ofs.close();
	}

	return 0;
}