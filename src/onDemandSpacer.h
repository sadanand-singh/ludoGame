#ifndef SPACERWIDGET_HEADER
#define SPACERWIDGET_HEADER

#include <QWidget>

class QHBoxLayout;
class QSpacerItem;

class OnDemandSpacer : public QWidget
{
    QHBoxLayout *hLayout;
    QSpacerItem *spacer;

    public:
    OnDemandSpacer(QWidget* parent = nullptr);
};

#endif
