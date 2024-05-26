#include "graphmaker.h"
#include "Sheetreader.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SearchableComboBoxDialog.h"
#include <string.h>
#include "SimulatorController.h"
#include "graphviz.h"
#include "SearchableComboBox.h"
#include "prompts.h"
#include "Networkmanipulator.h"
const bool skipQuery = false;

// This gets calculated later
int maxPUVandPaths = 0;
int checkedCount = 0;

MainWindow *MainWindow::instance = nullptr;

// Implement the getInstance() static member function
MainWindow &MainWindow::getInstance()
{
    if (!instance)
    {
        instance = new MainWindow(); // Create a new instance if it doesn't exist
    }
    return *instance;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showMaximized();

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
    ui->progressBar_1->setValue(0);
    ui->progressBar_2->setValue(0);
    ui->progressBar_3->setValue(0);

    // Disable all radio buttons initially
    QList<QRadioButton *> radioButtons = ui->centralwidget->findChildren<QRadioButton *>();
    for (QRadioButton *radioButton : radioButtons)
    {
        radioButton->setEnabled(false);
    }
    ui->pushButton_2->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openDirectory()
{
    // Open a directory dialog to select a directory
    std::string initialDir = "../data/sampleSet";
    if (!std::filesystem::exists(initialDir))
        std::filesystem::create_directory(initialDir);

    QString QinitialDir = QString::fromStdString(initialDir);
    QString directoryPath = QFileDialog::getExistingDirectory(this, tr("Open Directory"), QinitialDir, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    // Check if a directory was selected
    if (!directoryPath.isEmpty())
    {
        bool ok = skipQuery;
        int day = 1;
        if (!skipQuery)
            // TODO: If day doesn't exist??
            day = QInputDialog::getInt(this, tr("Input Number"), tr("Please enter a number indicating which day to be processed:"), 1, 1, INT_MAX, 1, &ok);
        // Check if the user clicked OK and entered a valid number
        if (ok)
        {
            bool limitOk = skipQuery;
            int limit = 0;
            if (!skipQuery)
                limit = QInputDialog::getInt(this, tr("Input Limit"), tr("Please enter a limit of lines from data to be processed:"), 0, 0, INT_MAX, 1, &limitOk);
            // Check if the user clicked OK and entered a valid limit
            if (limitOk)
            {
                // Convert QString to std::string
                std::string directoryPathStdString = directoryPath.toStdString();

                // Create an instance of the Graphmaker class
                Graphmaker graphOne;
                std::cout << "Directory path is: " << directoryPathStdString << std::endl;
                std::cout << "Day is: " << day << std::endl;
                std::cout << "Limit is: " << limit << std::endl;
                // Call processDataForDay with the directory path, day, and limit
                graphOne.processDataForDay(directoryPathStdString, day, limit, SimulatorController::getGraphDataPointer());
                // SimulatorController::addData(SimulatorController::getGraphDataPointer());
                ui->pushButton_2->setEnabled(true);
            }
        }
    }
}

void MainWindow::openImage()
{
    if (ui->radioButton_5->property("imagePath").toString().isEmpty())
    {
        QString filepath = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("All Files (*.*)"));
        string filePath = filepath.toStdString();
        if (!filePath.empty())
        {
            imageSaver(filePath);
        }
    }
}

void MainWindow::imageSaver(string filePath)
{
    QString qFilePath = QString::fromStdString(filePath);
    QPixmap image(qFilePath);
    ui->label->setPixmap(image);
    QSize imageSize = image.size();
    ui->label->setFixedSize(imageSize);

    // Find the next available radio button starting from radio button 1
    QRadioButton *nextRadioButton = nullptr;

    // Check if no radio button is currently checked
    if (!ui->radioButton->isChecked() && !ui->radioButton_2->isChecked() &&
        !ui->radioButton_3->isChecked() && !ui->radioButton_4->isChecked() &&
        !ui->radioButton_5->isChecked())
    {
        nextRadioButton = ui->radioButton; // If no radio button is checked, start from radio button 1
    }
    else
    {
        // Otherwise, find the next available radio button
        QList<QRadioButton *> radioButtons = {ui->radioButton_2, ui->radioButton_3,
                                              ui->radioButton_4, ui->radioButton_5};
        for (QRadioButton *radioButton : radioButtons)
        {
            if (!radioButton->isChecked())
            {
                nextRadioButton = radioButton;
                break;
            }
        }
    }
    // Store the file path and size as properties of the radio button
    if (nextRadioButton != nullptr)
    {
        QString currentImagePath = nextRadioButton->property("imagePath").toString();
        if (currentImagePath.isEmpty())
        {
            // No image associated, this radio button is available
            nextRadioButton->setProperty("imagePath", qFilePath);
            nextRadioButton->setProperty("imageSize", imageSize);
            nextRadioButton->setEnabled(true); // Enable the radio button
            nextRadioButton->setChecked(true); // Automatically check the radio button
        }
        else
        {
            // Radio button already has an image associated, try finding the next available one
            QRadioButton *availableRadioButton = nullptr;
            for (int i = 2; i <= 5; ++i)
            {
                // Start checking from radio button 2
                QString radioButtonName = QString("radioButton_%1").arg(i);
                availableRadioButton = findChild<QRadioButton *>(radioButtonName);
                // If the radio button is available, break out of the loop
                if (availableRadioButton && !availableRadioButton->isChecked() && availableRadioButton->property("imagePath").toString().isEmpty())
                {
                    break;
                }
            }
            // Check if an available radio button was found
            if (availableRadioButton)
            {
                // Assign the image path and size to the available radio button
                availableRadioButton->setProperty("imagePath", qFilePath);
                availableRadioButton->setProperty("imageSize", imageSize);
                availableRadioButton->setEnabled(true); // Enable the radio button
                availableRadioButton->setChecked(true); // Automatically check the radio button
            }
            else
            {
                // No available radio button found, display a message or handle accordingly
                qDebug() << "No available radio button found.";
            }
        }
    }
}

QRadioButton *MainWindow::findNextAvailableRadioButton(QRadioButton *startRadioButton)
{
    // Iterate over the radio buttons starting from the given one
    QList<QRadioButton *> radioButtons = {ui->radioButton_2, ui->radioButton_3, ui->radioButton_4, ui->radioButton_5};
    for (QRadioButton *radioButton : radioButtons)
    {
        // If the radio button is not checked, it's available for loading an image
        if (radioButton && !radioButton->isChecked())
        {
            return radioButton;
        }
    }
    // No available radio button found
    return nullptr;
}

void MainWindow::radioButtonClicked(bool checked)
{
    // Get the sender radiobutton
    QRadioButton *radioButton = qobject_cast<QRadioButton *>(sender());
    if (!radioButton || !checked)
        return;

    // Get the image path associated with the clicked radiobutton
    QString imagePath = radioButton->property("imagePath").toString();
    if (!imagePath.isEmpty())
    {
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
        QList<QRadioButton *> radioButtons = ui->centralwidget->findChildren<QRadioButton *>();
        for (QRadioButton *otherRadioButton : radioButtons)
        {
            if (otherRadioButton != radioButton && otherRadioButton->isChecked())
            {
                otherRadioButton->setChecked(false);
            }
        }
    }
}

void MainWindow::simulateProcessingOne()
{
    int currentValue = ui->progressBar_1->value();
    if (currentValue < 100)
    {
        ui->progressBar_1->setValue(currentValue + 20);
    }
}

void MainWindow::simulateProcessingTwo()
{
    int currentValue = ui->progressBar_2->value();
    if (currentValue < 100)
    {
        ui->progressBar_2->setValue(currentValue + 20);
    }
}

void MainWindow::simulateProcessingThree(int barValue)
{
    int currentValue = ui->progressBar_3->value();
    if (currentValue < 100)
    {
        ui->progressBar_3->setValue(currentValue + barValue);
    }
}

void MainWindow::generateGraph()
{
    bool ok;
    QString filename = QInputDialog::getText(nullptr, "Input", "Enter the filename for the Graphviz output:", QLineEdit::Normal, "", &ok);
    if (ok && !filename.isEmpty())
    {
        // User entered something and pressed OK
        Graphviz::GenerateDotandPNGFile((filename + ".dot").toStdString(), false, false);
        std::unordered_map<std::string, Linkutils> peakSet = Networkmanipulator::findPeaks(SimulatorController::getGraphDataPointer());
        Networkmanipulator::populateWithPeakValues(&SimulatorController::getGraphDataPointer().Augmentedlinks, peakSet);
        Graphviz::GenerateDotandPNGFile("NetworkDuringTheoreticPeak", true, true);
    }
}

void MainWindow::runAlgorithms()
{
    maxPUVandPaths = SimulatorController::getGraphDataPointer().MappedRouterVector.size();

    Prompts prompter = Prompts();
    ui->progressBar_3->setValue(0);
    ui->pushButton_4->setEnabled(false);
    QList<QCheckBox *> checkboxes = findChildren<QCheckBox *>();
    for (QCheckBox *checkbox : checkboxes)
    {
        checkbox->setEnabled(false);
    }

    int checkedCount_ = 0;
    int barValue = 100;
    for (QCheckBox *checkbox : checkboxes)
    {
        if (checkbox->isChecked())
        {
            checkedCount_++;
        }
    }
    checkedCount = checkedCount_;
    if (checkedCount == 0)
    {
        ui->pushButton_4->setEnabled(true);
        for (QCheckBox *checkbox : checkboxes)
        {
            checkbox->setEnabled(true);
        }
        return;
    }
    if (checkedCount != 0)
    {
        barValue = 100 / checkedCount;
    }

    if (ui->checkBox->isChecked())
    {
        // TODO: should prompt for router inputs! function only used to run dinics on specific routers
        //   to find maxflow between these routers, when no toher traffic is on the network.
        runAlgorithmOne(prompter);
        // simulateProcessingTwo(barValue);
    }

    if (ui->checkBox_2->isChecked())
    {
        runAlgorithmTwo(prompter);
        // simulateProcessingTwo(barValue);
    }

    if (ui->checkBox_3->isChecked())
    {
        runAlgorithmThree(prompter);
        // simulateProcessingTwo(barValue);
    }

    if (ui->checkBox_4->isChecked())
    {
        runAlgorithmFour(prompter);
        // simulateProcessingTwo(barValue);
    }

    if (ui->progressBar_3->value() != 100)
    {
        ui->progressBar_3->setValue(100);
    }

    ui->pushButton_4->setEnabled(true);
    for (QCheckBox *checkbox : checkboxes)
    {
        checkbox->setEnabled(true);
    }
}

void showResults(std::string title, std::string message)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(QString::fromStdString(title));
    msgBox.setText(QString::fromStdString(message));
    msgBox.setMinimumSize(600, 200); // Set the desired minimum width and height
    msgBox.setSizeGripEnabled(true);
    msgBox.setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    msgBox.setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    msgBox.exec();
}

