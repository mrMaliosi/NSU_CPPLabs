#include <iostream>
#include <string>
#include <fstream>
#include "ErrorsHierarchy.h"

using namespace std;

typedef unsigned int ul;

typedef struct fileinfo {
	ul ByteRate;
	ul StartPos;
}fileinfo;

typedef struct protocol {
	int Second1;
	int Second2;
}protocol;

// ����������� ������� ����� ��������
class Converter {
public:
	virtual void use(const protocol &prot, ifstream &InputFile, ofstream &OutputFile, ifstream &MixerFile) = 0;
	fileinfo to_pos(ifstream& file)
	{
		file.seekg(22, ios::beg);			//�������� �� ���������� ����� �����
		short int NumChannels, BlockAllign, BitsPerSample;
		ul SampleRate, ByteRate;				//Byte Rate- ����� ���� � ����� �������
		file.read((char *)&NumChannels, sizeof(short int));
		file.read((char *)&SampleRate, sizeof(int));
		file.read((char *)&ByteRate, sizeof(int));
		file.read((char *)&BlockAllign, sizeof(short int));
		file.read((char *)&BitsPerSample, sizeof(short int));
		char letter;
		string word = ""; 
		for (ul i = 0; i < sizeof(int); ++i)
		{
			file.read((char *)&letter, sizeof(char));
			word += letter;
		}
		
		if (word != "LIST")
		{
			throw WavParsingError();
			//cout << word << " " << "����������!!! �� ��������� ������ ������������� �����, �� ��������� ����� ������� �� ������ ��������� � �� ������ ������� ��� 510 ���, ������ ��� ��� ����������� ������ ������� ���, ����� �������� �������� �����, ������� �� ��������!!! ��������! �������� �� ���� ������ ������������, ���������������� ��� ���������� � ����� �������, �������� ���������� ���������� � ��������� � ������! ��������.";
			//exit(1);
		}

		ul InfoSize;
		file.read((char *)&InfoSize, sizeof(int));
		ul pos = file.tellg();
		file.seekg(pos + InfoSize, ios::beg);

		word = "";
		for (int i = 0; i < sizeof(int); ++i)
		{
			file.read((char *)&letter, sizeof(char));
			word += letter;
		}
		if (word != "data")
		{
			throw WavParsingError();
			//cout << "����������!!! �� ��������� ������ ������������� �����, �� ��������� ����� ������� �� ������ ��������� � �� ������ ������� ��� 510 ���, ������ ��� ��� ����������� ������ ������� ���, ����� �������� �������� �����, ������� �� ��������!!! ��������! �������� �� ���� ������ ������������, ���������������� ��� ���������� � ����� �������, �������� ���������� ���������� � ��������� � ������! ��������.";
			//exit(1);
		}
		ul BytesSize;
		file.read((char *)&BytesSize, sizeof(ul));
		ul start = file.tellg();
		fileinfo FileInfo;
		FileInfo.ByteRate = ByteRate; 
		FileInfo.StartPos = start;
		return FileInfo;
	}

	string buffer(ifstream &file, fileinfo info)
	{
		string buf;
		char letter;
		for (ul i = 0; i < info.ByteRate; ++i)
		{
			file.read((char *)&letter, sizeof(char));
			buf += letter;
		}
		return buf;
	}

	void to_sec(ifstream &file, fileinfo info, ul second)
	{
		file.seekg(info.StartPos + info.ByteRate*second, ios::beg);
	}

	void file_info_copy(ifstream &InputFile, ofstream &OutputFile, fileinfo info)
	{
		InputFile.seekg(0);
		char Byte;
		for (ul i = 0; i < info.StartPos; ++i)
		{
			InputFile.read((char *)&Byte, sizeof(char));
			OutputFile.write((char *)&Byte, sizeof(char));
		}
	}

	void file_copy_to(ifstream &InputFile, ofstream &OutputFile, fileinfo info, ul pos)
	{
		InputFile.seekg(0);
		char Byte;
		for (ul i = 0; i < pos; ++i)
		{
			InputFile.read((char *)&Byte, sizeof(char));
			OutputFile.write((char *)&Byte, sizeof(char));
		}
	}

	void file_copy(ifstream &InputFile, ofstream &OutputFile)
	{
		char Byte;
		while (InputFile.read((char *)&Byte, sizeof(char)))
		{
			OutputFile.write((char *)&Byte, sizeof(char));
		}
	}
};

// ���������� ����� mute
class Mute : public Converter {
public:
	void use(const protocol &prot, ifstream &InputFile, ofstream &OutputFile, ifstream &MixerFile)
	{
		ul Second1 = prot.Second1;
		ul Second2 = prot.Second2;
		fileinfo FileInfo = to_pos(InputFile);
		file_copy_to(InputFile, OutputFile, FileInfo, FileInfo.StartPos + FileInfo.ByteRate*Second1);
		int BytesToWrite = (Second2 - Second1)*(FileInfo.ByteRate);
		char ZeroByte = (char)0;
		for (int i = 0; i < BytesToWrite; ++i)
		{
			OutputFile.put(ZeroByte);
			InputFile.ignore();
		}
		file_copy(InputFile, OutputFile);
	}
};

// ���������� ����� mix
class Mix : public Converter {
public:
	void use(const protocol &prot, ifstream &InputFile, ofstream &OutputFile, ifstream &MixerFile) {
		ul Second1 = prot.Second1;
		fileinfo FileInfo = to_pos(InputFile);
		file_copy_to(InputFile, OutputFile, FileInfo, FileInfo.StartPos + FileInfo.ByteRate*Second1);
		char Byte1, Byte2;
		to_pos(MixerFile);
		while (InputFile.read((char *)&Byte1, sizeof(char)))
		{
			if (MixerFile.read((char *)&Byte2, sizeof(char)))
			{
				Byte1 ^= Byte2;
			}
			OutputFile.write((char *)&Byte1, sizeof(char));
		}
	}
};

// ���������� ����� inverse
class Inverse : public Converter {
public:
	void use(const protocol &prot, ifstream &InputFile, ofstream &OutputFile, ifstream &MixerFile) {
		ul Second1 = prot.Second1;
		ul Second2 = prot.Second2;
		fileinfo FileInfo = to_pos(InputFile);
		file_copy_to(InputFile, OutputFile, FileInfo, FileInfo.StartPos + FileInfo.ByteRate*Second1);
		int BytesToInverse = (Second2 - Second1)*(FileInfo.ByteRate);
		char Byte;
		for (int i = 0; i < BytesToInverse; ++i)
		{
			InputFile.read((char *)&Byte, sizeof(char));
			Byte = ~Byte;
			OutputFile.write((char *)&Byte, sizeof(char));
		}
		file_copy(InputFile, OutputFile);
	}
};

// �������
class Factory {
public:
	// ����� �������� ��������
	virtual Converter* createConverter() = 0;

	// ����� ������������� ��������
	/*void useConverter(protocol prot) {
		Converter* converter = createConverter();
		converter->use(prot);
	}*/
};

// ���������� ���������� ������� ��� mute
class MuteFactory : public Factory {
public:
	Converter* createConverter() {
		return new Mute();
	}
};

// ���������� ���������� ������� ��� mix
class MixFactory : public Factory {
public:
	Converter* createConverter() {
		return new Mix();
	}
};

// ���������� ���������� ������� ��� mix
class InverseFactory : public Factory {
public:
	Converter* createConverter() {
		return new Inverse();
	}
};