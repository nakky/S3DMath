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
        {
        }

        virtual void init() {}
        virtual void cleanup() {}

        virtual const short getResourceType() = 0;
    };

}; // namespace S3DMath

#endif // S3DMATH_RESOURCE_H
