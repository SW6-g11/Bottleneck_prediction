#include "prompts.h"
#include <string.h>
#include <QMessageBox>
#include "SimulatorController.h"

vector<MappedRouter> Prompts::routers;

std::string Prompts::promptRouter(QWidget *parent, std::string title)
{
    dialog.setTitle(title);
    while (true)
    {
        if (dialog.exec() != QDialog::Accepted)
        {
            return "";
        }
        QString selectedText = dialog.getTextValue();
        std::string selectedTextString = selectedText.toStdString();

        std::cout << "Selected: " << selectedTextString << " length: " << routers.size() << std::endl;

        auto it = std::find_if(routers.begin(), routers.end(), [&selectedTextString](const MappedRouter &router)
                               {
                                   std::cout << "Selected: \"" << selectedTextString << "\" test: \"" << router.id << "\"" << std::endl;
                                   return router.id == selectedTextString; // Capture targetId by reference
                               });

        if (it == routers.end())
        {
            QMessageBox::warning(parent, QString("Invalid Router"), QString("Please pick one from the list"));
            continue;
        }
        return selectedText.toStdString();
    }
}

void Prompts::RefreshData()
{
    dialog.addItems(SimulatorController::getGraphDataPointer().MappedRouterVector);
    routers = SimulatorController::getGraphDataPointer().MappedRouterVector;
}
Prompts::Prompts()
{
    // dialog = SearchableComboBoxDialog(parent);
    //  std::cout << "Adding items" << std::endl;
    dialog.addItems(SimulatorController::getGraphDataPointer().MappedRouterVector);
    // std::cout << "Added items" << std::endl;
    routers = SimulatorController::getGraphDataPointer().MappedRouterVector;
}

Prompts::~Prompts()
{
}