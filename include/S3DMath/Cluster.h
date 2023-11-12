#ifndef S3DMATH_CLUSTER_H
#define S3DMATH_CLUSTER_H

#include "S3DMath/Entity.h"

namespace S3DMath
{
    class Cluster
    {
    public:
        Cluster()
        {
        }

        virtual ~Cluster() {}

        Entity *getRootEntity() { return &mRootEntity; }

        bool tryUpdate();

    private:
        bool tryUpdateInternal(Entity *target, bool parentUpdate);

    protected:
        Entity mRootEntity;
    };
}

#endif // S3DMATH_CLUSTER_H
