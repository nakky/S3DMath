#ifndef S3DMATH_MATERIAL_H
#define S3DMATH_MATERIAL_H

#include "S3DMath/MathematicsTypes.h"

#include "Resource.h"

namespace S3DMath
{
    class Material : public Resource
    {
    public:
        Material()
            : Resource(),
              mShaderId(0),
              mIsOpaque(false),
              mNeedRender(true)
        {
        }

        virtual ~Material() {}

        virtual const bool needRender() { return mNeedRender; }
        virtual void resetNeedRender() { mNeedRender = false; }

        virtual const short getResourceType() { return RESOURCETYPE_MATERIAL; }

        const int getShaderId() { return mShaderId; }
        void setShaderId(const int shaderId)
        {
            mShaderId = shaderId;
            mNeedRender = true;
        }

        const bool isOpaque() { return mIsOpaque; }
        void setOpaque(const bool opaque)
        {
            mIsOpaque = opaque;
            mNeedRender = true;
        }

    protected:
        int mShaderId;
        bool mIsOpaque;
        bool mNeedRender;
    };
}

#endif // S3DMATH_MATERIAL_H
