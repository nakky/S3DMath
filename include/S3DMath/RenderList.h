/******************************************************************/
/*!
    @file	RenderList.h
    @brief	Render target container
    @note
    @todo
    @bug

    @author	Naoto Nakamura
    @date	Mar. 10, 2020
*/
/******************************************************************/

#ifndef S3DMATH_RENDERLIST_H
#define S3DMATH_RENDERLIST_H

#include "S3DMath/Common.h"

#include "S3DMath/MathematicsTypes.h"

#include <list>

namespace S3DMath
{
    class Entity;

    class RenderList
    {
    public:
        RenderList() {}

        void add(Entity *entity) { mRegisteredList.push_back(entity); }
        void remove(Entity *entity) { mRegisteredList.remove(entity); }

        void sort(const Vector3 &cameraPosition);

        std::list<Entity *> &getOpaqueSortedList() { return mOpaqueSortedList; }
        std::list<Entity *> &getNotOpaqueSortedList() { return mNotOpaqueSortedList; }

    protected:
        std::list<Entity *> mRegisteredList;
        std::list<Entity *> mOpaqueSortedList;
        std::list<Entity *> mNotOpaqueSortedList;
    };

}; // namespace S3DMath

#endif // S3DMATH_RENDERLIST_H