void MainWindow::runAlgorithmOne(Prompts &prompter)
{
    std::cout << "ProcessingOne" << std::endl;
    // TODO: add preload prompt?
    std::cout << "ProcessingOne1" << std::endl;
    std::string source = prompter.promptRouter(this, "Source?");
    if (source == "")
        return;
    std::string sink = prompter.promptRouter(this, "Sink?");
    if (sink == "")
        return;
    int result = SimulatorController::runDinics(source, sink, false, false);
    string filename = ("Flow_" + source + "---" + sink);
    Graphviz::GenerateDotandPNGFile(filename, false, true);
    std::cout << "Result: " << result << std::endl;
    showResults("Dinic's MaxFlow no preload", "Result: " + std::to_string(result));
}

void MainWindow::runAlgorithmTwo(Prompts &prompter)
{
    bool amountOK = !skipQuery;
    int amountPUV = 5;
    bool PUVOK = !skipQuery;
    int amountPaths = 2;
    bool responseOK = !skipQuery;
    std::string response = "";
    if (!skipQuery)
    {
        amountPUV = QInputDialog::getInt(this, tr("Input Number"), tr("Please enter an amount of PUV's wanted"), 1, 1, maxPUVandPaths, 1, &amountOK);
        amountPaths = QInputDialog::getInt(this, tr("Input Number"), tr("Please enter an amount of Paths's wanted"), 1, 1, maxPUVandPaths, 1, &PUVOK);
    }
    auto dinicsResults = SimulatorController::DinicsOnBottlenecksNoAugmentedNetork(amountPUV, amountPaths, false);
    std::string compiledOut = "";
    for (const auto &dinicsResult : dinicsResults)
    {
        compiledOut += dinicsResult.first + ": " + std::to_string(dinicsResult.second) + "\n";
    }

    showResults("Dinic's Auto Preload OFF", compiledOut);
}

