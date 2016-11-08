#ifndef RESOURCE_H
#define RESOURCE_H

#include <QString>
#include <QPixmap>
#include <memory>

struct R
{
    
    QString res_dir;
    
    QPixmap fast_cannon_1;
    QPixmap fast_cannon_2;
    QPixmap fast_cannon_3;
    
    QString get(const char *val);
    
    R();
    
};

#endif // RESOURCE_H


