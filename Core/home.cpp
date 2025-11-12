#include "home.h"
#include "ui_home.h"
#include "iconhelper.h"

#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QSpacerItem>

Home::Home(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Home)
{
    ui->setupUi(this);
    initUi();
}

Home::~Home()
{
    delete ui;
}

void Home::initUi()
{
    setupScrollArea();

    QWidget *content = ui->scrollAreaWidgetContents;
    if (content->layout()) {
        delete content->layout();
    }

    auto *rootLayout = new QVBoxLayout(content);
    rootLayout->setContentsMargins(48, 48, 48, 64);
    rootLayout->setSpacing(32);

    rootLayout->addWidget(createHeaderSection());
    rootLayout->addWidget(createPairingHintCard());
    rootLayout->addWidget(createStatsRow());
    rootLayout->addWidget(createMachineInfoCard());
    rootLayout->addWidget(createQuickActionsCard());
    rootLayout->addStretch();
}

void Home::setupScrollArea()
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
        "    margin: 0px;"
        "}" 
        "QScrollBar::handle:vertical {"
        "    background: rgba(15,23,42,0.16);"
        "    border-radius: 3px;"
        "}" 
        "QScrollBar::handle:vertical:hover {"
        "    background: rgba(15,23,42,0.28);"
        "}" 
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "    height: 0px;"
        "}" 
        "QScrollBar:horizontal {"
        "    background: transparent;"
        "    height: 6px;"
        "    margin: 0px;"
        "}" 
        "QScrollBar::handle:horizontal {"
        "    background: rgba(15,23,42,0.16);"
        "    border-radius: 3px;"
        "}" 
        "QScrollBar::handle:horizontal:hover {"
        "    background: rgba(15,23,42,0.28);"
        "}" 
        "QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {"
        "    width: 0px;"
        "}");
}

QWidget *Home::createHeaderSection()
{
    auto *section = new QWidget;
    auto *layout = new QVBoxLayout(section);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(8);

    auto *title = createTitleLabel(tr("欢迎回来"), 34);
    auto *subtitle = createSecondaryLabel(tr("此电脑已准备好被远程接管（被控端）"), 15, 0.55);

    layout->addWidget(title);
    layout->addWidget(subtitle);

    return section;
}

QFrame *Home::createPairingHintCard()
{
    auto *card = createGlassCard("pairingHintCard");
    card->setGraphicsEffect(createShadow(card, 40.0, 14.0));

    auto *layout = new QHBoxLayout(card);
    layout->setContentsMargins(24, 20, 24, 20);
    layout->setSpacing(18);

    auto *iconWrapper = new QLabel(card);
    iconWrapper->setFixedSize(44, 44);
    iconWrapper->setAlignment(Qt::AlignCenter);
    iconWrapper->setPixmap(IconHelper::draw(IconGlyph::Info, QSize(20, 20), QColor(10, 132, 255)));
    iconWrapper->setStyleSheet(
        "QLabel {"
        "    background: qlineargradient(x1:0,y1:0,x2:1,y2:1, stop:0 rgba(10,132,255,0.22), stop:1 rgba(0,81,199,0.12));"
        "    border-radius: 16px;"
        "    border: 1px solid rgba(10,132,255,0.3);"
        "}");

    auto *text = createSecondaryLabel(tr("提示：请在手机端使用同一账号登录，即可从手机远程接管本电脑。"), 12, 0.65);
    text->setWordWrap(true);

    layout->addWidget(iconWrapper, 0, Qt::AlignTop);
    layout->addWidget(text, 1);

    return card;
}

QWidget *Home::createStatsRow()
{
    auto *row = new QWidget;
    auto *layout = new QHBoxLayout(row);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(24);

    auto *statCard = createGlassCard("statCardOnline");
    statCard->setMinimumHeight(152);
    statCard->setGraphicsEffect(createShadow(statCard, 36.0, 12.0));

    auto *cardLayout = new QVBoxLayout(statCard);
    cardLayout->setContentsMargins(24, 24, 24, 24);
    cardLayout->setSpacing(12);

    auto *iconBadge = new QLabel(statCard);
    iconBadge->setFixedSize(52, 52);
    iconBadge->setAlignment(Qt::AlignCenter);
    iconBadge->setPixmap(IconHelper::draw(IconGlyph::Monitor, QSize(26, 26), QColor(249, 115, 22)));
    iconBadge->setStyleSheet(
        "QLabel {"
        "    background: qlineargradient(x1:0,y1:0,x2:1,y2:1, stop:0 rgba(249,115,22,0.2), stop:1 rgba(249,115,22,0.1));"
        "    border-radius: 18px;"
        "    border: 1px solid rgba(249,115,22,0.28);"
        "}");

    auto *label = createSecondaryLabel(tr("在线设备"), 13, 0.58);
    auto *value = createTitleLabel(QString::number(3), 30, true);
    value->setStyleSheet("QLabel { color: #f97316; font-weight: 600; font-size: 30px; }");

    cardLayout->addWidget(iconBadge, 0, Qt::AlignLeft);
    cardLayout->addWidget(label);
    cardLayout->addWidget(value);
    cardLayout->addStretch();

    layout->addWidget(statCard, 0);
    layout->addStretch(1);

    return row;
}

