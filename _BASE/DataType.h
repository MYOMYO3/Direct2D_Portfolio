#pragma once
#include <typeinfo>

// C++ 
// RTTI ���� Ÿ�� Ÿ�� ����
// RTTI ���� Ÿ�� Ÿ�� ���̵�Ƽ���̼�
// �����ڰ� �ִ�.
// type_info Data = typeid(�ڷ��� Ȥ�� �ĺ���)

class DataType
{
private:
	const type_info* info;

public:
	void TypeSetting();


public:
	bool CompareType(const type_info* _Info)
	{
		return info == _Info;
	}

	template<typename T>
	bool CompareType()
	{
		return info == &typeid(T);
	}

	bool CompareType(const DataType& _Name)
	{
		return info == _Name.info;
	}

public:
	DataType();
	virtual ~DataType();
};

