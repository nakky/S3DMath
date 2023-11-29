#include "S3DMath/Cluster.h"

namespace S3DMath
{
    void Cluster::updateActiveState()
    {
        return updateActiveStateInternal(this, true);
    }

    void Cluster::updateActiveStateInternal(Entity *target, bool parentIsActive)
    {
        target->mIsActiveInTree = target->isActive() && parentIsActive;

        auto children = target->mNode.getChildList();
        for (auto ite = children.begin(); ite != children.end(); ite++)
        {
            Entity *next = (Entity *)(*ite)->getUserData();
            bool ret = tryUpdateInternal(next, target->isActiveInTree());
        }
    }

    bool Cluster::tryUpdate()
    {
        return tryUpdateInternal(this, false);
    }

    bool Cluster::tryUpdateInternal(Entity *target, bool parentUpdate)
    {
        bool retval = false;

        bool needUpdate = parentUpdate || target->needUpdateState();
        if (target->isActiveInTree() && needUpdate)
        {
            target->updateState();
            retval = true;
        }

        auto children = target->mNode.getChildList();
        for (auto ite = children.begin(); ite != children.end(); ite++)
        {
            Entity *next = (Entity *)(*ite)->getUserData();
            bool ret = tryUpdateInternal(next, needUpdate);
            if (ret || retval)
                retval = true;
        }

        return retval;
    }

}; // namespace S3DMath