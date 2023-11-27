#include "S3DMath/Cluster.h"

namespace S3DMath
{
    bool Cluster::tryUpdateInternal(Entity *target, bool parentUpdate, bool parentIsActive)
    {
        target->mIsActiveInTree = target->isActive() && parentIsActive;

        bool needUpdate = parentUpdate || target->needUpdateState();
        if (target->isActive() && needUpdate)
        {
            target->updateState();
        }
        bool retval = false;
        auto children = target->mNode.getChildList();
        for (auto ite = children.begin(); ite != children.end(); ite++)
        {
            Entity *next = (Entity *)(*ite)->getUserData();
            bool ret = tryUpdateInternal(next, needUpdate, target->isActiveInTree());
            if (ret)
                retval = true;
        }

        return retval;
    }

    bool Cluster::tryUpdate()
    {
        return tryUpdateInternal(this, false, true);
    }

}; // namespace S3DMath