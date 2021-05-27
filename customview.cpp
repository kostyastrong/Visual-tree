#include "customview.h"


CustomView::CustomView(QWidget *parent) : QGraphicsView(parent)
{

}

void CustomView::wheelEvent(QWheelEvent *event)
{
     setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
     double scaleFactor = 1.15;
     if (event->delta() > 0) {  // move forward
         scale(scaleFactor, scaleFactor);  // in x- and y- directions
     } else {
         scale(1/scaleFactor, 1/scaleFactor);
     }

}
