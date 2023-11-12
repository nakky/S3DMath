#include "S3DMath/Cluster.h"

namespace S3DMath
{
    bool Cluster::tryUpdateInternal(Entity *target, bool parentUpdate)
    {
        bool needUpdate = parentUpdate || target->needStateUpdate();
        if (needUpdate)
        {
            target->mNode.calculateGlobalState();
            target->resetStateUpdateState();
        }
        bool retval = false;
        auto children = target->mNode.getChildList();
        for (auto ite = children.begin(); ite != children.end(); ite++)
        {
            Entity *next = (Entity *)(*ite)->getUserData();
            bool ret = tryUpdateInternal(next, needUpdate);
            if (ret)
                retval = true;
        }

        return retval;
    }

    bool Cluster::tryUpdate()
    {
        return tryUpdateInternal(&mRootEntity, false);
    }

}; // namespace S3DMath