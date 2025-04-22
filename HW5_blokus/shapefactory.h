#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include <QVector>
#include "shape.h"

class ShapeFactory
{
public:
    ShapeFactory();
    static QVector<Shape*> PremadeShapes();
};

#endif // SHAPEFACTORY_H
