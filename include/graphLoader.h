#ifndef GRAPHLOADER_H
#define GRAPHLOADER_H

#include <QString>

// Forward declaration of MainWindow class
class MainWindow;

class graphLoader
{
public:
   static void processDataForDay(QString& directoryPath, int day);
};

#endif // GRAPHLOADER_H
