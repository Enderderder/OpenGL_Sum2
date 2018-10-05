#pragma once

// Inherited Include
#include "Engine/GameObject.h"

// Forward Declare
class CMeshComponent;

class CCube : public CGameObject
{
public:
	CCube();
	~CCube();

	virtual void InitializeObject() override;
	virtual void Update() override;


private:

	CMeshComponent* m_meshRenderer;
};

