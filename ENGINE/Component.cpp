#include "Component.h"



Component::Component()
{
	//CompareType();
}


Component::~Component()
{
}

void Component::ComInit()
{	
	transform	= actor->GetTransform();
}

void Component::SceneChangeStart()
{
	//���Ϳ� �ٲ���� ���õ� ������ ����ȴ�.
	//����� ��������
}