void MainWindow::runAlgorithmThree(Prompts &prompter)
{
    std::cout << "ProcessingThree" << std::endl;
    bool amountOK = !skipQuery;
    bool PUVOK = !skipQuery;
    int amountPUV = 5;
    int amountPaths = 5;
    if (!skipQuery)
    {
        amountPUV = QInputDialog::getInt(this, tr("Input Number"), tr("Please enter an amount of PUV's wanted"), 1, 1, maxPUVandPaths, 1, &PUVOK);
        amountPaths = QInputDialog::getInt(this, tr("Input Number"), tr("Please enter an amount of Paths's wanted"), 1, 1, maxPUVandPaths, 1, &amountOK);
    }
    auto dinicsResults = SimulatorController::DinicsOnBottlenecksNoAugmentedNetork(amountPUV, amountPaths, true);
    std::string compiledOut = "";
    for (const auto &dinicsResult : dinicsResults)
    {
        compiledOut += dinicsResult.first + ": " + std::to_string(dinicsResult.second) + "\n";
    }
    showResults("Dinic's Auto Preload ON", compiledOut);
}

void MainWindow::runAlgorithmFour(Prompts &prompter)
{
    std::string source = "R1";
    std::string sink = "R4";
    if (!skipQuery)
    {
        source = prompter.promptRouter(this, "Source?");
        sink = prompter.promptRouter(this, "Sink?");
    }
    std::cout << "Processing" << std::endl;
    string filename = ("Mincut_" + source + "---" + sink);
    Graphviz::GenerateDotandPNGFile(filename, false, true);
    auto minCutResult = SimulatorController::minCut(source, sink, true);
    std::stringstream ss;
    for (const auto &cut : minCutResult)
    {
        ss << cut.first << " - " << cut.second << "\n";
    }
    std::string CompiledOut = ss.str();
    std::cout << "MinCut:\n" << CompiledOut << std::endl;
    showResults("MinCut from " + source + " to " + sink, CompiledOut);
}

//

// void MainWindow::runAlgorithmNoAugmentedNetwork(){
//     SimulatorController::DinicsOnBottlenecksNoAugmentedNetork(amountPUV, amountPaths);
//     simulateProcessingThree(barValue);
// }
