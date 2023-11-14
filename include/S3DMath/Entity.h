#ifndef S3DMATH_ENTITY_H
#define S3DMATH_ENTITY_H

#include "GeometricNode.h"
#include "Mesh.h"
#include "Material.h"

namespace S3DMath
{
    class Cluster;

    class Entity
    {
        friend class Cluster;

    public:
        Entity()
            : mNeedStateUpdate(true),
              mMesh(NULL),
              mMaterial(NULL),
              mUserData(NULL)
        {
            mNode.setUserData(this);
        }

        virtual ~Entity() {}

        Mesh *getMesh() { return mMesh; }
        void setMesh(Mesh *mesh) { mMesh = mesh; }

        Material *getMaterial() { return mMaterial; }
        void setMaterial(Material *mat) { mMaterial = mat; }

        bool needUpdateState() { return mNeedStateUpdate; }
        virtual void updateState();

        void addChild(Entity *child);
        void removeChild(Entity *child);

        void setLocalPosition(const Vector3 &pos);
        const Vector3 *getLocalPosition() const { return mNode.getLocalPosition(); }
        void setLocalRotation(const Quaternion4 &rot);
        const Quaternion4 *getLocalOrientation() const { return mNode.getLocalOrientation(); }
        void setLocalScale(const Vector3 &scl);
        const Vector3 *getLocalScale() const { return mNode.getLocalScale(); }

        const Vector3 *getGlobalPosition() const { return mNode.getGlobalPosition(); }
        const Quaternion4 *getGlobalOrientation() const { return mNode.getGlobalOrientation(); }
        const Vector3 *getGlobalScale() const { return mNode.getGlobalScale(); }

        float getDiffFromCamera() { return mDiffFromCamera; }
        void setDiffFromCamera(const float diff) { mDiffFromCamera = diff; }

    protected:
        S3DMath::GeometricNode mNode;
        bool mNeedStateUpdate;

        Mesh *mMesh;
        Material *mMaterial;

        float mDiffFromCamera;
        void *mUserData;
    };
}

#endif // S3DMATH_ENTITY_H
