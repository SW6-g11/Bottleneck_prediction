#include "graphLoader.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::openDirectory);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::generateGraph);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::openImage);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::runAlgorithms);

    // Connect checkbox state changed signal to the slot
    connect(ui->radioButton, &QRadioButton::clicked, this, &MainWindow::radioButtonClicked);
    connect(ui->radioButton_2, &QRadioButton::clicked, this, &MainWindow::radioButtonClicked);
    connect(ui->radioButton_3, &QRadioButton::clicked, this, &MainWindow::radioButtonClicked);
    connect(ui->radioButton_4, &QRadioButton::clicked, this, &MainWindow::radioButtonClicked);
    connect(ui->radioButton_5, &QRadioButton::clicked, this, &MainWindow::radioButtonClicked);

    // Initialize the QLabel with width and height set to 0
    ui->label->setFixedSize(0, 0);
    ui->progressBar->setValue(0);
    ui->progressBar_2->setValue(0);
    ui->progressBar_3->setValue(0);

    // Disable all radio buttons initially
    QList<QRadioButton*> radioButtons = ui->centralwidget->findChildren<QRadioButton*>();
    for (QRadioButton *radioButton : radioButtons) {
        radioButton->setEnabled(false);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openDirectory()
{
    // Open a directory dialog to select a directory
    QString directoryPath = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    // Check if a directory was selected
    if (!directoryPath.isEmpty()) {
        bool ok;
        int day = QInputDialog::getInt(this, tr("Input Number"), tr("Please enter a number from 1 to 7:"), 1, 1, 7, 1, &ok);
        // Check if the user clicked OK and entered a valid number
        if (ok) {
            // Call the processDataForDay function on the instance
            graphLoader::processDataForDay(directoryPath, day);
        }
    }
}

void MainWindow::openImage()
{
    if (ui->radioButton_5->property("imagePath").toString().isEmpty()) {
        QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("All Files (*.*)"));
        if (!filePath.isEmpty()) {
            QPixmap image(filePath);
            ui->label->setPixmap(image);
            QSize imageSize = image.size();
            ui->label->setFixedSize(imageSize);

            // Find the next available radio button starting from radio button 1
            QRadioButton* nextRadioButton = nullptr;

            // Check if no radio button is currently checked
            if (!ui->radioButton->isChecked() && !ui->radioButton_2->isChecked() &&
                !ui->radioButton_3->isChecked() && !ui->radioButton_4->isChecked() &&
                !ui->radioButton_5->isChecked()) {
                nextRadioButton = ui->radioButton; // If no radio button is checked, start from radio button 1
            } else {
                // Otherwise, find the next available radio button
                QList<QRadioButton*> radioButtons = { ui->radioButton_2, ui->radioButton_3,
                                                      ui->radioButton_4, ui->radioButton_5 };
                for (QRadioButton* radioButton : radioButtons) {
                    if (!radioButton->isChecked()) {
                        nextRadioButton = radioButton;
                        break;
                    }
                }
            }

            // Store the file path and size as properties of the radio button
            if (nextRadioButton != nullptr) {
                QString currentImagePath = nextRadioButton->property("imagePath").toString();
                if (currentImagePath.isEmpty()) {
                    // No image associated, this radio button is available
                    nextRadioButton->setProperty("imagePath", filePath);
                    nextRadioButton->setProperty("imageSize", imageSize);
                    nextRadioButton->setEnabled(true); // Enable the radio button
                    nextRadioButton->setChecked(true); // Automatically check the radio button
                } else {
                    // Radio button already has an image associated, try finding the next available one
                    QRadioButton* availableRadioButton = nullptr;
                    for (int i = 2; i <= 5; ++i) { // Start checking from radio button 2
                        QString radioButtonName = QString("radioButton_%1").arg(i);
                        availableRadioButton = findChild<QRadioButton*>(radioButtonName);

                        // If the radio button is available, break out of the loop
                        if (availableRadioButton && !availableRadioButton->isChecked() && availableRadioButton->property("imagePath").toString().isEmpty()) {
                            break;
                        }
                    }

                    // Check if an available radio button was found
                    if (availableRadioButton) {
                        // Assign the image path and size to the available radio button
                        availableRadioButton->setProperty("imagePath", filePath);
                        availableRadioButton->setProperty("imageSize", imageSize);
                        availableRadioButton->setEnabled(true); // Enable the radio button
                        availableRadioButton->setChecked(true); // Automatically check the radio button
                    } else {
                        // No available radio button found, display a message or handle accordingly
                        qDebug() << "No available radio button found.";
                    }
                }
            } else {
                // No available radio button found, display a message or handle accordingly
                qDebug() << "No available radio button found.";
            }
        }
    } else {
        // Display a message indicating that all radio buttons are occupied
        QMessageBox::information(this, tr("All Radio Buttons Occupied"),
                                 tr("All radio buttons are occupied. Cannot load more images."));
    }
}


