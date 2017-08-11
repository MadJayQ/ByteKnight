#include "CollisionSubsystem.h"

#include "MovementComponent.h"
#include "PositionComponent.h"
#include "UnitMetrics.h"


b2Vec2 WFVectorToB2Vector(const CVector3& in)
{
	return b2Vec2(in._x, in._y);
}
CCollisionSubsystem::CCollisionSubsystem()
{
	m_pCollisionWorld = std::make_unique<b2World>(b2Vec2(0.0f, 9.8));

	b2Vec2 vs[4] = 
	{ 
		b2Vec2(0, 0), 
		b2Vec2(1280, 0), 
		b2Vec2(1280,720), 
		b2Vec2(0, 720)
	};
	b2ChainShape chain;
	chain.CreateLoop(vs, 4);

	b2BodyDef bodyDef;
	bodyDef.position.Set(0, 0);
	b2Body* edge = m_pCollisionWorld->CreateBody(&bodyDef);
	b2FixtureDef edgeFixture;
	edgeFixture.shape = &chain;
	edge->CreateFixture(&edgeFixture);

	b2Vec2 slopeVS[2] =
	{
		b2Vec2(50, 50),
		b2Vec2(380, 280)
	};
	b2ChainShape slopeChain;
	slopeChain.CreateChain(slopeVS, 2);
	b2BodyDef slopeBodyDef;
	b2Body* slopeBody = m_pCollisionWorld->CreateBody(&slopeBodyDef);
	b2FixtureDef slopeFixture;
	slopeFixture.shape = &slopeChain;
	slopeBody->CreateFixture(&slopeFixture);

	b2Vec2 slopeTwoVS[4] =
	{
		b2Vec2(450, 300),
		b2Vec2(450, 400),
		b2Vec2(350, 410),
		b2Vec2(150, 719)
	};
	b2ChainShape slopeChain2;
	slopeChain2.CreateChain(slopeTwoVS, 4);
	b2BodyDef slopeBodyDef2;
	b2Body* slopeBody2 = m_pCollisionWorld->CreateBody(&slopeBodyDef2);
	b2FixtureDef slopeFixture2;
	slopeFixture2.shape = &slopeChain2;
	slopeBody2->CreateFixture(&slopeFixture2);


	b2BodyDef dynamicBodyDef;
	dynamicBodyDef.type = b2_dynamicBody;
	dynamicBodyDef.fixedRotation = false;
	dynamicBodyDef.gravityScale = 10.f;
	dynamicBodyDef.angularVelocity = 0.f;
	b2Vec2 pos = WFVectorToB2Vector(CUnitMetrics::Instance()->ConvertFromPixels<Meters>(CVector3(50, 0.f, 0.f)));
	dynamicBodyDef.position.Set(60.f, 30.f);
	b2Body* ball = m_pCollisionWorld->CreateBody(&dynamicBodyDef);
	b2CircleShape ballShape;
	ballShape.m_radius = 20.f;
	b2FixtureDef ballFixture;
	ballFixture.friction = 0.3f;
	ballFixture.restitution = 0.5f;
	ballFixture.shape = &ballShape;
	ball->CreateFixture(&ballFixture);

}

CCollisionSubsystem::~CCollisionSubsystem()
{

}
void CCollisionSubsystem::Tick(float flDeltaTime)
{
	m_pCollisionWorld->Step(flDeltaTime, 24, 20);
}

void CCollisionSubsystem::RegisterEntity(CEntityBase* ent)
{
	IGameSubsystem::RegisterEntity(ent);
}

void CCollisionSubsystem::UnRegisterEntity(CEntityBase* ent)
{
	IGameSubsystem::UnRegisterEntity(ent);
}

