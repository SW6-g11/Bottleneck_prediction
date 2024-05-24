#ifndef PROMPTS_H
#define PROMPTS_H
#include "SearchableComboBoxDialog.h"

class Prompts
{
private:
    SearchableComboBoxDialog dialog;
    static vector<MappedRouter> routers;

public:
    Prompts();
    ~Prompts();

    // std::string promptRouter(QWidget *parent);
    std::string promptRouter(QWidget *parent, std::string title = "Routers");
};
#endif