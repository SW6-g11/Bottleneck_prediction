#include "SearchableComboBoxDialog.h"
#include <QVBoxLayout>
#include <QDialogButtonBox>

SearchableComboBoxDialog::SearchableComboBoxDialog(QWidget *parent) : QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    Title = new QLabel(QString::fromStdString(""), this);
    layout->addWidget(Title);

    comboBox = new SearchableComboBox(this);
    layout->addWidget(comboBox);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

void SearchableComboBoxDialog::setTitle(std::string title)
{
    Title->setText(QString::fromStdString(title));
}

QString SearchableComboBoxDialog::getTextValue() const
{
    return comboBox->currentText();
}