#pragma once
#include <cstdint>

class Component
{
public:
	enum Type {
		kComponent = 0,
		kSpriteComponent,
		kAtlasComponent,
		kAnimComponent,
		kTileMapComponent,
		kMoveComponent,
		kInputComponent,
		kColliderComponent,
		kCircleComponent,
		kBoxComponent
	};

	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();

	virtual void ProcessInput(const uint8_t* keyState);
	virtual void Update(float deltaTime);
	virtual void OnUpdateWorldTransform(); // Actor의 WorldTransform이 변경됐을 때 Call

	virtual Type GetType() const = 0;
	class Actor* GetOwner() const { return mOwner; }
	int GetUpdateOrder() const { return mUpdateOrder; }

protected:
	class Actor* mOwner;
	int mUpdateOrder;
};
