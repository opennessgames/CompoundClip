/*
 * @Author: xixi_
 * @Date: 2025-04-07 19:13:53
 * @LastEditors: xixi_
 * @LastEditTime: 2025-04-09 21:13:10
 * @FilePath: /Xncut/Test/CompoundClip/Src/TimeLineTrackItemView.h
 * Copyright (c) 2020-2025 by xixi_ , All Rights Reserved.
 */

#ifndef ITEMVIEW_H
#define ITEMVIEW_H

#include <QGraphicsView>
#include <QMenu>
#include <QContextMenuEvent>
#include "ItemScene.h"
#include <QAction>

class ItemView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ItemView(QWidget *Parent = NULL);

    /* 设置场景 */
    void SetScene(ItemScene *Scene);

    /* 添加图元 */
    void AddItem();

    /* 移除图元 */
    void RemoveItem(QGraphicsItem *Item);

    /* 添加图元 */
    void AddItem(QGraphicsItem *Item);

    /* 视图菜单项被点击 */
    void MenuTriggered(QAction *Action);

protected:
    /* 重载事件 */
    void contextMenuEvent(QContextMenuEvent *Event) override;

signals:
    /* 向时总控发送`创建`复合片段请求 */
    void RequestCreateComplexClip(QList<QGraphicsItem *> ClipList);

    /* 向总控发送`打散`复合片段请求 */
    void RequestUnComplexClip(QGraphicsItem *ComplexClip);

private:
    QMenu *M_Menu = NULL; /* 视图菜单 */
    /* 视图菜单项 */
    QAction *M_AddItemAction = NULL;      /* 添加图元 */
    QAction *M_CreateCompoundClip = NULL; /* 新建复合片段 */
    QAction *M_UnCompoundClip = NULL;     /* 打散复合片段 */

    /* 持有场景 */
    ItemScene *M_TrackItemScene = NULL;
};

#endif // ITEMVIEW_H
