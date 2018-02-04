#pragma once
#ifndef _CAMERA_H
#define _CAMERA_H


#include <DirectXMath.h> //to include maths formulas 
#include "GameSprite.h"

class Graphics;

class Camera
{
public: 
	//constructors and destructor
	Camera(int width, int height, float angle, DirectX::XMFLOAT3 scaleFactors);
	~Camera();

	//Game Functions
	void Update();
	void Follow(GameSprite *following);
	void Unfollow();
	bool IsFollowing() const;
	void SetTransform(Graphics *gDevice) const;

private:
	float angle;
	DirectX::XMFLOAT3 scaleFactors;
	D3DXMATRIX orthographicMatrix;
	D3DXMATRIX identityMatrix;
	D3DXMATRIX viewMatrix;

	GameSprite *following;

	int width;
	int height;

};

#endif