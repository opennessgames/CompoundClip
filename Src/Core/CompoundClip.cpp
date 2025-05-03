/*
 * @Author: xixi_
 * @Date: 2025-04-07 19:10:01
 * @LastEditors: xixi_
 * @LastEditTime: 2025-04-08 00:50:13
 * @FilePath: /Xncut/Test/CompoundClip/Src/Core/TimeLineTrackCompoundItem.cpp
 * Copyright (c) 2020-2025 by xixi_ , All Rights Reserved.
 */

#include "CompoundClip.h"

CompoundClip::CompoundClip(QGraphicsItem *Parent) : Clip(Parent)
{
}

CompoundClip::~CompoundClip()
{
    delete M_ItemScene;
    M_ItemScene = NULL;

    foreach (QGraphicsItem *Item, M_ChildItems)
    {
        Item = NULL;
    }

    M_ChildItems.clear();
}

void CompoundClip::SetParentCompoundClip(CompoundClip *Parent)
{
    M_Parent = Parent;
}

void CompoundClip::SetItemScene(ItemScene *Scene)
{
    M_ItemScene = Scene;
}

void CompoundClip::AddChild(CompoundClip *ChildItem)
{
    M_ChildItems.append(ChildItem);
}

void CompoundClip::RemoveChild(CompoundClip *ChildItem)
{
    M_ChildItems.removeOne(ChildItem);
}

ItemScene *CompoundClip::GetItemScene()
{
    return M_ItemScene;
}

CompoundClip *CompoundClip::GetParent()
{
    return M_Parent;
}

void CompoundClip::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *Event)
{
    emit DoubleClick(this);
}

int CompoundClip::type() const
{
    return 114514;
}
