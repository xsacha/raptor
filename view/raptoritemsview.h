/* This file is part of the KDE project

   Copyright (C) 2008 Alessandro Diaferia <alediaferia@gmail.com>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
*/ 

#ifndef RAPTORITEMSVIEW_H
#define RAPTORITEMSVIEW_H

#include <QListView>

/**
 * A simple listview with smooth scrolling as base implementation for
 * the main items view of the menu.
 */

class RaptorItemsView : public QListView
{
    Q_OBJECT
    public:
        RaptorItemsView(QWidget *parent = 0);
        ~RaptorItemsView();

        void setOrientation(Qt::Orientation);

    protected:
        int getNewScrollValue(const QRect &rect);

    public slots:
        void smoothScrollTo(const QModelIndex &index);

    private:
        class RaptorItemsViewPrivate;
        RaptorItemsViewPrivate *d;
};
#endif