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
#include<random>

enum OBJ_TYPE
{
	ENEMY,
	PLAYER
};

using namespace std;
int main(void)
{
	srand(time(NULL));

	auto world = new CSWorld();
	for (int f1 = 0; f1 < 100; f1++)
	{
		auto body = CSBody::createShared(CSVec2(rand() % 1000, rand() % 1000));
		body->addShape(CSCircle::createShared(CSVec2(0.f, 0.f), 5.f));
		body->setCollisionGroup(0);
		world->addBody(body);
	}

	auto callback = CSHitCallback::createShared(0, 0);
	int hit = 0;
	callback->HitBegin = [&](const std::shared_ptr<CSBody>& bodyA, const std::shared_ptr<CSBody>& bodyB)
	{
		hit++;
	};

	world->addHitCallback(callback);

	long long sum = 0;
	for (int f1 = 0; f1 < 50; f1++)
	{
		auto start = chrono::system_clock::now();
		world->executeCollision();
		auto end = chrono::system_clock::now();
		sum += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		cout << "time:" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "[ms]" << endl;
	}
	cout << "ave:"<<sum/50.f<<"[ms]" << endl;

	cout << "hit:" << hit/10 << endl;

	cout << "ƒvƒƒOƒ‰ƒ€I—¹" << endl;


	fflush(stdin);
	getchar();
	return 0;
}