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
#include "prompts.h"

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
    void openGraphvizImage(string filePath);
    void simulateProcessingOne(int barValue);
    void simulateProcessingTwo(int barValue);
    void simulateProcessingThree(int barValue);
    void simulateProcessingFour(int barValue);
    void runAlgorithmNoAugmentedNetwork();
    void runAlgorithmOne(Prompts &prompter);
    void runAlgorithmTwo(Prompts &prompter);
    void runAlgorithmThree(Prompts &prompter);
    void runAlgorithmFour(Prompts &prompter);
    std::string promptRouter();
    static MainWindow &getInstance();

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

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QRadioButton *findNextAvailableRadioButton(QRadioButton *startRadioButton);

    QRadioButton *lastCheckedRadioButton;

    graphDataStruct graphdata;

    static MainWindow *instance;
};
#endif // MAINWINDOW_H
