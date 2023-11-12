

#include "S3DMath/Entity.h"

namespace S3DMath
{
    void Entity::addChild(Entity *child)
    {
        mNode.setRelationToChild(&(child->mNode));
    }

    void Entity::removeChild(Entity *child)
    {
        mNode.cutOffRelationToChild(&(child->mNode));
    }

    void Entity::setLocalPosition(Vector3 &pos)
    {
        mNode.setLocalPosition(pos);
        mStateNeedUpdate = true;
    }

    void Entity::setLocalRotation(Quaternion4 &rot)
    {
        mNode.setLocalOrientation(rot);
        mStateNeedUpdate = true;
    }

    void Entity::setLocalScale(Vector3 &scl)
    {
        mNode.setLocalScale(scl);
        mStateNeedUpdate = true;
    }

}; // namespace S3DMath