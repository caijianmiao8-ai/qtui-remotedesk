#include "about.h"
#include "ui_about.h"
#include "iconhelper.h"

#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

About::About(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::About)
{
    ui->setupUi(this);
    initUi();
}

About::~About()
{
    delete ui;
}

void About::initUi()
{
    setupScrollArea();

    QWidget *content = ui->scrollAreaWidgetContents;
    if (content->layout()) {
        delete content->layout();
    }

    auto *rootLayout = new QVBoxLayout(content);
    rootLayout->setContentsMargins(48, 48, 48, 72);
    rootLayout->setSpacing(32);

    rootLayout->addWidget(createHeroSection());
    rootLayout->addWidget(createChangelogCard());
    rootLayout->addWidget(createSystemInfoCard());
    rootLayout->addStretch();
}

void About::setupScrollArea()
{
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setStyleSheet(
        "QScrollArea {"
        "    border: none;"
        "    background: transparent;"
        "}" 
        "QScrollBar:vertical {"
        "    background: transparent;"
        "    width: 6px;"
        "}" 
        "QScrollBar::handle:vertical {"
        "    background: rgba(15,23,42,0.18);"
        "    border-radius: 3px;"
        "}" 
        "QScrollBar::handle:vertical:hover {"
        "    background: rgba(15,23,42,0.28);"
        "}" 
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "    height: 0px;"
        "}");
}

QWidget *About::createHeroSection()
{
    auto *hero = new QWidget;
    auto *layout = new QVBoxLayout(hero);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(18);
    layout->setAlignment(Qt::AlignHCenter);

    auto *iconBadge = new QLabel(hero);
    iconBadge->setFixedSize(110, 110);
    iconBadge->setAlignment(Qt::AlignCenter);
    iconBadge->setPixmap(IconHelper::draw(IconGlyph::Monitor, QSize(54, 54), Qt::white));
    iconBadge->setStyleSheet(
        "QLabel {"
        "    background: qlineargradient(x1:0,y1:0,x2:1,y2:1, stop:0 #0A84FF, stop:1 #0051C7);"
        "    border-radius: 28px;"
        "    border: 1px solid rgba(10,132,255,0.32);"
        "}");

    auto *title = new QLabel(tr("RemoteDesktop"), hero);
    title->setStyleSheet("QLabel { color: rgba(15,23,42,0.92); font-size: 34px; font-weight: 600; }");

    auto *version = new QLabel(tr("版本 2.0.1"), hero);
    version->setStyleSheet("QLabel { color: rgba(15,23,42,0.55); font-size: 16px; font-weight: 500; }");

    auto *ctaButton = new QPushButton(tr("检查更新"), hero);
    ctaButton->setCursor(Qt::PointingHandCursor);
    ctaButton->setStyleSheet(
        "QPushButton {"
        "    background: qlineargradient(x1:0,y1:0,x2:1,y2:1, stop:0 #0A84FF, stop:1 #0051C7);"
        "    color: white;"
        "    border-radius: 16px;"
        "    padding: 12px 28px;"
        "    font-size: 14px;"
        "    font-weight: 600;"
        "    min-width: 160px;"
        "}" 
        "QPushButton:hover {"
        "    background: qlineargradient(x1:0,y1:0,x2:1,y2:1, stop:0 #0B8CFF, stop:1 #0A5CD9);"
        "}" 
        "QPushButton:pressed {"
        "    background: qlineargradient(x1:0,y1:0,x2:1,y2:1, stop:0 #086FD6, stop:1 #074CB0);"
        "}");

    layout->addWidget(iconBadge, 0, Qt::AlignHCenter);
    layout->addWidget(title);
    layout->addWidget(version);
    layout->addWidget(ctaButton, 0, Qt::AlignHCenter);

    return hero;
}

