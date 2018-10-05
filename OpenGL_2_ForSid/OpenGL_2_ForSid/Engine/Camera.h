#pragma once

// Inherited Include
#include "Component.h"

enum ECAMERATYPE
{
	ORTHOGRAPHIC,
	PERSPECTIVE,
};

class CCamera : public CComponent
{
public:
	CCamera();
	~CCamera();


	virtual void Update(float _tick) override;
	virtual void Initialize() override;

	glm::mat4 GetView() const;
	void CalcViewMatrix();
	glm::mat4 GetProj() const;
	void CalcProjectionMatrix();

	glm::vec3 GetCameraFacing() const;
	void SetCameraFacing(glm::vec3 _Facing);

	glm::vec3 GetCameraNormal() const;
	void SetCameraNormal(glm::vec3 _Normal);



	
	/** Configuration for the camera */
public: 

	bool m_bPerspective;
	float m_fov;
	float m_nearPlane;
	float m_farPlane;

	bool m_bIsControlling;


	/** Member variables */
private: 

	glm::vec3 m_cameraFacing;
	glm::vec3 m_cameraNormal;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;
};