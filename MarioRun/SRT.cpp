#include "stdafx.h"

SRT::SRT()
{
	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&view);
	D3DXMatrixIdentity(&projection);

	D3DVIEWPORT9 viewport;
	DEVICE->GetViewport(&viewport);
	D3DXMatrixOrthoOffCenterLH(&projection, 0.0f, viewport.Width, viewport.Height, 0.0f, -1, 1);

	DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);
}

void SRT::SetSRT(D3DXVECTOR2 *Scale, D3DXVECTOR3 *Rotation, D3DXVECTOR2 *Translation, Texture* texture, bool isCenterS, bool CenterR)
{
	D3DXVECTOR2 imageSize;
	texture->GetRealSize(&imageSize, *Scale);
	imageSize *= 0.5f;

	SetSRT(Scale, Rotation, Translation, imageSize, isCenterS, CenterR);
}

void SRT::SetSRT(D3DXVECTOR2 * Scale, D3DXVECTOR3 * Rotation, D3DXVECTOR2 * Translation, D3DXVECTOR2 ImageSize, bool CenterS, bool CenterR)
{
	D3DXMATRIX S;
	D3DXMATRIX R;
	D3DXMATRIX T;

	ImageSize *= 0.5f;

	D3DXMATRIX matCenter;
	D3DXMATRIX matInvCenter;

	D3DXMatrixTranslation(&matCenter, ImageSize.x, ImageSize.y, 0.0f);
	D3DXMatrixInverse(&matInvCenter, NULL, &matCenter);

	if (CenterS)
	{
		D3DXMATRIX matScale;
		D3DXMatrixScaling(&matScale, Scale->x, Scale->y, 1.0f);
		S = matInvCenter * matScale * matCenter;
	}
	else
		D3DXMatrixScaling(&S, Scale->x, Scale->y, 1.0f);

	if (CenterR)
	{
		D3DXMATRIX matRotation;
		D3DXMatrixRotationYawPitchRoll(&matRotation, Rotation->y, Rotation->x, Rotation->z);
		R = matInvCenter * matRotation * matCenter;
	}
	else
		D3DXMatrixRotationYawPitchRoll(&R, Rotation->y, Rotation->x, Rotation->z);

	D3DXMatrixTranslation(&T, Translation->x, Translation->y, 0.0f);
	world = S * R * T;
}

void SRT::RenderSetting()
{
	Device::SetWorld(&world);
}
