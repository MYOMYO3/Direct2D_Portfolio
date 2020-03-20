#pragma once
#include <SmartPtr.h>
#include <Name.h>
#include <Debug.h>
#include <Maths.h>
#include <DataType.h>

#include "UpdaterBase.h"
#include "Actor.h"


class Component : public ControlBlock, public UpdaterBase, public DataType, public Name
{
private:
	std::wstring actorName;	//�ڽŰ� ����Ǿ��ִ� ������ �̸� ����뿡 ����

public:
	friend Actor;

	inline bool IsUpdate() override
	{
		return true == isUpdate && false == isDeath && true == GetActor()->IsUpdate();
	}
	inline bool IsDeath() override
	{
		return isDeath || true == GetActor()->IsDeath();
	}

private:
	Actor* actor;
	void SetActor(Actor* _Actor) 
	{ 
		actor = _Actor; 
		actorName = actor->GetName();
	}
public:
	Actor* GetActor()
	{
		return actor;
	}

private:
	Transform* transform;

public:
	Transform* GetTransform()
	{
		return transform;
	}

public:
	Scene* GetScene()
	{
		return GetActor()->GetScene();
	}

public:
	virtual void Init() {};
	void ComInit();

public:
	void DataCreate() {}

public:
	virtual void SceneChangeStart();

public:
	Component();
	~Component();
};

