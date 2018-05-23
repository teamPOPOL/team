#include "stdafx.h"
#include "Device.h"

Device* Device::instance = NULL;
LPDIRECT3DDEVICE9 Device::device = NULL;

Device * Device::Get(HWND hwnd)
{
	if (instance == NULL)
		instance = new Device(hwnd);

	return instance;
}

void Device::Delete()
{
	SAFE_DELETE(instance);
}

void Device::SetWorld(D3DXMATRIX * world)
{
	device->SetTransform(D3DTS_WORLD, world);
}

void Device::SetView(D3DXMATRIX * view)
{
	device->SetTransform(D3DTS_VIEW, view);
}

void Device::SetProjection(D3DXMATRIX * projection)
{
	device->SetTransform(D3DTS_PROJECTION, projection);
}

void Device::StartAlphaRender()
{
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
}

void Device::EndAlphaRender()
{
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void Device::BeginScene(DWORD clearColor)
{
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clearColor, 1.0f, 0);
	device->BeginScene();
}

void Device::EndScene() //�ĸ����
{
	device->EndScene();
	device->Present(NULL, NULL, NULL, NULL);
}

Device::Device(HWND hwnd)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	assert(d3d != NULL);

	D3DPRESENT_PARAMETERS param = { 0 };
	param.Windowed = TRUE;
	param.SwapEffect = D3DSWAPEFFECT_DISCARD;
	param.AutoDepthStencilFormat = D3DFMT_D16;
	param.EnableAutoDepthStencil = TRUE;

	//�ĸ� ���۸� ��ۼ� �ְ� �Ѵ�. ���� �������� ������ �ȴ�.
	param.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	
	//vSync(Vertical Synchronization) : ���� ����
	//�׷��� ī���� ������������ ȭ�� ������� ���� �����ϴ� ���
	//�������⸦ Ű�� 60���������� ����
	
	param.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;//vSync��

	HRESULT hr;
	hr = d3d->CreateDevice
	(
		D3DADAPTER_DEFAULT //��ȭ�龵�ų� ����ȭ�龵�ų�
		, D3DDEVTYPE_HAL //�ϵ�
		, hwnd //�ڵ� (�߿�!!)�ڵ鿡�� �������ȴ�
		, D3DCREATE_HARDWARE_VERTEXPROCESSING //����ó�� �����Ұų�(�ϵ����Ѵ�)
		, &param //�߰����� ����
		, &device
	);
	assert(SUCCEEDED(hr));
}

Device::~Device()
{
	SAFE_RELEASE(device);
	SAFE_RELEASE(d3d);
}
