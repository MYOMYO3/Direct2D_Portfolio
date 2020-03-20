#pragma once
#include "IO.h"
#include <vector>


//���� ������ �ۼ�, ����, ����, �̵� �� ���⿡ ���� �޼��带 ����
//FILESTREAM��ü�� ����µ� �������ش�

class File : public IO
{
public:
	//Ȯ���� �־��ָ� true
	bool CheckExtension(const wchar_t* _Ext);	//Ȯ���� üũ
	std::wstring GetFileName();

	std::vector<std::wstring> GetAllFileName();

public:	
	File(const wchar_t* _FileName);
	File(const std::wstring& _Path);
	File();
	~File();
};

