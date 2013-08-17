#ifndef STEPDETECTOR_H
#define STEPDETECTOR_H

#include <QObject>
#include <QAccelerometerFilter>

QTM_USE_NAMESPACE

#define TRAINING_LENGTH 100

class StepDetector : public QObject, public QAccelerometerFilter
{
    Q_OBJECT
public:
    explicit StepDetector(QObject *parent = 0);
    bool filter(QAccelerometerReading *reading);

signals:
    void trainingStarted();
    void trainingFinished();
    void stepDetected();

public slots:
};

#endif // STEPDETECTOR_H
