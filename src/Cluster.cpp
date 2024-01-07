
#include "S3DMath/Cluster.h"

namespace S3DMath
{
    void Cluster::init()
    {
        Entity::init();
    }

    void Cluster::cleanup()
    {
        for (auto ite = mEntityList.begin(); ite != mEntityList.end(); ite++)
        {
            (*ite)->cleanup();
            SAFE_DELETE(*ite);
        }
        mEntityList.clear();

        Entity::cleanup();
    }

}; // namespace S3DMath