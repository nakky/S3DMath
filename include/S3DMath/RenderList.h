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
#include "S3DMath/Entity.h"

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

        void sortByDistance(const Vector3 &cameraPosition);
        void sortByValue();

        std::list<Entity *> &getOpaqueDistanceSortedList() { return mOpaqueDistanceSortedList; }
        std::list<Entity *> &getNotOpaqueDistanceSortedList() { return mNotOpaqueDistanceSortedList; }
        std::list<Entity *> &getOpaqueValueSortedList() { return mOpaqueValueSortedList; }
        std::list<Entity *> &getNotOpaqueValueSortedList() { return mNotOpaqueValueSortedList; }

    protected:
        std::list<Entity *> mRegisteredList;

        std::list<Entity *> mOpaqueDistanceSortedList;
        std::list<Entity *> mNotOpaqueDistanceSortedList;
        std::list<Entity *> mOpaqueValueSortedList;
        std::list<Entity *> mNotOpaqueValueSortedList;
    };

}; // namespace S3DMath

#endif // S3DMATH_RENDERLIST_H
