#pragma once
#include "Resources.h" 


#ifdef X32
#ifdef DEBUGMODE
#pragma comment(lib, "..\\TPARTY\\X32\\Debug\\FW1FontWrapperD32.lib")
#elif RELEASEMODE
#pragma comment(lib, "..\\TPARTY\\X32\\Release\\FW1FontWrapperR32.lib")
#endif
#elif X64
#ifdef DEBUGMODE
#pragma comment(lib, "..\\TPARTY\\X64\\Debug\\FW1FontWrapperD64.lib")
#elif RELEASEMODE
#pragma comment(lib, "..\\TPARTY\\X64\\Release\\FW1FontWrapperR64.lib")
#endif
#endif

#include <FW1CompileSettings.h>
#include <FW1FontWrapper.h>

class Font : public Resources
{
private:
	IFW1Factory* fontFactory;
	IFW1FontWrapper* fontWrapper;

public:
	bool Create(const wchar_t* _FontName);
	bool DrawWorld(const wchar_t* _Name, float _FontSize, Vector4 _Position, Vector4 _Color, FW1_TEXT_FLAG _Flag);

	//��ũ����ǥ �������� �ϹǷ� ĳ���� �Ӹ��쿡 ĳ���θ��� ���� �ʹٴ��� �ϸ�
	// ���� ��ǥ�迡�� ��ũ�� ��ǥ��� ��ȯ�ؼ� ��ġ�� �־��ָ� �ɰ��̴�.
	void DrawUI(const wchar_t* _Name, float _FontSize, Vector4 _Position, Vector4 _Color, FW1_TEXT_FLAG _Flag = FW1_TOP);



public:
	Font();
	~Font();
};

