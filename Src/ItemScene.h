/*
 * @Author: xixi_
 * @Date: 2025-04-07 19:13:37
 * @LastEditors: xixi_
 * @LastEditTime: 2025-04-30 00:24:26
 * @FilePath: /Test/CompoundClip/Src/ItemScene.h
 * Copyright (c) 2020-2025 by xixi_ , All Rights Reserved.
 */

#ifndef ITEMSCENE_H
#define ITEMSCENE_H

#include <QGraphicsScene>

class ItemScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit ItemScene(QObject *Parent = NULL);
    ~ItemScene();
};

#endif // ITEMSCENE_H
