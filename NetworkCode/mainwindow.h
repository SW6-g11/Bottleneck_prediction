#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCheckBox>
#include <QFileDialog>
#include <QLabel>
#include <QPixmap>
#include <QFileInfo>
#include <QRadioButton>
#include <QMessageBox>
#include <QInputDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
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
    void simulateProcessingOne();
    void simulateProcessingTwo();

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

    QRadioButton* findNextAvailableRadioButton(QRadioButton* startRadioButton);

    void simulateProcessingThree(int barValue);

    QRadioButton* lastCheckedRadioButton;
};
#endif // MAINWINDOW_H
