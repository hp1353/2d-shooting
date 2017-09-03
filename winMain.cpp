#include "stdafx.h"
#include "gameStudy.h"

//�������� ������
HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse = { 0, 0 };
POINT_FLOAT _ptMousef = { 0.f, 0.f };

gameStudy _gs;

/* #### �Լ� ���� ������ #### */
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam, int nCmdShow)
{
	_hInstance = hInstance;

	//MSG : �ü������ �����ϴ� �޽��� ������ �����ϱ� ���� ����ü
	MSG message;

	//WNDCLASS : �������� ������ �����ϱ� ���� ����ü
	WNDCLASS wndClass;

	wndClass.cbClsExtra = 0;             //Ŭ���� ���� �޸�
	wndClass.cbWndExtra = 0;             //������ ���� �޸�
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //��׶���
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);   //Ŀ��
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //������
	wndClass.hInstance = hInstance;                   //�ν��Ͻ�
	wndClass.lpfnWndProc = (WNDPROC)WndProc;          //������ ���ν���
	wndClass.lpszClassName = WINNAME;                 //Ŭ�����̸�
	wndClass.lpszMenuName = NULL;                     //�޴��̸�
	wndClass.style = CS_HREDRAW | CS_VREDRAW;         //������ ��Ÿ��

	//������ Ŭ���� ���
	RegisterClass(&wndClass);

	//������ ����
	_hWnd = CreateWindow(
		WINNAME,			//������ Ŭ������ �̸�
		WINNAME,			//������ Ÿ��Ʋ�� �̸�
		WINSTYLE,			//������ ��Ÿ��
		WINSTARTX,			//������ ȭ����ǥ x
		WINSTARTY,			//������ ȭ����ǥ y
		WINSIZEX,			//������ ȭ����ǥ width
		WINSIZEY,			//������ ȭ����ǥ height
		NULL,				//�θ� ������
		(HMENU)NULL,		//�޴��ڵ�
		hInstance,			//�ν��Ͻ� ����
		NULL);				//������ �� �ڽ� �����츦 �����ϸ�
							//�������ֵ� �׷��� ������ NULL

	//ȭ�� �۾� ������ ���� ���
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);
	

	//ȭ�鿡 ������ �����ش�
	ShowWindow(_hWnd, nCmdShow);

	if (FAILED(_gs.init()))
	{
		//gameStudy �ʱ�ȭ ���н� �ٷ� ��������
		return 0;
	}

	
	while (true) //���ӿ�
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			TIMEMANAGER->update(100.f);
			_gs.update();
			_gs.render();
		}
	}

	

	//�޽��� ť�� �޽����� ������ �޽��� ó��...
	//while (GetMessage(&message, 0, 0, 0)) //�Ϲ� ���α׷���
	//{
	//	TranslateMessage(&message);
	//	DispatchMessage(&message);
	//}

	//gameStudy �޸� ����
	_gs.release();

	//������ Ŭ���� ��ϵ� ����
	UnregisterClass(WINNAME, hInstance);

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _gs.MainProc(hWnd, iMessage, wParam, lParam);
}

void setWindowSize(int x, int y, int width, int height)
{
	RECT rc;

	rc.left = 0;
	rc.top = 0;
	rc.right = width;
	rc.bottom = height;

	AdjustWindowRect(&rc, WINSTYLE, false);

	SetWindowPos(_hWnd, NULL, x, y, (rc.right - rc.left),
		(rc.bottom - rc.top), SWP_NOZORDER | SWP_NOMOVE);
}