QRadioButton* MainWindow::findNextAvailableRadioButton(QRadioButton* startRadioButton)
{
    // Iterate over the radio buttons starting from the given one
    QList<QRadioButton*> radioButtons = { ui->radioButton_2, ui->radioButton_3, ui->radioButton_4, ui->radioButton_5 };
    for (QRadioButton* radioButton : radioButtons) {
        // If the radio button is not checked, it's available for loading an image
        if (radioButton && !radioButton->isChecked()) {
            return radioButton;
        }
    }
    // No available radio button found
    return nullptr;
}


void MainWindow::radioButtonClicked(bool checked)
{
    // Get the sender radiobutton
    QRadioButton *radioButton = qobject_cast<QRadioButton*>(sender());
    if (!radioButton || !checked)
        return;

    // Get the image path associated with the clicked radiobutton
    QString imagePath = radioButton->property("imagePath").toString();
    if (!imagePath.isEmpty()) {
        // Load the image associated with the clicked radiobutton
        QPixmap image(imagePath);

        // Retrieve the size of the image from the clicked radio button
        QSize imageSize = radioButton->property("imageSize").toSize();

        // Resize the image to the stored size
        image = image.scaled(imageSize);

        // Set the image to the QLabel
        ui->label->setPixmap(image);

        // Adjust the size of the QLabel to fit the image
        ui->label->setFixedSize(imageSize);

        // Uncheck other radiobuttons (1 to 5) if they are checked
        QList<QRadioButton*> radioButtons = ui->centralwidget->findChildren<QRadioButton*>();
        for (QRadioButton *otherRadioButton : radioButtons) {
            if (otherRadioButton != radioButton && otherRadioButton->isChecked()) {
                otherRadioButton->setChecked(false);
            }
        }
    }
}

void MainWindow::simulateProcessingOne()
{
    int currentValue = ui->progressBar->value();
    if (currentValue < 100) {
        ui->progressBar->setValue(currentValue + 20);
    }
}

void MainWindow::generateGraph()
{
    // Call the function to generate the graph (not implemented yet)
    // replace `functionToGenerateGraph()` with your actual function call
    // functionToGenerateGraph();
}

void MainWindow::simulateProcessingTwo()
{
    int currentValue = ui->progressBar_2->value();
    if (currentValue < 100) {
        ui->progressBar_2->setValue(currentValue + 25);
    }
}

void MainWindow::runAlgorithms(){

    ui->progressBar_3->setValue(0);
    ui->pushButton_4->setEnabled(false);
    QList<QCheckBox*> checkboxes = findChildren<QCheckBox*>();
    for (QCheckBox* checkbox : checkboxes) {
        checkbox->setEnabled(false);
    }

    int checkedCount = 0;
    int barValue = 100;
    for (QCheckBox* checkbox : checkboxes) {
        if (checkbox->isChecked()) {
            checkedCount++;
        }
    }
    if(checkedCount == 0){
        ui->pushButton_4->setEnabled(true);
        for (QCheckBox* checkbox : checkboxes) {
            checkbox->setEnabled(true);
        }
        return;
    }
    if(checkedCount != 0){
            barValue =  100 / checkedCount;
    }

    if(ui->checkBox->isChecked()){
    simulateProcessingThree(barValue);
    }

    if(ui->checkBox_2->isChecked()){
    simulateProcessingThree(barValue);
    }

    if(ui->checkBox_3->isChecked()){
    simulateProcessingThree(barValue);
    }

    if(ui->checkBox_4->isChecked()){
    simulateProcessingThree(barValue);
    }

    if(ui->progressBar_3->value() != 100){
        ui->progressBar_3->setValue(100);
    }

    ui->pushButton_4->setEnabled(true);
    for (QCheckBox* checkbox : checkboxes) {
        checkbox->setEnabled(true);
    }

}

void MainWindow::simulateProcessingThree(int barValue){
    int currentValue = ui->progressBar_3->value();
    if (currentValue < 100) {
        ui->progressBar_3->setValue(currentValue + barValue);
    }
}