QFrame *Home::createMachineInfoCard()
{
    auto *card = createGlassCard("machineInfoCard");
    card->setGraphicsEffect(createShadow(card));

    auto *layout = new QVBoxLayout(card);
    layout->setContentsMargins(40, 40, 40, 40);
    layout->setSpacing(28);

    auto *title = createTitleLabel(tr("本机信息"), 22);
    layout->addWidget(title);

    auto *gridContainer = new QWidget(card);
    auto *grid = new QGridLayout(gridContainer);
    grid->setContentsMargins(0, 0, 0, 0);
    grid->setHorizontalSpacing(48);
    grid->setVerticalSpacing(32);

    auto makePair = [&](int row, int column, const QString &caption, const QString &valueText) {
        auto *pair = new QWidget(gridContainer);
        auto *pairLayout = new QVBoxLayout(pair);
        pairLayout->setContentsMargins(0, 0, 0, 0);
        pairLayout->setSpacing(6);

        auto *captionLabel = createSecondaryLabel(caption, 13, 0.6);
        auto *valueLabel = createTitleLabel(valueText, 18, false);
        valueLabel->setStyleSheet("QLabel { color: rgba(15,23,42,0.92); font-size: 18px; font-weight: 500; }");

        pairLayout->addWidget(captionLabel);
        pairLayout->addWidget(valueLabel);

        grid->addWidget(pair, row, column);
    };

    makePair(0, 0, tr("设备名称"), tr("我的工作电脑"));
    makePair(0, 1, tr("设备ID"), QStringLiteral("RD-2024-10241502"));
    makePair(1, 0, tr("本机IP"), QStringLiteral("192.168.1.100"));

    auto *networkWidget = new QWidget(gridContainer);
    auto *networkLayout = new QVBoxLayout(networkWidget);
    networkLayout->setContentsMargins(0, 0, 0, 0);
    networkLayout->setSpacing(6);
    networkLayout->addWidget(createSecondaryLabel(tr("网络状态"), 13, 0.6));
    networkLayout->addWidget(createStatusBadge(tr("局域网 · 在线"), QColor(34, 197, 94)));
    grid->addWidget(networkWidget, 1, 1);

    layout->addWidget(gridContainer);

    return card;
}

QFrame *Home::createQuickActionsCard()
{
    auto *card = createGlassCard("quickActionsCard");
    card->setGraphicsEffect(createShadow(card, 40.0, 14.0));

    auto *layout = new QVBoxLayout(card);
    layout->setContentsMargins(36, 32, 36, 32);
    layout->setSpacing(24);

    layout->addWidget(createTitleLabel(tr("快速操作"), 18));

    auto *grid = new QHBoxLayout();
    grid->setSpacing(20);
    grid->setContentsMargins(0, 0, 0, 0);

    auto createTile = [&](const QString &title, const QString &description, IconGlyph iconGlyph) {
        auto *tile = new QFrame(card);
        tile->setObjectName("quickTile");
        tile->setStyleSheet(
            "QFrame#quickTile {"
            "    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,"
            "        stop:0 rgba(255,255,255,0.88),"
            "        stop:1 rgba(244,248,255,0.54));"
            "    border: 1px solid rgba(255,255,255,0.72);"
            "    border-bottom-color: rgba(15,23,42,0.12);"
            "    border-right-color: rgba(15,23,42,0.1);"
            "    border-radius: 20px;"
            "}"
            "QFrame#quickTile:hover {"
            "    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,"
            "        stop:0 rgba(255,255,255,0.94),"
            "        stop:1 rgba(236,242,255,0.66));"
            "    border-color: rgba(10,132,255,0.28);"
            "}");
        tile->setMinimumHeight(160);
        tile->setCursor(Qt::PointingHandCursor);

        auto *tileLayout = new QVBoxLayout(tile);
        tileLayout->setContentsMargins(24, 24, 24, 24);
        tileLayout->setSpacing(16);

        auto *iconLabel = new QLabel(tile);
        iconLabel->setFixedSize(44, 44);
        iconLabel->setAlignment(Qt::AlignCenter);
        iconLabel->setStyleSheet(
            "QLabel {"
            "    background: qlineargradient(x1:0,y1:0,x2:1,y2:1, stop:0 rgba(10,132,255,0.22), stop:1 rgba(0,81,199,0.12));"
            "    border-radius: 16px;"
            "    border: 1px solid rgba(10,132,255,0.28);"
            "}");
        iconLabel->setPixmap(IconHelper::draw(iconGlyph, QSize(22, 22), QColor(10, 132, 255)));

        auto *titleLabel = createTitleLabel(title, 16);
        titleLabel->setStyleSheet("QLabel { color: rgba(15,23,42,0.92); font-size: 16px; font-weight: 600; }");

        auto *descLabel = createSecondaryLabel(description, 13, 0.6);
        descLabel->setWordWrap(true);

        tileLayout->addWidget(iconLabel, 0, Qt::AlignLeft);
        tileLayout->addWidget(titleLabel);
        tileLayout->addWidget(descLabel);

        auto *chevronRow = new QHBoxLayout();
        chevronRow->setContentsMargins(0, 0, 0, 0);
        chevronRow->addStretch();
        auto *chevron = new QLabel(tile);
        chevron->setFixedSize(20, 20);
        chevron->setAlignment(Qt::AlignCenter);
        chevron->setPixmap(IconHelper::draw(IconGlyph::ChevronRight, QSize(16, 16), QColor(10, 132, 255, 220)));
        chevron->setAttribute(Qt::WA_TransparentForMouseEvents);
        chevronRow->addWidget(chevron);
        tileLayout->addLayout(chevronRow);
        tileLayout->addStretch();

        return tile;
    };

    grid->addWidget(createTile(tr("设备管理"), tr("查看已注册设备"), IconGlyph::Grid));
    grid->addWidget(createTile(tr("系统设置"), tr("配置参数"), IconGlyph::Settings));
    grid->addStretch(1);

    layout->addLayout(grid);

    return card;
}

