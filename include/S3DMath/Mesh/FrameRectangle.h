#ifndef S3DMATH_MESH_FRAMERECTANGLE_H
#define S3DMATH_MESH_FRAMERECTANGLE_H

#include "S3DMath/Mesh.h"
#include "S3DMath/MathematicsTypes.h"

namespace S3DMath
{
    class FrameRectangle : public Mesh
    {
    public:
        FrameRectangle(
            float width = 0.1f, float height = 0.1f,
            float top = 0.01f, float right = 0.01f, float bottom = 0.01f, float left = 0.01f)
            : mWidth(width),
              mHeight(height),
              mTop(top),
              mRight(right),
              mBottom(bottom),
              mLeft(left)
        {
        }

        virtual ~FrameRectangle() {}

        virtual void init()
        {
            float hwidth = mWidth / 2.0f;
            float hheight = mHeight / 2.0f;

            mVertices[0].x = -hwidth;
            mVertices[0].y = -hheight;
            mVertices[0].z = 0.0f;
            mVertices[1].x = -hwidth + mLeft;
            mVertices[1].y = -hheight;
            mVertices[1].z = 0.0f;
            mVertices[2].x = hwidth - mRight;
            mVertices[2].y = -hheight;
            mVertices[2].z = 0.0f;
            mVertices[3].x = hwidth;
            mVertices[3].y = -hheight;
            mVertices[3].z = 0.0f;

            mVertices[4].x = -hwidth;
            mVertices[4].y = -hheight + mBottom;
            mVertices[4].z = 0.0f;
            mVertices[5].x = -hwidth + mLeft;
            mVertices[5].y = -hheight + mBottom;
            mVertices[5].z = 0.0f;
            mVertices[6].x = hwidth - mRight;
            mVertices[6].y = -hheight + mBottom;
            mVertices[6].z = 0.0f;
            mVertices[7].x = hwidth;
            mVertices[7].y = -hheight + mBottom;
            mVertices[7].z = 0.0f;

            mVertices[8].x = -hwidth;
            mVertices[8].y = hheight - mTop;
            mVertices[8].z = 0.0f;
            mVertices[9].x = -hwidth + mLeft;
            mVertices[9].y = hheight - mTop;
            mVertices[9].z = 0.0f;
            mVertices[10].x = hwidth - mRight;
            mVertices[10].y = hheight - mTop;
            mVertices[10].z = 0.0f;
            mVertices[11].x = hwidth;
            mVertices[11].y = hheight - mTop;
            mVertices[11].z = 0.0f;

            mVertices[12].x = -hwidth;
            mVertices[12].y = hheight;
            mVertices[12].z = 0.0f;
            mVertices[13].x = -hwidth + mLeft;
            mVertices[13].y = hheight;
            mVertices[13].z = 0.0f;
            mVertices[14].x = hwidth - mRight;
            mVertices[14].y = hheight;
            mVertices[14].z = 0.0f;
            mVertices[15].x = hwidth;
            mVertices[15].y = hheight;
            mVertices[15].z = 0.0f;

            float vrate = mTop / (mTop + mBottom);
            float hrate = mLeft / (mLeft + mRight);

            mUvs[0].x = 0.0f;
            mUvs[0].y = 1.0f;
            mUvs[1].x = hrate;
            mUvs[1].y = 1.0f;
            mUvs[2].x = hrate;
            mUvs[2].y = 1.0f;
            mUvs[3].x = 1.0f;
            mUvs[3].y = 1.0f;

            mUvs[4].x = 0.0f;
            mUvs[4].y = vrate;
            mUvs[5].x = hrate;
            mUvs[5].y = vrate;
            mUvs[6].x = hrate;
            mUvs[6].y = vrate;
            mUvs[7].x = 1.0f;
            mUvs[7].y = vrate;

            mUvs[8].x = 0.0f;
            mUvs[8].y = vrate;
            mUvs[9].x = hrate;
            mUvs[9].y = vrate;
            mUvs[10].x = hrate;
            mUvs[10].y = vrate;
            mUvs[11].x = 1.0f;
            mUvs[11].y = vrate;

            mUvs[12].x = 0.0f;
            mUvs[12].y = 0.0f;
            mUvs[13].x = hrate;
            mUvs[13].y = 0.0f;
            mUvs[14].x = hrate;
            mUvs[14].y = 0.0f;
            mUvs[15].x = 1.0f;
            mUvs[15].y = 0.0f;

            for (int r = 0; r < 16; r++)
            {
                mIndices[r * 6] = r;
                mIndices[r * 6 + 1] = r + 1;
                mIndices[r * 6 + 2] = r + 4 + 1;

                mIndices[r * 6 + 3] = r;
                mIndices[r * 6 + 4] = r + 4 + 1;
                mIndices[r * 6 + 5] = r + 4;
            }
        }
        virtual void cleanup() {}

        virtual void *getVertices() { return mVertices; }
        virtual unsigned int getNumVertices() { return 16; }
        virtual unsigned int getVerticesBufferSize() { return 16 * sizeof(Vector3); }
        virtual void *getIndices() { return mIndices; }
        virtual unsigned int getNumIndices() { return 96; }
        virtual unsigned int getIndicesBufferSize() { return 96 * sizeof(int); }
        virtual void *getUvs() { return mUvs; }
        virtual unsigned int getNumUvs() { return 16; }
        virtual unsigned int getUvsBufferSize() { return 16 * sizeof(Vector2); }

    protected:
        float mWidth;
        float mHeight;
        float mTop;
        float mRight;
        float mBottom;
        float mLeft;

        Vector3 mVertices[16];
        int mIndices[96];
        Vector2 mUvs[16];
    };

}; // namespace S3DMath

#endif // S3DMATH_MESH_FRAMERECTANGLE_H
