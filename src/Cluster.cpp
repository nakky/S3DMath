#include "S3DMath/Cluster.h"

namespace S3DMath
{
    void Cluster::updateActiveState()
    {
        updateActiveStateInternal(this, true);
    }

    void Cluster::updateActiveStateInternal(Entity *target, bool parentIsActive)
    {
        target->mIsActiveInTree = target->isActive() && parentIsActive;

        std::list<GeometricNode *> &children = target->mNode.getChildList();
        for (auto ite = children.begin(); ite != children.end(); ite++)
        {
            Entity *next = (Entity *)(*ite)->getUserData();
            updateActiveStateInternal(next, target->isActiveInTree());
        }
    }

    void Cluster::tryUpdate()
    {
        tryUpdateInternal(this, false);
    }

    void Cluster::tryUpdateInternal(Entity *target, bool parentUpdate)
    {
        bool needUpdate = parentUpdate || target->needUpdateState();
        if (target->isActiveInTree() && needUpdate)
        {
            target->updateState();
        }

        std::list<GeometricNode *> &children = target->mNode.getChildList();
        for (auto ite = children.begin(); ite != children.end(); ite++)
        {
            Entity *next = (Entity *)(*ite)->getUserData();
            tryUpdateInternal(next, needUpdate);
        }
    }

    const bool Cluster::needRender()
    {
        if (Entity::needRender())
            return true;

        std::list<GeometricNode *> &children = mNode.getChildList();
        for (auto ite = children.begin(); ite != children.end(); ite++)
        {
            Entity *next = (Entity *)(*ite)->getUserData();
            bool ret = needRenderInternal(next);
            if (ret)
                return true;
        }
        return false;
    }

    const bool Cluster::needRenderInternal(Entity *target)
    {
        if (target->needRender())
            return true;
        std::list<GeometricNode *> &children = target->mNode.getChildList();
        for (auto ite = children.begin(); ite != children.end(); ite++)
        {
            Entity *next = (Entity *)(*ite)->getUserData();
            bool ret = needRenderInternal(next);
            if (ret)
                return true;
        }
        return false;
    }

    void Cluster::resetNeedRender()
    {
        Entity::resetNeedRender();

        std::list<GeometricNode *> &children = mNode.getChildList();
        for (auto ite = children.begin(); ite != children.end(); ite++)
        {
            Entity *next = (Entity *)(*ite)->getUserData();
            resetNeedRenderInternal(next);
        }
    }

    void Cluster::resetNeedRenderInternal(Entity *target)
    {
        target->resetNeedRender();
        std::list<GeometricNode *> &children = target->mNode.getChildList();
        for (auto ite = children.begin(); ite != children.end(); ite++)
        {
            Entity *next = (Entity *)(*ite)->getUserData();
            resetNeedRenderInternal(next);
        }
    }

}; // namespace S3DMath