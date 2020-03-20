#pragma once
// io input output�� ����
// ��������� �Լ��� �ƴϸ� ������
// ��κ� io ��� 
// img Texture

#include <iostream>
#include <io.h>

#include <string>




//System.IO ���� �����̽����� ���� �� ������ ��Ʈ���� ���� 
//�б� �� ���⸦ ����ϴ� ���İ� �⺻ ���� �� ���͸� ������ �����ϴ� ������ ���ԵǾ� �ֽ��ϴ�.
class IO	//input output
{
public:
	static bool ExistFile(const char*    _FileName);
	static bool ExistFile(const wchar_t* _FileName);

protected:
	std::wstring fullPath;

public:
	void PathSetting(const wchar_t* _Path);
	void PathSetting(const std::wstring& _Path);

public:
	bool FileCheck();

public:
	inline const wchar_t* GetFullPath()
	{
		return fullPath.c_str();
	}

	inline std::wstring GetFullPathString()
	{
		return fullPath;
	}

	inline int GetFullPathSize()
	{
		return (int)fullPath.size();
	}

protected:
	std::wstring GetFileName();

public:
	IO() {}
	~IO() {}
};

