#ifndef S3DMATH_MESH_H
#define S3DMATH_MESH_H

namespace S3DMath
{

    class Mesh
    {
    public:
        Mesh()
            : mUserData(NULL)
        {
        }

        virtual ~Mesh() {}

        virtual void init() = 0;
        virtual void cleanup() = 0;

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