QFrame *Home::createGlassCard(const QString &objectName) const
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
        "    border-radius: 22px;"
        "    border: 1px solid rgba(255,255,255,0.7);"
        "    border-top-color: rgba(255,255,255,0.86);"
        "    border-left-color: rgba(255,255,255,0.8);"
        "    border-right-color: rgba(15,23,42,0.08);"
        "    border-bottom-color: rgba(15,23,42,0.12);"
        "}").arg(objectName));
    return card;
}

QGraphicsDropShadowEffect *Home::createShadow(QObject *parent, qreal blur, qreal yOffset) const
{
    auto *effect = new QGraphicsDropShadowEffect(parent);
    effect->setBlurRadius(blur);
    effect->setOffset(0, yOffset);
    effect->setColor(QColor(15, 23, 42, 30));
    return effect;
}

QLabel *Home::createTitleLabel(const QString &text, int size, bool bold) const
{
    auto *label = new QLabel(text);
    label->setStyleSheet(QString(
        "QLabel {"
        "    color: rgba(15,23,42,0.92);"
        "    font-size: %1px;"
        "    font-weight: %2;"
        "}" ).arg(size).arg(bold ? 600 : 500));
    return label;
}

QLabel *Home::createSecondaryLabel(const QString &text, int size, qreal opacity) const
{
    auto *label = new QLabel(text);
    label->setStyleSheet(QString(
        "QLabel {"
        "    color: rgba(15,23,42,%1);"
        "    font-size: %2px;"
        "    font-weight: 500;"
        "}" ).arg(opacity).arg(size));
    label->setWordWrap(false);
    return label;
}

QWidget *Home::createStatusBadge(const QString &text, const QColor &color) const
{
    auto *badge = new QWidget;
    badge->setObjectName("statusBadge");
    badge->setStyleSheet(QString(
        "QWidget#statusBadge {"
        "    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,"
        "        stop:0 rgba(%1,%2,%3,0.26),"
        "        stop:1 rgba(%1,%2,%3,0.14));"
        "    border: 1px solid rgba(%1,%2,%3,0.32);"
        "    border-radius: 999px;"
        "}" )
        .arg(color.red())
        .arg(color.green())
        .arg(color.blue()));

    auto *layout = new QHBoxLayout(badge);
    layout->setContentsMargins(12, 6, 16, 6);
    layout->setSpacing(8);

    auto *dot = new QLabel(badge);
    dot->setFixedSize(8, 8);
    dot->setStyleSheet(QString(
        "QLabel {"
        "    background: qradialgradient(cx:0.4, cy:0.4, radius:0.7,"
        "        stop:0 rgba(%1,%2,%3,1), stop:1 rgba(%1,%2,%3,0.1));"
        "    border-radius: 4px;"
        "}"
        ).arg(color.red())
         .arg(color.green())
         .arg(color.blue()));

    auto *label = new QLabel(text, badge);
    label->setStyleSheet(QString(
        "QLabel {"
        "    color: rgb(%1,%2,%3);"
        "    font-size: 13px;"
        "    font-weight: 600;"
        "}" )
        .arg(color.red())
        .arg(color.green())
        .arg(color.blue()));

    layout->addWidget(dot);
    layout->addWidget(label);

    return badge;
}
