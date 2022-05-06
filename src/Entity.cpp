#include "Entity.h"

Entity::Entity(b2World& pWorld, b2Vec2 _size, b2Vec2 _pos) {
    
    size = _size;
  
  //créer le body
    b2BodyDef bodyDef;
    bodyDef.position.Set(_pos.x, _pos.y);
    bodyDef.type = b2_dynamicBody; //body soumis aux forces
    bodyDef.fixedRotation = true; //pas de moment cinétique
    body = pWorld.CreateBody(&bodyDef);

  //créer le rectangle
    b2PolygonShape dynamicBox; //boite de collision
    dynamicBox.SetAsBox(size.x * 0.5, size.y * 0.5);

  //créer la fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.f;
    fixtureDef.friction = 0.3;

    body->CreateFixture(&fixtureDef);
}

Entity::Entity() {
}

void Entity::init_physical_body(b2World& pWorld, b2Vec2 _size, b2Vec2 _pos) {
  size = _size;
  
  //créer le body
    b2BodyDef bodyDef;
    bodyDef.position.Set(_pos.x, _pos.y);
    bodyDef.type = b2_dynamicBody; //body soumis aux forces
    bodyDef.fixedRotation = true; //pas de moment cinétique
    body = pWorld.CreateBody(&bodyDef);

  //créer le rectangle
    b2PolygonShape dynamicBox; //boite de collision
    dynamicBox.SetAsBox(size.x * 0.5, size.y * 0.5);

  //créer la fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.f;
    fixtureDef.friction = 0.3;

    body->CreateFixture(&fixtureDef);
}