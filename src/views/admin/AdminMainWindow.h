#ifndef ADMINMAINWINDOW_H
#define ADMINMAINWINDOW_H

#include <QMainWindow>
#include "AdminComplaintPage.h"
#include "AdminInquiryPage.h"
#include "AdminDefaultPage.h"

namespace Ui {
class AdminMainWindow;
}

class AdminMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminMainWindow(QWidget *parent = nullptr);
    ~AdminMainWindow();

private slots:
    void on_pushButton_complaint_clicked();

    void on_pushButton_inquiry_clicked();

private:
    Ui::AdminMainWindow *ui;
    AdminDefaultPage *defaultPage;
    AdminComplaintPage *complaintPage;
    AdminInquiryPage *inquiryPage;

    void setEmptyPageLayout();
};

#endif // ADMINMAINWINDOW_H
