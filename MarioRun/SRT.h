#pragma once

class SRT
{
private:
	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;

	bool isCenter;
public:
	SRT();
	void SetSRT(D3DXVECTOR2 *Scale, D3DXVECTOR3 *Rotation, D3DXVECTOR2 *Translation, Texture* texture, bool CenterS = true, bool CenterR = true);
	void SetSRT(D3DXVECTOR2 *Scale, D3DXVECTOR3 *Rotation, D3DXVECTOR2 *Translation, D3DXVECTOR2 ImageSize, bool CenterS = true, bool CenterR = true);
	void RenderSetting();
};