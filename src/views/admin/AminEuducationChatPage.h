#ifndef AMINEUDUCATIONCHATPAGE_H
#define AMINEUDUCATIONCHATPAGE_H

#include <QWidget>

namespace Ui {
class AminEuducationChatPage;
}

class AminEuducationChatPage : public QWidget
{
    Q_OBJECT

public:
    explicit AminEuducationChatPage(QWidget *parent = nullptr);
    ~AminEuducationChatPage();

private:
    Ui::AminEuducationChatPage *ui;
};

#endif // AMINEUDUCATIONCHATPAGE_H
