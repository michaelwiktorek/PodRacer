#include "stdafx.h"


int main(int argc, char *argv[])
{
    theWorld.Initialize(800, 600, "Test Game, Please Ignore", true, false, true);
    
    theWorld.SetupPhysics(*(new Vector2(0, 0))); // TODO: Don't leak memory
    theWorld.SetSideBlockers(true, 0.7f);
    theWorld.Add(new GridActor(), -1);
    
    PhysicsActor *engine1 = new PhysicsActor();
    engine1->SetPosition(-2, 5);
    engine1->SetSize(1.0f, 5.0f);
    engine1->SetColor(0.3f, 0.3f, 0.3f);
    engine1->InitPhysics();
    theWorld.Add(engine1);
    
    PhysicsActor *engine2 = new PhysicsActor();
    engine2->SetPosition(2, 5);
    engine2->SetSize(1.0f, 5.0f);
    engine2->SetColor(0.3f, 0.3f, 0.3f);
    engine2->InitPhysics();
    theWorld.Add(engine2);
    
    PhysicsActor *pod = new PhysicsActor();
    pod->SetPosition(0, -2);
    pod->SetSize(2.0f, 3.0f);
    pod->SetColor(0.3f, 0.3f, 0.7f);
    pod->InitPhysics();
    theWorld.Add(pod);
    
    b2Body *engine1body = engine1->GetBody();
    b2Body *engine2body = engine2->GetBody();
    
    b2DistanceJointDef jointDef;
    jointDef.bodyA = engine1body;
    jointDef.bodyB = engine2body;
    jointDef.frequencyHz = 0.5f;
    jointDef.dampingRatio = 0.01f;
    jointDef.collideConnected = true;
    
    glColor3f(1.0f, 1.0f, 1.0f);
    DrawLine(*new Vector2(3,1), *new Vector2(5, 3));
    
    jointDef.length = 5;
    jointDef.localAnchorA = *new b2Vec2(-0.5f, 2.0f);
    jointDef.localAnchorB = *new b2Vec2(0.5f, -2.0f);
    b2DistanceJoint *joint = (b2DistanceJoint*)(theWorld.GetPhysicsWorld().CreateJoint(&jointDef));
    
    jointDef.length = 5;
    jointDef.localAnchorA = *new b2Vec2(-0.5f, -2.0f);
    jointDef.localAnchorB = *new b2Vec2(0.5f, 2.0f);
    b2DistanceJoint *joint2 = (b2DistanceJoint*)(theWorld.GetPhysicsWorld().CreateJoint(&jointDef));
    
    jointDef.length = 3;
    jointDef.localAnchorA = *new b2Vec2(-0.5f, 2.0f);
    jointDef.localAnchorB = *new b2Vec2(0.5f, 2.0f);
    b2DistanceJoint *joint3 = (b2DistanceJoint*)(theWorld.GetPhysicsWorld().CreateJoint(&jointDef));
    
    jointDef.length = 3;
    jointDef.localAnchorA = *new b2Vec2(-0.5f, -2.0f);
    jointDef.localAnchorB = *new b2Vec2(0.5f, -2.0f);
    b2DistanceJoint *joint4 = (b2DistanceJoint*)(theWorld.GetPhysicsWorld().CreateJoint(&jointDef));

    
    engine1->ApplyLinearImpulse(*new Vector2(0,1), *new Vector2(0, 0));
    //engine2->ApplyAngularImpulse(5);
    engine2->ApplyLinearImpulse(*new Vector2(0,1), *new Vector2(0, 0));
    
    
    theWorld.StartGame();
    theWorld.Destroy();
    
    return 0;
}