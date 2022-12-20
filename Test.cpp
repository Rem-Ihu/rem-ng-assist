#include "Test.h"
#include <QCoreApplication>

namespace Test
{

//A bar set contains one data value for each category.
//The first value of a set is assumed to belong to the first category,
//the second one to the second category, and so on. If the set has fewer values
//than there are categories, the missing values are assumed to be located
//at the end of the set. For missing values in the middle of a set,
//the numerical value of zero is used. Labels for zero value sets are not shown.

QBarSet *createBrakeSet()
{
    //set a new bar to be added.
    QBarSet *set = new QBarSet(QCoreApplication::tr("Brakes"));
    //appending values to each individual bar.
    set->append({15.0, 12.0, 8.0, 11.5, 18.7});
    return set;
}

QBarSet *createFrontTireSet()
{
    //set a new bar to be added.
    QBarSet *set = new QBarSet(QCoreApplication::tr("Front Tire"));
    //appending values to each individual bar.
    set->append({9.0, 11.0, 9.0, 7, 12.2});
    return set;
}

QBarSet *createRearTireSet()
{
    //set a new bar to be added.
    QBarSet *set = new QBarSet(QCoreApplication::tr("Rear Tire"));
    //appending values to each individual bar.
    set->append({5.0, 7.6, 9.3, 8, 8.1});
    return set;
}

QBarSet *createSuspensionSet()
{
    //set a new bar to be added.
    QBarSet *set = new QBarSet(QCoreApplication::tr("Suspension"));
    //appending values to each individual bar.
    set->append({5.4, 7.1, 9.3, 12.3, 11.3});
    return set;
}

QStringList createRunCategories()
{
    //set a new list for the names of the different bar groups that are added.
    return QStringList{QCoreApplication::tr("Run1"),
                       QCoreApplication::tr("Run2"),
                       QCoreApplication::tr("Run3"),
                       QCoreApplication::tr("Run4"),
                       QCoreApplication::tr("Run5")};
}

}
