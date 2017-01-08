#include "onDemandSpacer.h"
#include <QHBoxLayout>
#include <QSpacerItem>

OnDemandSpacer::OnDemandSpacer(QWidget* parent) : QWidget(parent),
    hLayout(new QHBoxLayout),
    spacer(new QSpacerItem(150, 12, QSizePolicy::Fixed, QSizePolicy::Fixed))
{
    hLayout->addSpacerItem(spacer);
    this->setLayout(hLayout);
}
