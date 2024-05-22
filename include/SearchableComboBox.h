#ifndef SEARCHABLECOMBOBOX_H
#define SEARCHABLECOMBOBOX_H

#include <QWidget>
#include <QComboBox>
#include <QStringList>
#include <QLabel>
#include "MappedRouter.h"

class SearchableComboBox : public QWidget
{
    Q_OBJECT

public:
    explicit SearchableComboBox(QWidget *parent = nullptr);
    QString currentText() const;

    template <typename T>
    void addItems(std::vector<T> list)
    {
        for (const T &item : list)
        {
            originalItems.append(QString::fromStdString(item.toString()));
        }
        comboBox->addItems(originalItems);
    }

private slots:
    void filterItems(const QString &text);

private:
    QComboBox *comboBox;
    QStringList originalItems;
};

#endif // SEARCHABLECOMBOBOX_H