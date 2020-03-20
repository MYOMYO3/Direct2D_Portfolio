#pragma once
#include <list>
#include <set>
#include <vector>

#include <SmartPtr.h>
#include <Name.h>

#include "UpdaterBase.h"



class Component;
class Transform;
class Scene;
class Actor final : public ControlBlock, public Name, public UpdaterBase
{
public:
	friend Scene;
	friend Transform;

#pragma region OverAcotrScript
private:
	bool SceneOverPossiblity;
	std::set<std::wstring> overSceneName_Set;

public:
	bool IsOverScene()
	{
		return SceneOverPossiblity;
	}

	void PossibleOverScene()
	{
		SceneOverPossiblity = true;
	}
	void ImPossibleOverScene()
	{
		SceneOverPossiblity = false;
	}

public:
	inline bool CheckSceneOver(const wchar_t* _NextScene)
	{
		return overSceneName_Set.end() != overSceneName_Set.find(_NextScene);
	}

	template<typename ...Rest>
	void OverScene(Rest ..._Arg)
	{
		PushOver(_Arg...);
	}

private:
	template<typename ...Rest>
	void PushOver(std::wstring _OverSceneName, Rest ..._Arg)
	{
		overSceneName_Set.insert(_OverSceneName);
		PushOver(_Arg...);
	}
	void PushOver() {}

public:
	bool IsOver() 
	{
		return 0 != overSceneName_Set.size();
	}
#pragma endregion




#pragma region POINTER
//Actor
private:
	Scene* scene;
	void SetScene(Scene* _Scene); 
public:
	Scene* GetScene() { return scene; }

//TRANSFORM
private:
	Transform* transform;
	void SetTransform(Transform* _Transform) { transform = _Transform; }
public:
	Transform* GetTransform() { return transform; }

#pragma endregion

#pragma region COMPONENT
private:
	std::list<My_Ptr<Component>> componentList;
	std::list<My_Ptr<Component>>::iterator componentStart;
	std::list<My_Ptr<Component>>::iterator componentEnd;

	std::list<My_Ptr<Component>>::iterator findStart;
	std::list<My_Ptr<Component>>::iterator findEnd;

public:
	template<typename COM, typename... Types>
	My_Ptr<COM> AddComponent(Types&&... _Args)
	{
		COM* NewCom = new COM();
		
		PushComponent(NewCom);
		NewCom->DataCreate(_Args...);
		return NewCom;
	}

	template<typename COM>
	My_Ptr<COM> GetComponent()
	{
		findStart = componentList.begin();
		findEnd = componentList.end();
		for (; findStart != findEnd; ++findStart)
		{
			// ������� ����� ��κ��� ������
			// �𸥴ٰ� �ϴ°�.
			// ��������� ���� �� �θ�
			// ����� ���� ���� ����.
			// ���δ�.
			// ���ø�.

			// ���⼭ h
			// �̳༮�� �����ߴ��� �𸥴ٴ� ������� ���Ҵ�.


			// �� �۾��� �����Ϸ��� ������ �ʿ��Ѱ�? 
			// (*FindStart)->IsType<COM>()
			// ���漱�� ������ ���� �ֳ�?
			// typeid����� ������� ����Ҽ� �ִ�.
			Component* P = (*findStart);

			if (true == CheckFunc(P, &typeid(COM)))
			{
				// �ܼ��� �������� ���԰� ���Ͽ���.
				// �̷��� �׳� ��� ����� ���� �ȴ�.
				// �׳༮�� �Լ��� ������ �˾ƾ� �ϴ� ��찡 �ƴϸ�
				// ��� ����� �ʿ����.
				// �����͸� ���ų� �����Ѵٴ� ������ 
				// ���漱�� ������ 

				// HPTR<HCOM> -> HPTR<HRENDER>
				return (COM*)P;
			}
		}
		return nullptr;
	}

	template<typename Component>
	std::vector<My_Ptr<Component>> GetComponentList()
	{
		std::vector<My_Ptr<Component>> returnList;

		findStart	= componentList.begin();
		findEnd		= componentList.end();

		for (; findStart != findEnd; ++findStart)
		{
			if (true == CheckFunc((*findStart), &typeid(Component)))
			{
				returnList.push_back((Component*)(*findStart).ptr);
			}
		}

		return returnList;
	}
	


private:
	bool CheckFunc(Component* _Com, const type_info* _TypeInfo);
	void PushComponent(Component* _Com);
#pragma endregion

public:
	void UpdateAfter()			override;
	void Update()				override;
	void UpdateBefore()			override;
	void FinalUpdate()			override;
	void RenderObjBefore()		override;
	//void RenderObj()			override;
	void RenderObjAfter()		override;
	void ColBefore()			override;
	//void Col()					override;
	void ColAfter()				override;
	void Release()				override;
	void ReleaseAfter()			override;

public:
	void SceneChangeStart();

	///////�θ��ڽı���

private:
	bool isChildReady;
	Actor* parentActor;

	std::list<My_Ptr<Actor>>::iterator	childAcotr_Start;
	std::list<My_Ptr<Actor>>::iterator	childAcotr_End;
	std::list<My_Ptr<Actor>>			childActor_List;

private:
	bool IsChildReady()
	{
		return isChildReady;
	}
	void ChildReadyUpdate();

public:
	void SetParent(My_Ptr<Actor>	_ParentActor);


private:
	enum GOOPY 
	{
		LITTLEGOOPY,
		MIDDLEGOOPY,
		BIGGOOPY,
		CROWNGOOPY,
		PIRANA,
		ULTRAGOOPY,
	};

	GOOPY goopy;

public:
	void SetGoopy(int _Value)
	{
		goopy = (GOOPY)_Value;
	}
	int GetGoopy()
	{
		return goopy;
	}

public:
	Actor();
	~Actor();
};

