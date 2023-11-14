#ifndef S3DMATH_MESH_RECTANGLE_H
#define S3DMATH_MESH_RECTANGLE_H

#include "S3DMath/Mesh.h"
#include "S3DMath/MathematicsTypes.h"

namespace S3DMath
{
    class Rectangle : public Mesh
    {
    public:
        Rectangle(float width = 0.1f, float height = 0.1f)
            : mWidth(width),
              mHeight(height)
        {
        }

        virtual ~Rectangle() {}

        virtual void init()
        {
            float hwidth = mWidth / 2.0f;
            float hheight = mHeight / 2.0f;
            mVertices[0].x = -hwidth;
            mVertices[0].y = -hheight;
            mVertices[0].z = 0.0f;
            mVertices[1].x = hwidth;
            mVertices[1].y = -hheight;
            mVertices[1].z = 0.0f;
            mVertices[2].x = hwidth;
            mVertices[2].y = hheight;
            mVertices[2].z = 0.0f;
            mVertices[3].x = -hwidth;
            mVertices[3].y = hheight;
            mVertices[3].z = 0.0f;
        }
        virtual void cleanup() {}

        virtual void *getVertices() { return mVertices; }
        virtual unsigned int getNumVertices() { return 4; }
        virtual unsigned int getVerticesBufferSize() { return 4 * sizeof(Vector3); }
        virtual void *getIndices() { return mIndices; }
        virtual unsigned int getNumIndices() { return 6; }
        virtual unsigned int getIndicesBufferSize() { return 6 * sizeof(int); }
        virtual void *getUvs() { return mUvs; }
        virtual unsigned int getNumUvs() { return 4; }
        virtual unsigned int getUvsBufferSize() { return 4 * sizeof(Vector2); }

    protected:
        float mWidth;
        float mHeight;

        Vector3 mVertices[4];
        int mIndices[6] = {0, 1, 2, 0, 2, 3};
        Vector2 mUvs[4] = {Vector2(0.0f, 0.0f), Vector2(0.0f, 1.0f), Vector2(1.0f, 1.0f), Vector2(1.0f, 0.0f)};
    };

}; // namespace S3DMath

#endif // S3DMATH_MESH_RECTANGLE_H
