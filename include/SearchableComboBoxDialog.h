#ifndef SEARCHABLECOMBOBOXDIALOG_H
#define SEARCHABLECOMBOBOXDIALOG_H

#include <QDialog>
#include "SearchableComboBox.h"
#include <string.h>

class SearchableComboBoxDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchableComboBoxDialog(QWidget *parent = nullptr);

    void setTitle(std::string title);
    QString getTextValue() const;
    template <typename T>
    void addItems(std::vector<T> list)
    {
        comboBox->addItems(list);
    }

private:
    QLabel *Title;
    SearchableComboBox *comboBox;
};

#endif // SEARCHABLECOMBOBOXDIALOG_H
