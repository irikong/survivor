#pragma once

class Component
{
public:
	enum Type {
		kComponent = 0,
		kSpriteComponent,
		kTileMapComponent,
		kMoveComponent
	};

	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();

	virtual void ProcessInput(const uint8_t* keyState);
	virtual void Update(float deltaTime);
	virtual void OnUpdateWorldTransform(); // Actor의 WorldTransform이 변경됐을 때 Call

	virtual Type GetType() const = 0;
	int GetUpdateOrder() const { return mUpdateOrder; }

protected:
	class Actor* mOwner;
	int mUpdateOrder;
};
