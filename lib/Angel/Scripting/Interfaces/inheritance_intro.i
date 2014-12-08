%include <factory.i>

%factory(Actor*, TextActor, FullScreenActor, MazeFinder, SwigTest, HUDActor, PhysicsActor, Camera, ParticleActor);
%factory(DeveloperLog*, ConsoleLog, CompoundLog, FileLog, SystemLog);
%factory(MessageListener*, TextActor, MazeFinder, SwigTest, HUDActor, FullScreenActor, Camera, PhysicsActor, ParticleActor, Actor);
%factory(Renderable*, TextActor, MazeFinder, SwigTest, FullScreenActor, HUDActor, Camera, Actor, GridActor, PhysicsActor, ParticleActor);