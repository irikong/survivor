#include "Physics2D.h"
#include "CircleComponent.h"
#include "BoxComponent.h"

Physics2D::Physics2D(Game* game) :
	mGame(game)
{

}

void Physics2D::AddCircle(CircleComponent* circle)
{
	mCircles.emplace_back(circle);
}

void Physics2D::RemoveCircle(CircleComponent* circle)
{
	auto iter = std::find(mCircles.begin(), mCircles.end(), circle);
	if (iter != mCircles.end()) {
		mCircles.erase(iter);
	}
}

void Physics2D::AddBox(BoxComponent* box)
{
	mBoxes.emplace_back(box);
}

void Physics2D::RemoveBox(BoxComponent* box)
{
	auto iter = std::find(mBoxes.begin(), mBoxes.end(), box);
	if (iter != mBoxes.end()) {
		mBoxes.erase(iter);
	}
}

void Physics2D::CollisionDetection(CircleComponent* circle)
{
	for (CircleComponent* cc : mCircles) {
		if (circle != cc && Intersect(circle->GetWorldCircle(), cc->GetWorldCircle())) {

		}
	}

	for (BoxComponent* bc : mBoxes) {
		if (Intersect(circle->GetWorldCircle(), bc->GetWorldBox())) {

		}
	}
}

void Physics2D::CollisionDetection(BoxComponent* box)
{
	for (CircleComponent* cc : mCircles) {
		if (Intersect(box->GetWorldBox(), cc->GetWorldCircle())) {

		}
	}

	for (BoxComponent* bc : mBoxes) {
		if (box != bc && Intersect(box->GetWorldBox(), bc->GetWorldBox())) {

		}
	}
}
