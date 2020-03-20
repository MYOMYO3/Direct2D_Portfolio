#pragma once
#include <iostream>
#include "IO.h"
// � ��� �־��ָ� ������ �����ϴ���
// �������� �ʴ��� �˷��ִ� �Լ��� ������?
// ������? 

class FileStream
{
protected:
	FILE* file;

public:
	bool IsOpen() 
	{
		return nullptr != file;
	}

public:
	FileStream(const char* _FileName, const char* _Mode);
	FileStream(const wchar_t* _FileName, const wchar_t* _Mode);
	virtual ~FileStream();
};

#pragma region BINARY
class FileWBStream : public FileStream
{
public:
	template<typename T>
	void operator <<(const T& _Data)
	{
		fwrite(&_Data, sizeof(T), 1, file);
	}

public:
	FileWBStream(const char* _FileName);
	FileWBStream(const wchar_t* _FileName);
	~FileWBStream() {}
};

class FileRBStream : public FileStream
{
public:
	template<typename T>
	void operator >>(T& _Data)
	{
		fread_s(&_Data, sizeof(T), sizeof(T), 1, file);
	}

public:
	FileRBStream(const char* _FileName);
	FileRBStream(const wchar_t* _FileName);
	~FileRBStream() {}
};
#pragma endregion

#pragma region TEXT
class FileWTStream : public FileStream
{
public:
	template<typename T>
	void operator <<(const T& _Data)
	{
		fwrite(&_Data, sizeof(T), 1, file);
	}

public:
	FileWTStream(const char* _FileName);
	FileWTStream(const wchar_t* _FileName);
	~FileWTStream() {}
};

class FileRTStream : public FileStream
{
public:
	template<typename T>
	void operator >>(T& _Data)
	{
		fread_s(&_Data, sizeof(T), sizeof(T), 1, file);
	}

public:
	FileRTStream(const char* _FileName);
	FileRTStream(const wchar_t* _FileName);
	~FileRTStream() {}
};

#pragma endregion



