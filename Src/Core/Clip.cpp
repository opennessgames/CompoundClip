/*
 * @Author: xixi_
 * @Date: 2025-04-07 19:08:23
 * @LastEditors: xixi_
 * @LastEditTime: 2025-04-08 12:27:10
 * @FilePath: /Xncut/Test/CompoundClip/Src/Core/TimeLineTrackItem.cpp
 * Copyright (c) 2020-2025 by xixi_ , All Rights Reserved.
 */

#include "Clip.h"

Clip::Clip(QGraphicsItem *Parent) : QGraphicsItem(Parent)
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable); /* 开启拖移和被选中 */
    setAcceptHoverEvents(true);                                               /* 接受鼠标指针悬浮 */
    setToolTip("此片段无描述");                                               /* 默认描述 */
}

void Clip::SetWidth(int Width)
{
    M_Width = Width;
}

void Clip::SetHeight(int Height)
{
    M_Height = Height;
}

void Clip::SetBackgroundColor(QColor Color)
{
    M_ItemColor = Color;
}

void Clip::SetItemName(QString Name)
{
    M_ItemName = Name;
}

QString Clip::GetItemName()
{
    return M_ItemName;
}

QRectF Clip::boundingRect() const
{
    return QRectF(0, 0, M_Width, M_Height);
}

void Clip::paint(QPainter *Painter, const QStyleOptionGraphicsItem *Option, QWidget *Widget)
{
    Q_UNUSED(Widget);

    Painter->setBrush(isSelected() ? QColor(2, 25, 55) : M_ItemColor); /* 颜色 */
    Painter->drawRect(boundingRect());                                 /* 绘制矩形 */
    Painter->drawText(5, 0, M_Width - 10, M_Height, 0, M_ItemName);    /* 绘制名称 */
}
