/*
 * @Author: xixi_
 * @Date: 2025-04-07 19:13:53
 * @LastEditors: xixi_
 * @LastEditTime: 2025-04-09 21:09:16
 * @FilePath: /Xncut/Test/CompoundClip/Src/TimeLineTrackItemView.cpp
 * Copyright (c) 2020-2025 by xixi_ , All Rights Reserved.
 */

#include "ItemView.h"
#include <QGraphicsRectItem>

ItemView::ItemView(QWidget *Parent) : QGraphicsView(Parent)
{
    setDragMode(QGraphicsView::RubberBandDrag);
    /* 初始化 */
    M_Menu = new QMenu(this);
    M_AddItemAction = new QAction(this);      /* 添加图元 */
    M_CreateCompoundClip = new QAction(this); /* 新建复合片段 */
    M_UnCompoundClip = new QAction(this);     /* 打散复合片段 */

    /* 设置动作文本 */
    M_AddItemAction->setText("添加矩形");
    M_CreateCompoundClip->setText("新建复合片段");
    M_UnCompoundClip->setText("打散复合片段");

    /* 添加动作 */
    M_Menu->addAction(M_AddItemAction);
    M_Menu->addAction(M_CreateCompoundClip);
    M_Menu->addAction(M_UnCompoundClip);

    /* 信号槽 */
    connect(M_Menu, &QMenu::triggered, this, &ItemView::MenuTriggered);
}

void ItemView::SetScene(ItemScene *Scene)
{
    M_TrackItemScene = Scene;
    setScene(M_TrackItemScene);
}

void ItemView::AddItem()
{
    QGraphicsRectItem *NewItem = new QGraphicsRectItem();
    NewItem->setRect(0, 0, 100, 100);
    NewItem->setBrush(QColor(255, 0, 0));
    NewItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    M_TrackItemScene->addItem(NewItem);
}

void ItemView::RemoveItem(QGraphicsItem *Item)
{
    M_TrackItemScene->removeItem(Item);
    M_TrackItemScene->setParent(NULL);
}

void ItemView::AddItem(QGraphicsItem *Item)
{
    M_TrackItemScene->addItem(Item);
}

void ItemView::MenuTriggered(QAction *Action)
{
    if (Action == M_AddItemAction)
    {
        AddItem();
    }
    else if (Action == M_CreateCompoundClip)
    {
        emit RequestCreateComplexClip(M_TrackItemScene->selectedItems());
    }
    else if (Action == M_UnCompoundClip)
    {
        emit RequestUnComplexClip(M_TrackItemScene->selectedItems().first());
    }
}

void ItemView::contextMenuEvent(QContextMenuEvent *Event)
{
    /* 预先移除掉打散复合片段 */
    M_Menu->removeAction(M_UnCompoundClip);

    /* 选中个数为0,只能创建图元 */
    if (M_TrackItemScene->selectedItems().count() <= 0)
    {
        M_Menu->removeAction(M_CreateCompoundClip);
    }
    else
    {
        M_Menu->addAction(M_CreateCompoundClip);
        if (M_TrackItemScene->selectedItems().first()->type() == 114514)
        {
            M_Menu->addAction(M_UnCompoundClip);
        }
    }
    M_Menu->exec(Event->globalPos()); /* 弹出菜单 */
    QGraphicsView::contextMenuEvent(Event);
}
