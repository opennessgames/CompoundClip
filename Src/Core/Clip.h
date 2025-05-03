/*
 * @Author: xixi_
 * @Date: 2025-04-07 19:08:02
 * @LastEditors: xixi_
 * @LastEditTime: 2025-04-30 00:24:33
 * @FilePath: /Test/CompoundClip/Src/Core/Clip.h
 * Copyright (c) 2020-2025 by xixi_ , All Rights Reserved.
 */

#ifndef CLIP_H
#define CLIP_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

class Clip : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Clip(QGraphicsItem *Parent = NULL);

    /* 设置宽度 */
    void SetWidth(int Width);

    /* 设置高度 */
    void SetHeight(int Height);

    /* 设置背景颜色 */
    void SetBackgroundColor(QColor Color);

    /* 设置名称 */
    void SetItemName(QString Name);

    /* 获取片段名称 */
    QString GetItemName();

protected:
    /* 重载事件 */
    /* 绘制区域 */
    QRectF boundingRect() const override;

    /* 绘制 */
    void paint(QPainter *Painter, const QStyleOptionGraphicsItem *Option, QWidget *Widget) override;

private:
    int M_Width = -1;                        /* 宽度 */
    int M_Height = -1;                       /* 高度 */
    QColor M_ItemColor = QColor(0, 0, 0, 0); /* 颜色 */
    QString M_ItemName = "";                 /* 剪辑名称 */
};

#endif // CLIP_H
