#include <QApplication>
#include <QComboBox>
#include <QLineEdit>
#include <QStringList>
#include <QVBoxLayout>
#include <QWidget>
#include "SearchableComboBox.h"

SearchableComboBox::SearchableComboBox(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    comboBox = new QComboBox(this);
    comboBox->setEditable(true);

    // originalItems << "Apple" << "Orange" << "Banana" << "Grape" << "Peach" << "Strawberry";
    comboBox->addItems(originalItems);

    QLineEdit *lineEdit = comboBox->lineEdit();
    connect(lineEdit, &QLineEdit::textEdited, this, &SearchableComboBox::filterItems);

    layout->addWidget(comboBox);
    setLayout(layout);
}

void SearchableComboBox::filterItems(const QString &text)
{
    QString currentText = comboBox->currentText();

    comboBox->clear();
    for (const QString &item : originalItems)
    {
        if (item.contains(text, Qt::CaseInsensitive))
        {
            std::cout << "addedItem" << std::endl;
            comboBox->addItem(item);
        }
    }

    comboBox->setEditText(currentText);
}

QString SearchableComboBox::currentText() const
{
    return comboBox->currentText();
}