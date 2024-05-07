#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <string>
#include <vector>
#include <QMainWindow>
#include <QCheckBox>
#include <QFileDialog>
#include <QLabel>
#include <QPixmap>
#include <QFileInfo>
#include <QRadioButton>
#include <QMessageBox>
#include <QInputDialog>
#include "graphDataStruct.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class QLabel;
class QProgressBar;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static void simulateProcessingOne();
    void simulateProcessingTwo();
    void simulateProcessingThree();
    void simulateProcessingFour();

private slots:
    void openDirectory();
    void generateGraph();
    void openImage();
    void runAlgorithms();

    void radioButtonClicked(bool checked);

private:
    Ui::MainWindow *ui;
    QLabel *imageLabel;
    QProgressBar *progressBar;

    QRadioButton *findNextAvailableRadioButton(QRadioButton *startRadioButton);

    QRadioButton *lastCheckedRadioButton;

    graphDataStruct graphdata;
};
#endif // MAINWINDOW_H
