#pragma once
#include <MyWindow.h>

#include "GraphicDevice.h"
#include "Scene.h"

class GameWindow : public Window
{
private:
	static std::map<std::wstring, My_Ptr<GameWindow>>::iterator gameWindow_Start;
	static std::map<std::wstring, My_Ptr<GameWindow>>::iterator gameWindow_End;
	static std::map<std::wstring, My_Ptr<GameWindow>> gameWindow_Map;
	static GameWindow* inst;

public:
	static My_Ptr<GameWindow> FindGameWindow(const wchar_t* _WindowName);
	static My_Ptr<GameWindow> CreateGameWindow(const wchar_t* _WindowName);
	
	//�̹� ������� �����츦 �޾Ƽ� ����  �����ϴ� �������� ����
	static My_Ptr<GameWindow> CreateGameWindow(const wchar_t* _WindowName, HWND _Hwnd);


	static GameWindow* Inst()
	{
		return inst;
	}

public:
	static void EngineLoop();
	static void __stdcall GameWindowUpdate();

	////////////////////���ο��� ���� ���� �����찡 �����Ѵ�

private:
	std::map<std::wstring, My_Ptr<Scene>> sceneMap;
	My_Ptr<Scene> nextScene;
	My_Ptr<Scene> currentScene;
	Scene* madeScene;

public:
	std::set<std::wstring> sceneNameSet;	//��� ���� �̸��� �������ִ� Set

public:
	void ChangeScene(const wchar_t* _SceneName);

#pragma region Variable Template
	template<typename ...Rest>
	void CreateScene(const wchar_t* _SceneName, Rest ..._Arg)
	{
		sceneNameSet.insert(std::set<std::wstring>::value_type(_SceneName));

		madeScene = new Scene();
		madeScene->SetWindow(this);
		madeScene->SetName(_SceneName);
		PushUpdater(_Arg...);
	}
	template<typename ...Rest>
	void PushUpdater(Scene::Updater* _Updater, Rest ..._Arg)
	{
		madeScene->AddUpdater(_Updater);
		PushUpdater(_Arg...);
	}
	void PushUpdater()
	{
		if (0 == sceneMap.size())	//first Created scene Become currentScene
		{
			nextScene = madeScene;
		}

		sceneMap.insert(std::map<std::wstring, My_Ptr<Scene>>::value_type(madeScene->GetName(), madeScene));

		madeScene = nullptr;
	}
#pragma endregion

	void SceneUpdate();

private:
	My_Ptr<GraphicDevice> device;

public:
	void CreateGraphicDevice();

private:
	GameWindow();
	~GameWindow();
};

