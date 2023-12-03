#ifndef S3DMATH_MESH_H
#define S3DMATH_MESH_H

#include "Resource.h"

namespace S3DMath
{

    class Mesh : public Resource
    {
    public:
        Mesh()
            : Resource(),
              mUserData(NULL)
        {
        }

        virtual ~Mesh() {}

        virtual const short getResourceType() { return RESOURCETYPE_MESH; }

        virtual void *getVertices() = 0;
        virtual unsigned int getNumVertices() = 0;
        virtual unsigned int getVerticesBufferSize() = 0;
        virtual void *getIndices() = 0;
        virtual unsigned int getNumIndices() = 0;
        virtual unsigned int getIndicesBufferSize() = 0;
        virtual void *getUvs() = 0;
        virtual unsigned int getNumUvs() = 0;
        virtual unsigned int getUvsBufferSize() = 0;

        void *getUserData() { return mUserData; }
        void setUserData(void *data) { mUserData = data; }

    protected:
        void *mUserData;
    };

}; // namespace S3DMath

#endif // S3DMATH_MESH_H
