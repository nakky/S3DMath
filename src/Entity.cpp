

#include "S3DMath/Entity.h"

namespace S3DMath
{
    void Entity::init()
    {
        mNode.init();
    }

    void Entity::cleanup()
    {
        mNode.cleanup();
    }

    void Entity::addChild(Entity *child)
    {
        mNode.setRelationToChild(&(child->mNode));
    }

    void Entity::removeChild(Entity *child)
    {
        mNode.cutOffRelationToChild(&(child->mNode));
    }

    void Entity::setLocalPosition(const Vector3 &pos)
    {
        mNode.setLocalPosition(pos);
        mNeedStateUpdate = true;
    }

    void Entity::setLocalRotation(const Quaternion4 &rot)
    {
        mNode.setLocalOrientation(rot);
        mNeedStateUpdate = true;
    }

    void Entity::setLocalScale(const Vector3 &scl)
    {
        mNode.setLocalScale(scl);
        mNeedStateUpdate = true;
    }

    void Entity::updateState()
    {
        mNode.calculateGlobalState();
        mNeedStateUpdate = false;
    }

}; // namespace S3DMath