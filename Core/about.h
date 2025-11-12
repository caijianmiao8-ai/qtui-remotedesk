#ifndef ABOUT_H
#define ABOUT_H

#include <QWidget>

namespace Ui {
class About;
}

class About : public QWidget
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = nullptr);
    ~About();

private:
    Ui::About *ui;
    void initUi();
};

#endif // ABOUT_H
