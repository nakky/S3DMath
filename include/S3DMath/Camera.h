#ifndef S3DMATH_CAMERA_H
#define S3DMATH_CAMERA_H

#include "S3DMath/Entity.h"

namespace S3DMath
{
    class Camera : public Entity
    {
    public:
        Camera()
            : Entity()
        {
        }

        virtual ~Camera() {}

        virtual void updateState();

        void ortho(float left, float right, float bottom, float top, float near, float far);
        void perspective(float fovy, float aspect, float near, float far);

        S3DMath::Matrix44 &getProjectionMatrix() { return mProjection; }

    protected:
        S3DMath::Matrix44 mProjection;
    };
}

#endif // S3DMATH_CAMERA_H
