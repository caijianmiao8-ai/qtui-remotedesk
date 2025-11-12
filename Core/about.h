#ifndef ABOUT_H
#define ABOUT_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QGraphicsDropShadowEffect>

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
    void setupScrollArea();
    QWidget *createHeroSection();
    QFrame *createChangelogCard();
    QFrame *createSystemInfoCard();
    QFrame *createGlassCard(const QString &objectName) const;
    QGraphicsDropShadowEffect *createShadow(QObject *parent, qreal blur = 44.0, qreal yOffset = 16.0) const;
};

#endif // ABOUT_H
