/*
 * @Author: xixi_
 * @Date: 2025-04-07 19:09:28
 * @LastEditors: xixi_
 * @LastEditTime: 2025-04-30 00:24:54
 * @FilePath: /Test/CompoundClip/Src/Core/CompoundClip.h
 * Copyright (c) 2020-2025 by xixi_ , All Rights Reserved.
 */

#ifndef COMPOUND_CLIP_H
#define COMPOUND_CLIP_H

#include "Clip.h"
#include "../ItemScene.h"

class CompoundClip : public Clip
{
    Q_OBJECT
public:
    explicit CompoundClip(QGraphicsItem *Parent = NULL);
    ~CompoundClip();

    /* 设置父级复合片段 */
    void SetParentCompoundClip(CompoundClip *Parent);

    /* 设置场景 */
    void SetItemScene(ItemScene *Scene);

    /* 添加子复合片段到列表 */
    void AddChild(CompoundClip *ChildItem);

    /* 移除子复合片段到列表 */
    void RemoveChild(CompoundClip *ChildItem);

    /* 获取场景 */
    ItemScene *GetItemScene();

    /* 设置父复合片段 */
    CompoundClip *GetParent();

protected:
    /* 重载事件 */
    /* 双击事件 */
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *Event) override;

    /* 类型 */
    int type() const override;

signals:
    /* 双击信号 */
    void DoubleClick(CompoundClip *Item);

private:
    /* NB!这里public是为了方便! 最好还是private,设置公有接口 */
    ItemScene *M_ItemScene = NULL;           /* 场景 */
    QList<CompoundClip *> M_ChildItems = {}; /* 子复合片段 */
    CompoundClip *M_Parent = NULL;           /* 父复合片段 */
};

#endif // COMPOUND_CLIP_H
