/* This file is part of the KDE project

   Copyright (C) 2008 Alessandro Diaferia <alediaferia@gmail.com>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
*/

#ifndef RAPTORITEMDELEGATE_H
#define RAPTORITEMDELEGATE_H

#include <QStyledItemDelegate>

class RaptorItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
    public:
        RaptorItemDelegate(QObject *parent = 0);
        ~RaptorItemDelegate();

        void paint(QPainter *painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
        void setTextColor(const QColor &);


    protected slots:
        void animatePaint(int);

    private:
        class Private;
        Private *d;
};

#endif