
#include "FileStream.h"
#include <assert.h>

///////////////////////////////// BASE FILE

// FPen
FileStream::FileStream(const char* _FileName, const char* _Mode) : file(nullptr)
{
	// W�� �ƴ϶��
	//if (false == HIO::IsFile(_FileName))
	//{
	//	assert(false);
	//}
	fopen_s(&file, _FileName, _Mode);
}

FileStream::FileStream(const wchar_t* _FileName, const wchar_t* _Mode) : file(nullptr)
{
	//if (false == HIO::IsFile(_FileName))
	//{
	//	assert(false);
	//}

	_wfopen_s(&file, _FileName, _Mode);
}

FileStream::~FileStream()
{
	if (nullptr != file)
	{
		fclose(file);
	}
}

#pragma region BINARY
///////////////////////////////// WB
FileWBStream::FileWBStream(const char* _FileName)
	: FileStream(_FileName, "wb") {}
// : HFILESTREAM() // �̷������� �θ���� �����ڸ� 
// �ڽ��� �׻� ȣ���� �ְ� �־���.
FileWBStream::FileWBStream(const wchar_t* _FileName)
	: FileStream(_FileName, L"wb") {}

///////////////////////////////// RB
FileRBStream::FileRBStream(const char* _FileName)
	: FileStream(_FileName, "rb") {}
// : HFILESTREAM() // �̷������� �θ���� �����ڸ� 
// �ڽ��� �׻� ȣ���� �ְ� �־���.
FileRBStream::FileRBStream(const wchar_t* _FileName)
	: FileStream(_FileName, L"rb") {}
#pragma endregion

#pragma region TEXT
///////////////////////////////// WB
FileWTStream::FileWTStream(const char* _FileName)
	: FileStream(_FileName, "wt") {}
// : HFILESTREAM() // �̷������� �θ���� �����ڸ� 
// �ڽ��� �׻� ȣ���� �ְ� �־���.
FileWTStream::FileWTStream(const wchar_t* _FileName)
	: FileStream(_FileName, L"wt") {}

///////////////////////////////// RB
FileRTStream::FileRTStream(const char* _FileName)
	: FileStream(_FileName, "rt") {}
// : HFILESTREAM() // �̷������� �θ���� �����ڸ� 
// �ڽ��� �׻� ȣ���� �ְ� �־���.
FileRTStream::FileRTStream(const wchar_t* _FileName)
	: FileStream(_FileName, L"rt") {}
#pragma endregion

