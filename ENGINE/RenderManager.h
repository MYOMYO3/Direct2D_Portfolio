#pragma once
#include <map>

#include "Camera.h"
#include "RenderPath.h"

//��� ���������� ����������
//��������	render�Լ��� ȣ���ϴ� ������ �����ϰ�
//ī�޶� ������ ����� ������ ���� ���ִ°��� �������̴�
//������Ʈ�� �ʿ伺�� �����.
//ī�޶�/ Rnder::FInDCAMERA(L"");
//����İ� ������Ʈ ����� ������ �ȵ���
//ī�޶� ���������� �ϴ°ž�?
//���� �̰� ���ְ� �ִ°ž�?
//������ �ϴ� �׷�
//ī�޶�
//������
//HCAM�� ����� ���� � ������ �η��鸸 �����ش�

class Mesh;
class RenderManager;
class Instancing
{
public:
	friend RenderManager;

private:
	RenderPath	renderPath;
	const type_info* dataType;
	int dataSize;
	int dataCount;
	std::vector<char>	data;	//�ν��Ͻ̿� �����͸� ��Ƶδ°�
	My_Ptr<Mesh> mesh;

public:
	void SetRenderPath(const RenderPath& _RenderPath)
	{
		renderPath = _RenderPath;
	}

public:
	void SetMesh(const wchar_t* _Name);
};


class Camera;
class Scene;
class Renderer;
class RenderManager
{
public:
	enum SORTTYPE
	{
		NONE, 
		Z,Y,X,
		CAMZ, CAMY, CAMX,
		MAX,
	};

public:
	friend Camera;
	friend Renderer;
	friend Scene;

private:
	Scene* scene;

private:
	std::map<int, std::list<My_Ptr<Camera>>>::iterator	camListMap_Begin;
	std::map<int, std::list<My_Ptr<Camera>>>::iterator	camListMap_End;
	std::map<int, std::list<My_Ptr<Camera>>>			camListMap;
	std::map<int, SORTTYPE>								sortType;

	std::list<My_Ptr<Camera>>::iterator					camList_Begin;
	std::list<My_Ptr<Camera>>::iterator					camList_End;
	std::list<My_Ptr<Camera>>							camList;

private:
	void CollectCamForRender(int _Order);
	void SortByCameraOrder();

private:
	void PushCamera(const My_Ptr<Camera>& _CAM);

private:
	// ����
	// 0�� �������� ��������.
	// 1�� �׷��� �ִٸ�
	std::map<int, std::list<My_Ptr<Renderer>>>::iterator renderListMap_Begin;
	std::map<int, std::list<My_Ptr<Renderer>>>::iterator renderListMap_End;
	std::map<int, std::list<My_Ptr<Renderer>>> renderList_Map;

	std::list<My_Ptr<Renderer>>::iterator renderList_Begin;
	std::list<My_Ptr<Renderer>>::iterator renderList_End;

private:
	void PushRenderer(const My_Ptr<Renderer>& _Renderer);


public:
	void Render();
	void Release();
	void OverRendererRelease();
//SORT FUNCTION
public:
	static bool ZSort(const My_Ptr<Renderer>&, const My_Ptr<Renderer>&);
	static bool YSort(const My_Ptr<Renderer>&, const My_Ptr<Renderer>&);
	static bool XSort(const My_Ptr<Renderer>&, const My_Ptr<Renderer>&);
	static bool (*sortFunc[MAX])(const My_Ptr<Renderer>&, const My_Ptr<Renderer>&);

	//INSTANCING
private:
	static std::map<std::wstring, My_Ptr<Instancing>>::iterator findInstIter;
	static std::map<std::wstring, My_Ptr<Instancing>> instMap;

public:
	static My_Ptr<Instancing> FindInstancing(const wchar_t* _Name)
	{
		findInstIter = instMap.find(_Name);
		
		if (findInstIter == instMap.end())
		{
			return nullptr;
		}
		return findInstIter->second;
	}

	template<typename  T>
	static void CreateInstancing(const wchar_t* _Name, const wchar_t* _MeshName, const RenderPath& _Path, UINT _InstCount = 1000)//�ڵ�Ȯ���ϰ� ����ڴ�.
	{
		My_Ptr<Instancing> inst = FindInstancing(_Name);
		
		if (nullptr != inst)
		{
			BOOM;
			return;
		}

		inst = new Instancing();
		inst->SetMesh(_MeshName);
		inst->SetRenderPath(_Path);

		inst->dataType = &typeid(T);
		inst->dataSize = sizeof(T);
		inst->dataCount = _InstCount;
		inst->data.resize(inst->dataSize * inst->dataCount);

		instMap.insert(std::map<std::wstring, My_Ptr<Instancing>>::value_type(_Name, inst));
	}

public:
	RenderManager(Scene* _Scene) ;
	~RenderManager();
};

