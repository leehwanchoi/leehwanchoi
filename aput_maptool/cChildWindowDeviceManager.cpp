#include "stdafx.h"
#include "cChildWindowDeviceManager.h"


cChildWindowDeviceManager::cChildWindowDeviceManager()
{
	m_pD3D2 = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9 stCaps;		// 장치 정보를 담을 구조체
	int nVertexProcessing;	// 버텍스를 처리하는 방식

	m_pD3D2->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &stCaps);

	if (stCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		nVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		nVertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	D3DPRESENT_PARAMETERS stD3DPP;
	ZeroMemory(&stD3DPP, sizeof(D3DPRESENT_PARAMETERS));
	stD3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	stD3DPP.Windowed = TRUE;
	stD3DPP.BackBufferFormat = D3DFMT_UNKNOWN;		// 픽셀 포맷 p79
	stD3DPP.EnableAutoDepthStencil = TRUE;			// 깊이 버퍼 자동 관리
	stD3DPP.AutoDepthStencilFormat = D3DFMT_D16;	// 깊이 버퍼 p82
	stD3DPP.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; //프레임제한 해제

	HRESULT hr2 = m_pD3D2->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		g_childhWnd,
		nVertexProcessing,
		&stD3DPP,
		&m_pD3DDevice2);
}


cChildWindowDeviceManager::~cChildWindowDeviceManager()
{
}

void cChildWindowDeviceManager::Destroy()
{
	if (m_pD3DDevice2)
	{
		ULONG ul = m_pD3DDevice2->Release();
		assert(ul == 0 && "디바이스를 이용해서 생성한 객체 중 소멸되지 않은 객체가 있음");
	}
}
