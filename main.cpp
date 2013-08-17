#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"

#include "stepdetector.h"
#include <QAccelerometer>
#include <QGraphicsObject>

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/GetOffYourAss/main.qml"));
    viewer.showExpanded();

    QObject *rootObject = viewer.rootObject();

    QAccelerometer sensor;
    StepDetector filter;
    sensor.setProperty("alwaysOn", true);
    sensor.addFilter(&filter);

    QObject::connect(&filter, SIGNAL(stepDetected()),
                     rootObject, SLOT(stepDetected()));

    QObject::connect(&filter, SIGNAL(trainingStarted()),
                     rootObject, SLOT(trainingStarted()));

    QObject::connect(&filter, SIGNAL(trainingFinished()),
                     rootObject, SLOT(trainingFinished()));

    sensor.start();

    return app->exec();
}
