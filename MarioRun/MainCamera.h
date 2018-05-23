#pragma once

class MainCamera
{
private:
	Camera * main;
	FreeView* free;
	FollowView* follow;

	D3DXMATRIX projection;
	static MainCamera* instance;	

	MainCamera();
	~MainCamera();

	void SetMainCamera(Camera* camera);
public:
	static MainCamera* Get();
	static void Delete();

	void UpdateProjectionMatrix();

	void Update();

	void ChangeSpotPoint(ISpotPoint* spotPoint);
	void SetFreePosition(D3DXVECTOR2 position);

	void SetFreeCamera();
	void SetFollowCamera();

	Camera* GetMain()
	{
		return main;
	}
};