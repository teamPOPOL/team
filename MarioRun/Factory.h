#pragma once

class Factory
{
protected:
	virtual Camera* Create() = 0;
	virtual void Delete(Camera* camera) = 0;

public:
	Camera * CreateCamera()
	{
		return Create();
	}
	void DeleteCamera(Camera* camera)
	{
		Delete(camera);
	}
};

class FreeFactory : public Factory
{
private:
	Camera * Create()
	{
		return new FreeView();
	}
	void Delete(Camera* camera)
	{
		//FreeView* free = (FreeView*)camera;
		FreeView* free = dynamic_cast<FreeView*>(camera);
		SAFE_DELETE(free);
	}
};

class FollowFactory : public Factory
{
private:
	Camera * Create()
	{
		return new FollowView();
	}
	void Delete(Camera* camera)
	{		
		FollowView* follow = dynamic_cast<FollowView*>(camera);
		SAFE_DELETE(follow);
	}
};