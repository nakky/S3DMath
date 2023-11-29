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

        void updateActiveState();
        bool tryUpdate();

    private:
        void updateActiveStateInternal(Entity *target, bool parentIsActive);
        bool tryUpdateInternal(Entity *target, bool parentUpdate);
    };
}

#endif // S3DMATH_CLUSTER_H
