#ifndef S3DMATH_RESOURCE_H
#define S3DMATH_RESOURCE_H

#include "S3DMath/Common.h"

namespace S3DMath
{
    enum ResourceType
    {
        RESOURCETYPE_ENTITY = 50000,
        RESOURCETYPE_MESH = 50001,
        RESOURCETYPE_MATERIAL = 50002
    };

    class Resource
    {
    public:
        Resource()
            : mUserData(NULL),
              mResourceId(0)
        {
        }

        virtual void init() {}
        virtual void cleanup() {}

        virtual const short getResourceType() = 0;

        void *getUserData() { return mUserData; }
        void setUserData(void *data) { mUserData = data; }

        unsigned int getResourceId() { return mResourceId; }
        void setResourceId(unsigned id) { mResourceId = id; }

        protected:
        void *mUserData;
        unsigned int mResourceId;
    };

}; // namespace S3DMath

#endif // S3DMATH_RESOURCE_H
