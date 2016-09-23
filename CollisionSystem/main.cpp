#include"CSVec2/CSVec2.h"
#include"CSHitCallback/CSHitCallback.h"
#include"CSworld/CSWorld.h"
#include"CSBody/CSBody.h"
#include"CSShape/CSCircle/CSCircle.h"
#include"CSShape/CSPolygon/CSPolygon.h"
#include"CSShape\AABB\AABB.h"
#include<iostream>
#include<list>

#include<chrono>

enum OBJ_TYPE
{
	ENEMY,
	PLAYER
};

using namespace std;
int main(void)
{

	AABB aabb1 = AABB(CSVec2(0.f, 0.f), CSVec2(10.f, 10.f));
	AABB aabb2 = AABB(CSVec2(10.0f, 10.0f), CSVec2(20.f, 20.f));

	auto world = new CSWorld();
	for (int f1 = 0; f1 < 100; f1++)
	{
		auto body = CSBody::createShared(CSVec2(0.f, 0.f));
		body->addShape(CSCircle::createShared(CSVec2(0.f, 0.f), 10.f));
		body->setCollisionGroup(0);
		world->addBody(body);
	}


	for (int f2 = 0; f2 < 10; f2++)
	{
		auto body2 = CSBody::createShared(CSVec2(0.f, 0.f));
		body2->addShape(CSCircle::createShared(CSVec2(0.f, 0.f), 10.f));
		body2->setCollisionGroup(1);
		world->addBody(body2);
	}

	auto callback = CSHitCallback::createShared(0, 1);
	callback->HitBegin = [](const std::shared_ptr<CSBody>& bodyA, const std::shared_ptr<CSBody>& bodyB)
	{
	};

	world->addHitCallback(callback);

	auto start = chrono::system_clock::now();

	world->executeCollision();

	auto end = chrono::system_clock::now();

	cout << "time:" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()<<"[ms]"<< endl;

	aabb2.dump();

	cout << aabb1.isIntersect(aabb2) << endl;

	aabb2.setCenterPosition(CSVec2(10.f, 10.f));
	aabb2.dump();

	cout << aabb1.isIntersect(aabb2) << endl;

	cout << "ƒvƒƒOƒ‰ƒ€I—¹" << endl;

	fflush(stdin);
	getchar();
	return 0;
}