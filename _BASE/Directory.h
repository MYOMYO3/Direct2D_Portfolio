#pragma once
#include <vector>
#include <string>

#include "IO.h"
#include "File.h"
//���丮 ����, �̵�, �̸��ٲٱ�, ����� �� ������ ���� �Ϲ����� �۾����� DIrectoryŬ������ ���


class Directory: public IO
{
public:
	void ReplaceToParentPath();
	bool MoveDirectory(const wchar_t* _FolderName);
	bool ExistFileInDir(const wchar_t* _FileName);
	
public:	
	std::wstring GetFolderName();
	std::vector<std::wstring> GetDirectories();
	void GetAllFileName(std::vector<File>& _FileNames, const wchar_t* _FileExt);


public:
	Directory(const Directory& _Other); // �����α׷��� ����� ��ġ�� �ڽ��� ��η� ����
	Directory(const wchar_t* _Name);
	Directory();						// ��ΰ� �����Ȱ� Directory(const wchar_t* _Name);
	~Directory();
};

