#ifndef ADMININQUIRYPAGE_H
#define ADMININQUIRYPAGE_H

#include <QWidget>

namespace Ui {
class AdminInquiryPage;
}

class AdminInquiryPage : public QWidget
{
    Q_OBJECT

public:
    explicit AdminInquiryPage(QWidget *parent = nullptr);
    ~AdminInquiryPage();

private:
    Ui::AdminInquiryPage *ui;
};

#endif // ADMININQUIRYPAGE_H
