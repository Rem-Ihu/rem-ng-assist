#ifndef TEST_H
#define TEST_H

#include <QList>
#include <QBarSet>

namespace TestRun
{
    //all Utilities QSets that are going to be created
    QBarSet *createBrakeSet();
    QBarSet *createFrontTireSet();
    QBarSet *createRearTireSet();
    QBarSet *createSuspensionSet();
    QStringList createRunCategories();

    //this is unknown :(
    //actuall documentation says that qreal is double for Qt
    //and in the parenthesis it takes everything from QList and QBarSet and adds all the
    //list elements to get the total sum.
    qreal totalSum(const QList<QBarSet *> &setList);
}

#endif // UTILITIES_H