QFrame *About::createChangelogCard()
{
    auto *card = createGlassCard("changelogCard");
    card->setGraphicsEffect(createShadow(card));

    auto *layout = new QVBoxLayout(card);
    layout->setContentsMargins(36, 30, 36, 30);
    layout->setSpacing(16);

    auto *title = new QLabel(tr("更新日志"), card);
    title->setStyleSheet("QLabel { color: rgba(15,23,42,0.9); font-size: 18px; font-weight: 600; }");

    auto *versionLabel = new QLabel(QStringLiteral("v2.0.1 · 2024-10-24"), card);
    versionLabel->setStyleSheet("QLabel { color: rgba(15,23,42,0.75); font-size: 14px; font-weight: 600; }");

    auto *list = new QWidget(card);
    auto *listLayout = new QVBoxLayout(list);
    listLayout->setContentsMargins(0, 0, 0, 0);
    listLayout->setSpacing(8);

    auto addItem = [&](const QString &text) {
        auto *row = new QWidget(list);
        auto *rowLayout = new QHBoxLayout(row);
        rowLayout->setContentsMargins(0, 0, 0, 0);
        rowLayout->setSpacing(12);

        auto *dot = new QLabel(row);
        dot->setFixedSize(6, 6);
        dot->setStyleSheet("QLabel { background: qradialgradient(cx:0.4, cy:0.4, radius:0.7, stop:0 rgba(15,23,42,0.45), stop:1 rgba(15,23,42,0.05)); border-radius: 3px; }");

        auto *label = new QLabel(text, row);
        label->setWordWrap(true);
        label->setStyleSheet("QLabel { color: rgba(15,23,42,0.68); font-size: 13px; font-weight: 500; }");

        rowLayout->addWidget(dot, 0, Qt::AlignTop);
        rowLayout->addWidget(label, 1);

        listLayout->addWidget(row);
    };

    addItem(tr("优化网络连接稳定性 / Improved connection stability"));
    addItem(tr("修复部分已知问题 / Bug fixes"));
    addItem(tr("提升画质传输效率 / Better streaming quality"));

    layout->addWidget(title);
    layout->addWidget(versionLabel);
    layout->addWidget(list);

    return card;
}

QFrame *About::createSystemInfoCard()
{
    auto *card = createGlassCard("systemInfoCard");
    card->setGraphicsEffect(createShadow(card));

    auto *layout = new QVBoxLayout(card);
    layout->setContentsMargins(36, 30, 36, 30);
    layout->setSpacing(20);

    auto *title = new QLabel(tr("系统信息"), card);
    title->setStyleSheet("QLabel { color: rgba(15,23,42,0.9); font-size: 18px; font-weight: 600; }");

    auto *gridWidget = new QWidget(card);
    auto *grid = new QGridLayout(gridWidget);
    grid->setContentsMargins(0, 0, 0, 0);
    grid->setHorizontalSpacing(40);
    grid->setVerticalSpacing(18);

    auto addInfo = [&](int row, int column, const QString &caption, const QString &value) {
        auto *container = new QWidget(gridWidget);
        auto *containerLayout = new QVBoxLayout(container);
        containerLayout->setContentsMargins(0, 0, 0, 0);
        containerLayout->setSpacing(6);

        auto *captionLabel = new QLabel(caption, container);
        captionLabel->setStyleSheet("QLabel { color: rgba(15,23,42,0.58); font-size: 13px; font-weight: 500; }");
        auto *valueLabel = new QLabel(value, container);
        valueLabel->setStyleSheet("QLabel { color: rgba(15,23,42,0.9); font-size: 16px; font-weight: 600; }");

        containerLayout->addWidget(captionLabel);
        containerLayout->addWidget(valueLabel);

        grid->addWidget(container, row, column);
    };

    addInfo(0, 0, tr("操作系统"), tr("Windows 11 Pro"));
    addInfo(0, 1, tr("构建版本"), QStringLiteral("22000.1219"));

    layout->addWidget(title);
    layout->addWidget(gridWidget);

    return card;
}

QFrame *About::createGlassCard(const QString &objectName) const
{
    auto *card = new QFrame;
    card->setObjectName(objectName);
    card->setAttribute(Qt::WA_StyledBackground, true);
    card->setStyleSheet(QString(
        "QFrame#%1 {"
        "    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,"
        "        stop:0 rgba(255,255,255,0.9),"
        "        stop:0.55 rgba(255,255,255,0.66),"
        "        stop:1 rgba(240,244,255,0.5));"
        "    border: 1px solid rgba(255,255,255,0.7);"
        "    border-top-color: rgba(255,255,255,0.86);"
        "    border-left-color: rgba(255,255,255,0.8);"
        "    border-right-color: rgba(15,23,42,0.08);"
        "    border-bottom-color: rgba(15,23,42,0.12);"
        "    border-radius: 24px;"
        "}").arg(objectName));
    return card;
}

QGraphicsDropShadowEffect *About::createShadow(QObject *parent, qreal blur, qreal yOffset) const
{
    auto *effect = new QGraphicsDropShadowEffect(parent);
    effect->setBlurRadius(blur);
    effect->setOffset(0, yOffset);
    effect->setColor(QColor(15, 23, 42, 30));
    return effect;
}
