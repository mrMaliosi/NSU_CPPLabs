#include <iostream>
#include <string>
#include <fstream>
#include "parser.h"
#include "ErrorsHierarchy.h"
#include "Factory.h"

using namespace std;

int file_copy(ifstream& InputFile, ofstream& OutputFile)
{
	int count = 0;
	char Byte;
	while (InputFile.read((char *)&Byte, sizeof(char)))
	{
		OutputFile.write((char *)&Byte, sizeof(char));
		++count;
	}
	return count;
}

int main(int argc, char * argv[])
{
	//cout << argc << endl;
	setlocale(LC_CTYPE, "rus");
	try {
		if (argc < 2)
		{
			throw ArgumentsError();
		}
		else if (argc == 2)
		{
			if ((argv[1][0] != '-') && (argv[1][1] != 'h'))
			{
				throw ArgumentsError();
			}
			else
			{
				cout << "Ты просишь меня помощи, но делаешь это без уважения..." << endl;
			}
		}
		else if (argc <= 4)
		{
			throw ArgumentsError();
		}
		else if (argc > 4)
		{
			if ((argv[1][0] != '-') || (argv[1][1] != 'c'))
			{
				throw ArgumentsError();
			}
			ifstream config;
			config.open(argv[2]);
			if (config.is_open() == 0)
			{
				throw FileSearchError();
			}
			ifstream InputFile1;
			InputFile1.open(argv[4], ios::binary);
			if (InputFile1.is_open() == 0)
			{
				throw FileSearchError();
			}
			ofstream BufFile("buff.txt", ios::binary);
			if (BufFile.is_open() == 0)
			{
				throw FileSearchError();
			}
			cout << "Starting..." << endl;
			int count = file_copy(InputFile1, BufFile);
			cout << "Sizeof Data in file: " << count << " bytes." << endl;
			BufFile.close();
			InputFile1.close();
			Factory* muteFactory = new MuteFactory();
			Factory* mixFactory = new MixFactory();
			Factory* inverseFactory = new InverseFactory();

			Converter* mute = muteFactory->createConverter();
			Converter* mix = mixFactory->createConverter();
			Converter* inverse = inverseFactory->createConverter();

			while (!config.eof())
			{
				Parser p(config);
				protocol prot;
				if (p.data_.code == 1)
				{
					cout << "Starting of using converter 1..." << endl;
					ifstream InputFile("buff.txt", ios::binary);
					if (InputFile.is_open() == 0)
					{
						throw FileSearchError();
					}

					ofstream OutputFile(argv[3], ios::binary);
					if (OutputFile.is_open() == 0)
					{
						throw FileSearchError();
					}
					prot.Second1 = p.data_.data1;
					prot.Second2 = p.data_.data2;
					mute->use(prot, InputFile, OutputFile, InputFile);
					InputFile.close();
					OutputFile.close();
					cout << "Converter 1 done." << endl;
				}
				else if (p.data_.code == 2)
				{
					cout << "Starting of using converter 2..." << endl;
					ifstream InputFile("buff.txt", ios::binary);
					if (InputFile.is_open() == 0)
					{
						throw FileSearchError();
					}

					ofstream OutputFile(argv[3], ios::binary);
					if (OutputFile.is_open() == 0)
					{
						throw FileSearchError();
					}

					ifstream MixerFile(argv[p.data_.data1 + 3], ios::binary);
					if (MixerFile.is_open() == 0)
					{
						throw FileSearchError();
					}
					prot.Second1 = p.data_.data2;
					mix->use(prot, InputFile, OutputFile, MixerFile);
					InputFile.close();
					OutputFile.close();
					MixerFile.close();
					cout << "Converter 2 done." << endl;
				}
				else if (p.data_.code == 3)
				{
					cout << "Starting of using converter 3..." << endl;
					ifstream InputFile("buff.txt", ios::binary);
					if (InputFile.is_open() == 0)
					{
						throw FileSearchError();
					}

					ofstream OutputFile(argv[3], ios::binary);
					if (OutputFile.is_open() == 0)
					{
						throw FileSearchError();
					}
					prot.Second1 = p.data_.data1;
					prot.Second2 = p.data_.data2;
					inverse->use(prot, InputFile, OutputFile, InputFile);
					InputFile.close();
					OutputFile.close();
					cout << "Converter 3 done." << endl;
				}

				ifstream InputFile(argv[3], ios::binary);
				if (InputFile.is_open() == 0)
				{
					throw FileSearchError();
				}
				ofstream OutputFile("buff.txt", ios::binary);
				if (InputFile.is_open() == 0)
				{
					throw FileSearchError();
				}
				count = file_copy(InputFile, OutputFile);
				cout << "Sizeof Data in file: " << count << " bytes." << endl;
				InputFile.close();
				OutputFile.close();

			}
			config.close();
		}
	}
	catch (const Error& e)
	{
		e.exit_code();
	}

	return 0;
}
