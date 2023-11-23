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

        bool tryUpdate();

    private:
        bool tryUpdateInternal(Entity *target, bool parentUpdate);
    };
}

#endif // S3DMATH_CLUSTER_H
