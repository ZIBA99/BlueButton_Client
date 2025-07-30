#ifndef DOUBLECLICKBUTTON_H
#define DOUBLECLICKBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class DoubleClickButton : public QPushButton
{
    Q_OBJECT

public:
    explicit DoubleClickButton(QWidget *parent = nullptr);

signals:
    void doubleClicked();
protected:
    void mouseDoubleClickEvent(QMouseEvent* event) override
    {
        if (event->button() == Qt::LeftButton) {
            emit doubleClicked();
        }
        QPushButton::mouseDoubleClickEvent(event);
    }

};

#endif // DOUBLECLICKBUTTON_H
