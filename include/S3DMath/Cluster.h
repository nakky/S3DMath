#ifndef S3DMATH_CLUSTER_H
#define S3DMATH_CLUSTER_H

#include "S3DMath/Entity.h"
#include <list>

namespace S3DMath
{
    class Cluster : public Entity
    {
    public:
        Cluster()
            : Entity()
        {
        }

        virtual ~Cluster() {}

        virtual const bool needRender();
        virtual void resetNeedRender();

        void updateActiveState();
        void tryUpdate();

    private:
        virtual const bool needRenderInternal(Entity *target);
        virtual void resetNeedRenderInternal(Entity *target);

        void updateActiveStateInternal(Entity *target, bool parentIsActive);
        void tryUpdateInternal(Entity *target, bool parentUpdate);
    };
}

#endif // S3DMATH_CLUSTER_H
