#include <PropertyViewer.hpp>
#include <QVBoxLayout>
#include <QHeaderView>

PropertyViewer::PropertyViewer() : QWidget()
{
    prop_table = new QTableWidget();
    prop_table->verticalHeader()->setVisible(false);
    prop_table->horizontalHeader()->setVisible(false);
    prop_table->horizontalHeader()->setStretchLastSection(true);
    prop_table->setColumnCount(2);

    prop_label = new QLabel();
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(prop_label);
    layout->addWidget(prop_table);

    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    prop_label->setText("Properties");
}

void PropertyViewer::view(RNR::Instance* instance)
{
    prop_label->setText(QString::asprintf("%s Properties (%s)", instance->getName().c_str(), instance->getClassName().c_str()));

    std::vector<RNR::ReflectionProperty> properties = instance->getProperties();

    prop_table->setRowCount(properties.size());

    int property_count = 0;
    for(auto& property : properties)
    {
        QTableWidgetItem* new_property_item = new QTableWidgetItem(tr("%1").arg(property.name().c_str()));
        QTableWidgetItem* new_property_itemval = new QTableWidgetItem(tr("%1").arg(property.toString().c_str()));

        new_property_item->setStatusTip(property.description().c_str());

        prop_table->setItem(property_count, 0, new_property_item);
        prop_table->setItem(property_count, 1, new_property_itemval);
        property_count++;
    }
}