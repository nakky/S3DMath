#ifndef S3DMATH_MESH_H
#define S3DMATH_MESH_H

namespace S3DMath
{

    class Mesh
    {
    public:
        Mesh()
        {
        }

        virtual ~Mesh() {}

        virtual void init() = 0;
        virtual void cleanup() = 0;

        virtual void *getVertices() = 0;
        virtual unsigned int getVerticesBufferSize() = 0;
        virtual void *getIndices() = 0;
        virtual unsigned int getIndicesBufferSize() = 0;
        virtual void *getUvs() = 0;
        virtual unsigned int getUvsBufferSize() = 0;

    protected:
    };

}; // namespace S3DMath

#endif // S3DMATH_MESH_H