#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include <QColor>

namespace Ui {
class Home;
}

class Home : public QWidget
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr);
    ~Home();

private:
    Ui::Home *ui;

    void initUi();
    void setupScrollArea();

    QWidget *createHeaderSection();
    QFrame *createPairingHintCard();
    QWidget *createStatsRow();
    QFrame *createMachineInfoCard();
    QFrame *createQuickActionsCard();

    QFrame *createGlassCard(const QString &objectName) const;
    QGraphicsDropShadowEffect *createShadow(QObject *parent, qreal blur = 48.0, qreal yOffset = 18.0) const;
    QLabel *createTitleLabel(const QString &text, int size, bool bold = true) const;
    QLabel *createSecondaryLabel(const QString &text, int size = 14, qreal opacity = 0.65) const;
    QWidget *createStatusBadge(const QString &text, const QColor &color) const;
};

#endif // HOME_H
