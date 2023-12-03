
#include "S3DMath/RenderList.h"

#include "S3DMath/Mesh.h"
#include "S3DMath/Material.h"
#include "S3DMath/Entity.h"

namespace S3DMath
{
    bool less(Entity *&v1, Entity *&v2)
    {
        return v1->getDiffFromCamera() < v2->getDiffFromCamera();
    }

    bool greater(Entity *&v1, Entity *&v2)
    {
        return v1->getDiffFromCamera() > v2->getDiffFromCamera();
    }

    void RenderList::sort(const Vector3 &cameraPosition)
    {
        Mesh *mesh;
        Material *mat;

        mOpaqueSortedList.clear();
        mNotOpaqueSortedList.clear();

        float diff;

        for (auto ite = mRegisteredList.begin(); ite != mRegisteredList.end(); ite++)
        {
            mesh = (*ite)->getMesh();
            mat = (*ite)->getMaterial();
            if (mesh == NULL || mat == NULL)
                continue;

            if (mat->isOpaque())
            {
                mOpaqueSortedList.push_back((*ite));
            }
            else
            {
                mNotOpaqueSortedList.push_back((*ite));
            }
            diff = (*((*ite)->getGlobalPosition()) - cameraPosition).length();
            (*ite)->setDiffFromCamera(diff);
        }

        mOpaqueSortedList.sort(less);
        mNotOpaqueSortedList.sort(greater);
    }

}; // namespace S3DMath
