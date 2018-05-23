#include "stdafx.h"

MainCamera* MainCamera::instance = NULL;

MainCamera::MainCamera()
{
	free = NULL;
	follow = NULL;
	
	DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);
	DEVICE->SetRenderState(D3DRS_ZENABLE, FALSE);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	UpdateProjectionMatrix();
}

MainCamera::~MainCamera()
{
	Factory* freeFactory = new FreeFactory();
	freeFactory->DeleteCamera(free);
	SAFE_DELETE(freeFactory);

	Factory* followFactory = new FollowFactory();
	followFactory->DeleteCamera(follow);
	SAFE_DELETE(followFactory);
}

void MainCamera::SetMainCamera(Camera * camera)
{
	assert(camera != NULL);
	main = camera;
}

MainCamera * MainCamera::Get()
{
	if (instance == NULL)
		instance = new MainCamera();

	return instance;
}

void MainCamera::Delete()
{
	SAFE_DELETE(instance);
}

void MainCamera::UpdateProjectionMatrix()
{
	D3DVIEWPORT9 viewport;
	DEVICE->GetViewport(&viewport);

	D3DXMatrixOrthoOffCenterLH(&projection, 0.0f,
		(float)viewport.Width, (float)viewport.Height,
		0.0f, -1, 1);

	Device::SetProjection(&projection);
}

void MainCamera::Update()
{
	if (main != NULL)
	{
		FreeView* tempFree = dynamic_cast<FreeView*>(main);
		if (tempFree != NULL)
		{
			if (KEYBOARD->KeyPress(VK_CONTROL))
			{
				if (KEYBOARD->KeyPress(VK_UP))
					tempFree->MoveUp();
				if (KEYBOARD->KeyPress(VK_DOWN))
					tempFree->MoveDown();
				if (KEYBOARD->KeyPress(VK_LEFT))
					tempFree->MoveLeft();
				if (KEYBOARD->KeyPress(VK_RIGHT))
					tempFree->MoveRight();
			}
		}
		main->Update();
	}
}

void MainCamera::ChangeSpotPoint(ISpotPoint * spotPoint)
{
	assert(follow != NULL);
	follow->ChangeSpotPoint(spotPoint);
}

void MainCamera::SetFreePosition(D3DXVECTOR2 position)
{
	FreeView* free = dynamic_cast<FreeView*>(main);
	if (free != NULL)
	{
		free->SetPosition(position);
		free->UpdateViewMatrix();
	}
}

void MainCamera::SetFreeCamera()
{
	if (free == NULL)
	{
		Factory* factory = new FreeFactory();
		free = (FreeView*)factory->CreateCamera();
		SAFE_DELETE(factory);
	}
	SetMainCamera(free);
}

void MainCamera::SetFollowCamera()
{
	if (follow == NULL)
	{
		Factory* factory = new FollowFactory();
		follow = (FollowView*)factory->CreateCamera();
		SAFE_DELETE(factory);
	}
	SetMainCamera(follow);
}
