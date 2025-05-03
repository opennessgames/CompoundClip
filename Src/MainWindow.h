/*
 * @Author: xixi_
 * @Date: 2025-04-07 19:03:45
 * @LastEditors: xixi_
 * @LastEditTime: 2025-04-30 00:31:03
 * @FilePath: /Test/CompoundClip/Src/MainWindow.h
 * Copyright (c) 2020-2025 by xixi_ , All Rights Reserved.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include "ItemView.h"
#include "Core/CompoundClip.h"
#include <QPushButton>
#include <QGraphicsGridLayout>
#include <QGraphicsLayout>
#include <QGraphicsLinearLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *Parent = NULL);
    ~MainWindow();

    /* 尝试创建复合片段 */
    void TryCreateCompoundItem(QList<QGraphicsItem *> ClipList);

    /* 尝试显示复合片段 */
    void TryShowCompoundItem(CompoundClip *Item);

    /* 尝试打散复合片段 */
    void TryUnCompoundItem(QGraphicsItem *Item);

    /* 返回上一级 */
    void Back();

private:
    /* 中心控件 */
    QWidget *M_CentralWidget = NULL;           /* 中心控件 */
    QVBoxLayout *M_CentralWidgetLayout = NULL; /* 中心控件布局 */
    /**********************************************************************************************************/

    /* 路径部件 */
    QWidget *M_CompoundItemPath = NULL;           /* 显示路径部件 */
    QHBoxLayout *M_CompoundItemPathLayout = NULL; /* 显示路径部件布局 */
    QPushButton *M_Back = NULL;                   /* 返回按钮 */
    /**********************************************************************************************************/

    /* 主视图 */
    ItemView *M_ItemView = NULL; /* 视图 */

    /* 记录复合片段 */
    CompoundClip *M_RootCompoundClip = NULL; /* 根复合片段 */
    CompoundClip *M_CurrCompoundClip = NULL; /* 当前复合片段 */
    /**********************************************************************************************************/

    int M_Count = -1; /* 复合片段计数 */
    /**********************************************************************************************************/
};
#endif // MAINWINDOW_H
