/*
 * @Author: xixi_
 * @Date: 2025-04-07 19:03:45
 * @LastEditors: xixi_
 * @LastEditTime: 2025-04-30 00:46:56
 * @FilePath: /Test/CompoundClip/Src/MainWindow.cpp
 * Copyright (c) 2020-2025 by xixi_ , All Rights Reserved.
 */

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *Parent)
    : QMainWindow(Parent)
{
    /* 标题 */
    setWindowTitle("熙柠剪辑 - 复合片段");

    /* 初始化 */
    M_CentralWidget = new QWidget();
    M_CentralWidgetLayout = new QVBoxLayout();
    M_CompoundItemPath = new QWidget();
    M_CompoundItemPathLayout = new QHBoxLayout();
    M_Back = new QPushButton("主时间线");
    M_ItemView = new ItemView();
    M_RootCompoundClip = new CompoundClip();
    /**********************************************************************************************************/

    /* 初始化记录 */
    M_RootCompoundClip->SetParentCompoundClip(NULL); /* NB!根节点一定要设置为空 */
    M_RootCompoundClip->SetItemScene(new ItemScene());
    M_CurrCompoundClip = M_RootCompoundClip; /* 第一次时,当前的就是根的 */

    /* 顶部路径 */
    M_CompoundItemPath->setFixedHeight(35); /* 固定路径高度 */

    /* 路径布局 */
    M_CompoundItemPathLayout->setContentsMargins(0, 0, 0, 0);
    M_CompoundItemPathLayout->setSpacing(0);
    M_CompoundItemPathLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    M_CompoundItemPathLayout->addWidget(M_Back);
    M_CompoundItemPathLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    /* 返回按钮 */
    M_Back->hide();

    /* 图元视图 */
    M_ItemView->SetScene(M_RootCompoundClip->GetItemScene()); /* 设置场景 */
    /**********************************************************************************************************/

    /* 设置布局 */
    /* 布局 */
    M_CentralWidgetLayout->addWidget(M_CompoundItemPath);
    M_CentralWidgetLayout->addWidget(M_ItemView); /* 添加进布局 */
    M_CompoundItemPath->setLayout(M_CompoundItemPathLayout);

    /* 设置属性 */
    setCentralWidget(M_CentralWidget); /* 设置中心控件 */
    M_CentralWidget->setLayout(M_CentralWidgetLayout);
    /**********************************************************************************************************/
    /* 信号槽 */
    connect(M_ItemView, &ItemView::RequestCreateComplexClip, this, &MainWindow::TryCreateCompoundItem);
    connect(M_ItemView, &ItemView::RequestUnComplexClip, this, &MainWindow::TryUnCompoundItem);
    connect(M_Back, &QPushButton::clicked, this, &MainWindow::Back);
    /**********************************************************************************************************/
}

MainWindow::~MainWindow()
{
    delete M_RootCompoundClip; /* 释放根节点 */
    M_RootCompoundClip = NULL;
}

void MainWindow::TryCreateCompoundItem(QList<QGraphicsItem *> ClipList)
{
    /* New一个复合片段 */
    CompoundClip *NewCompoundClip = new CompoundClip(); /* 复合片段 */
    ItemScene *NewItemScene = new ItemScene();          /* 场景 */

    /* 逐一添加进新的复合片段 */
    foreach (QGraphicsItem *Item, ClipList)
    {
        /* NB!创建时遇到复合片段,必须重新设置父复合片段,否则返回场景有错误 */
        if (Item->type() == 114514)
        {
            CompoundClip *TmpCompoundClip = qgraphicsitem_cast<CompoundClip *>(Item);
            TmpCompoundClip->SetParentCompoundClip(NewCompoundClip);
        }
        NewItemScene->addItem(Item); /* 普通图元无需处理父级 */
    }

    /* 设置新复合片段属性属性 */
    NewCompoundClip->SetItemName(QString("复合图元 %1").arg(++M_Count)); /* 设置名称 */
    NewCompoundClip->SetParentCompoundClip(M_CurrCompoundClip);          /* 设置父复合片段 */
    NewCompoundClip->SetItemScene(NewItemScene);                         /* 设置场景 */
    NewCompoundClip->SetWidth(150);                                      /* 宽度 */
    NewCompoundClip->SetHeight(80);                                      /* 高度 */
    NewCompoundClip->SetBackgroundColor(QColor(255, 0, 255));            /* 颜色 */

    /* 更新 */
    M_CurrCompoundClip->AddChild(NewCompoundClip); /* 追加到当前复合片段子复合片段列表 */
    M_ItemView->AddItem(NewCompoundClip);          /* 添加到当前场景 */

    /* 链接信号槽 */
    connect(NewCompoundClip, &CompoundClip::DoubleClick, this, &MainWindow::TryShowCompoundItem);
}

void MainWindow::TryShowCompoundItem(CompoundClip *Item)
{
    M_ItemView->SetScene(Item->GetItemScene()); /* 设置新场景 */
    M_CurrCompoundClip = Item;                  /* 更新指向 */

    /* 更新路径 */
    QString ParentName = M_CurrCompoundClip->GetParent()->GetItemName();                  /* 获取父级名称 */
    M_Back->setText(QString("< %1").arg(ParentName.isEmpty() ? "主时间线" : ParentName)); /* 设置路径 */
    M_Back->show();                                                                       /* 返回按钮使能 */
}

void MainWindow::TryUnCompoundItem(QGraphicsItem *Item)
{
    /* 是否为复合片段 */
    if (Item->type() != 114514)
    {
        return;
    }

    /* 获取要打散的复合片段 */
    CompoundClip *TmpCompoundClip = qgraphicsitem_cast<CompoundClip *>(Item);
    M_CurrCompoundClip->RemoveChild(TmpCompoundClip);

    /* 逐一添加进原复合片段的父场景 */
    foreach (QGraphicsItem *Item, TmpCompoundClip->GetItemScene()->items())
    {
        /* NB!打散时遇到复合片段,必须重新设置父复合片段,否则会崩溃 */
        if (Item->type() == 114514)
        {
            CompoundClip *TmpCompoundItem = qgraphicsitem_cast<CompoundClip *>(Item);
            TmpCompoundItem->SetParentCompoundClip(M_CurrCompoundClip->GetParent()); /* 更新父复合片段 */
            TmpCompoundItem->setParent(M_CurrCompoundClip->GetParent()->GetItemScene());
        }

        /* 添加到新场景 */
        M_ItemView->AddItem(Item);
    }

    /* 清理 */
    M_ItemView->RemoveItem(Item); /* 从当前复合片段的场景中移除 */
    delete Item;                  /* 删除掉 */
}

void MainWindow::Back()
{
    /* 当前父级是否为根节点 */
    if (M_CurrCompoundClip->GetParent() != NULL)
    {
        M_ItemView->SetScene(M_CurrCompoundClip->GetParent()->GetItemScene());
        M_CurrCompoundClip = M_CurrCompoundClip->GetParent();
    }

    /* 路径显示 */
    if (M_CurrCompoundClip->GetParent())
    {
        QString ParentName = M_CurrCompoundClip->GetParent()->GetItemName();                    /* 获取父级路径 */
        M_Back->setText(ParentName.isEmpty() ? "< 主时间线" : QString("< %1").arg(ParentName)); /* 设置路径 */
    }
    else
    {
        M_Back->setText("主时间线");
        M_Back->hide();
    }
}
