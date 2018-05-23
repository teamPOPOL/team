#include "stdafx.h"

Camera::Camera()
{
	position = { 0, 0 };
	D3DXMatrixIdentity(&view);		
}

Camera::~Camera()
{
}

void Camera::Update()
{
	
}

void Camera::UpdateViewMatrix()
{
	D3DXMatrixTranslation(&view, position.x, position.y, 0.0f);
	Device::SetView(&view);
}
/*
void Camera::SetProjection()
{
	D3DVIEWPORT9 viewport;
	DEVICE->GetViewport(&viewport);

	D3DXMatrixOrthoOffCenterLH(&projection, 0.0f,
		(float)viewport.Width, (float)viewport.Height,
		0.0f, -1, 1);

	Device::SetProjection(&projection);
}*/
