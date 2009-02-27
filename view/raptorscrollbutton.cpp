/* This file is part of the KDE project

   Copyright (C) 2008 Lukas Appelhans <l.appelhans@gmx.de>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
*/
#include "raptorscrollbutton.h"

#include <plasma/svg.h>

#include <QRectF>
#include <QPainter>
#include <QTimeLine>
#include <QStyleOptionGraphicsItem>

#include <KDebug>

class RaptorScrollButton::Private
{
    public:
        Private(Side s, RaptorScrollButton * button)
          : q(button),
            side(s),
            frame(0)
        {
            svg = new Plasma::Svg(q);
            svg->setImagePath("widgets/raptorarrows");
            svg->setContainsMultipleImages(true);
            timeLine = new QTimeLine(250, button);
        }
        ~Private()
        {}

        RaptorScrollButton * q;
        Side side;
        Plasma::Svg * svg;
        QTimeLine * timeLine;
        int frame;
};
RaptorScrollButton::RaptorScrollButton(Side side, QGraphicsWidget * parent)
  : QGraphicsWidget(parent),
    d(new Private(side, this))
{
    setAttribute(Qt::WA_NoSystemBackground);
    setAcceptHoverEvents(true);
    update();
    installEventFilter(this);
    connect(d->timeLine, SIGNAL(frameChanged(int)), this, SLOT(animatePaint(int)));
}

RaptorScrollButton::~RaptorScrollButton()
{
}

void RaptorScrollButton::paint(QPainter * p, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    //QPainter p(this);
    QRectF r(option->rect);
    
    qreal buttonRatioWidth = 0.7;
    qreal buttonRatioHeight = 0.6;

    p->setRenderHint(QPainter::SmoothPixmapTransform);
    p->setRenderHint(QPainter::Antialiasing);

    r.setSize(QSizeF(contentsRect().size().width() * buttonRatioWidth + d->frame, 
                     contentsRect().size().height() * buttonRatioHeight + d->frame));
    d->svg->resize(r.size());
    r.moveCenter(contentsRect().center());

    if (d->side == Right) {
       d->svg->paint(p, r, "rightarrow");
    }
    else {
       d->svg->paint(p, r, "leftarrow");
    }
}

bool RaptorScrollButton::eventFilter(QObject * watched, QEvent * event)
{
    Q_UNUSED(watched)
    switch(event->type())
    {
        case QEvent::GraphicsSceneHoverEnter:
            d->timeLine->setFrameRange(0, 20);
            d->timeLine->start();
            break;
        case QEvent::GraphicsSceneHoverLeave:
            d->timeLine->stop();
            d->frame = 0;
            update();
            break;
        case QEvent::GraphicsSceneMousePress:
            emit clicked();
            break;
        default:
            break;
    };
    return false;
}

void RaptorScrollButton::animatePaint(int frame)
{
    d->frame = frame;
    update();
}
