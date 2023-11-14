#ifndef S3DMATH_MATERIAL_H
#define S3DMATH_MATERIAL_H

#include "S3DMath/MathematicsTypes.h"

namespace S3DMath
{
    struct Material
    {
        Vector4 color;
        int textureId;
        int shaderId;
        bool opaque;

        void *userData;
    };
}

#endif // S3DMATH_MATERIAL_H
