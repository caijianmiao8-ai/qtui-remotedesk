#include "about.h"
#include "ui_about.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>
#include <QSysInfo>
#include <QDesktopServices>
#include <QUrl>
#include <QDate>

About::About(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    buildLayout();
}

About::~About()
{
    delete ui;
}

void About::buildLayout()
{
    // 清除现有布局
    if (ui->widget->layout()) {
        QLayout *oldLayout = ui->widget->layout();
        QLayoutItem *item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete oldLayout;
    }

    // 创建主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(ui->widget);
    mainLayout->setContentsMargins(32, 32, 32, 32);  // p-8 = 32px
    mainLayout->setSpacing(0);

    // 1. 标题区
    mainLayout->addWidget(createHeader());
    mainLayout->addSpacing(32);  // mb-8 = 32px

    // 2. 应用信息卡片
    mainLayout->addWidget(createAppInfoCard());
    mainLayout->addSpacing(24);  // mb-6 = 24px

    // 3. 系统信息卡片
    mainLayout->addWidget(createSystemInfoCard());
    mainLayout->addSpacing(24);  // mb-6 = 24px

    // 4. 链接卡片
    mainLayout->addWidget(createLinksCard());

    // 添加弹性空间
    mainLayout->addStretch(1);
}

QWidget* About::createHeader()
{
    QWidget *header = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(header);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(8);  // mb-2 = 8px

    // 主标题: "About"
    QLabel *title = new QLabel("About");
    title->setStyleSheet(
        "QLabel {"
        "    color: #1e293b;"           // text-slate-900
        "    font-size: 36px;"           // text-4xl
        "    font-weight: 600;"          // font-semibold
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background: transparent;"
        "    border: none;"
        "    padding: 0;"
        "    margin: 0;"
        "}");

    // 副标题: "Application information"
    QLabel *subtitle = new QLabel("Application information");
    subtitle->setStyleSheet(
        "QLabel {"
        "    color: #64748b;"             // text-slate-500
        "    font-size: 16px;"            // text-base
        "    font-weight: 400;"           // normal
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background: transparent;"
        "    border: none;"
        "    padding: 0;"
        "    margin: 0;"
        "}");

    layout->addWidget(title);
    layout->addWidget(subtitle);

    return header;
}

QWidget* About::createAppInfoCard()
{
    QWidget *card = new QWidget();
    card->setStyleSheet(
        "QWidget {"
        "    background: rgba(255, 255, 255, 0.7);"
        "    border: 1px solid rgba(0, 0, 0, 0.05);"
        "    border-radius: 20px;"
        "}");

    // 添加阴影效果
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(60);
    shadow->setColor(QColor(0, 0, 0, 15));
    shadow->setOffset(0, 30);
    card->setGraphicsEffect(shadow);

    QVBoxLayout *layout = new QVBoxLayout(card);
    layout->setContentsMargins(32, 32, 32, 32);  // p-8 = 32px
    layout->setSpacing(24);  // space-y-6 = 24px

    // Logo 和应用名称区域
    QWidget *logoSection = new QWidget();
    logoSection->setStyleSheet("background: transparent;");
    QHBoxLayout *logoLayout = new QHBoxLayout(logoSection);
    logoLayout->setContentsMargins(0, 0, 0, 0);
    logoLayout->setSpacing(16);  // gap-4 = 16px

    // Logo 容器
    QWidget *logoContainer = new QWidget();
    logoContainer->setFixedSize(64, 64);  // w-16 h-16 = 64x64px
    logoContainer->setStyleSheet(
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
        "stop:0 #0A84FF, stop:1 #0051C7);"
        "border-radius: 16px;");

    // Logo 文字 (使用 "RD" 作为占位符)
    QLabel *logoText = new QLabel("RD", logoContainer);
    logoText->setAlignment(Qt::AlignCenter);
    logoText->setGeometry(0, 0, 64, 64);
    logoText->setStyleSheet(
        "QLabel {"
        "    color: #ffffff;"
        "    font-size: 28px;"
        "    font-weight: 700;"
        "    background: transparent;"
        "}");

    // 应用名称和版本
    QWidget *nameContainer = new QWidget();
    nameContainer->setStyleSheet("background: transparent;");
    QVBoxLayout *nameLayout = new QVBoxLayout(nameContainer);
    nameLayout->setContentsMargins(0, 0, 0, 0);
    nameLayout->setSpacing(4);  // space-y-1 = 4px

    QLabel *appName = new QLabel("RemoteDesk");
    appName->setStyleSheet(
        "QLabel {"
        "    color: #1e293b;"
        "    font-size: 24px;"            // text-2xl
        "    font-weight: 600;"           // font-semibold
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background: transparent;"
        "}");

    QLabel *appVersion = new QLabel("Version " + getAppVersion());
    appVersion->setStyleSheet(
        "QLabel {"
        "    color: #64748b;"
        "    font-size: 14px;"            // text-sm
        "    font-weight: 400;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background: transparent;"
        "}");

    nameLayout->addWidget(appName);
    nameLayout->addWidget(appVersion);

    logoLayout->addWidget(logoContainer);
    logoLayout->addWidget(nameContainer, 1);

    // 描述文本
    QLabel *description = new QLabel(
        "A modern remote desktop solution with low latency and high performance. "
        "Control your devices from anywhere with secure and reliable connections."
    );
    description->setWordWrap(true);
    description->setStyleSheet(
        "QLabel {"
        "    color: #64748b;"
        "    font-size: 14px;"
        "    line-height: 1.6;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background: transparent;"
        "}");

    // 构建日期
    QLabel *buildDate = new QLabel("Built on " + getBuildDate());
    buildDate->setStyleSheet(
        "QLabel {"
        "    color: #94a3b8;"             // text-slate-400
        "    font-size: 13px;"            // text-[13px]
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background: transparent;"
        "}");

    layout->addWidget(logoSection);
    layout->addWidget(description);
    layout->addWidget(buildDate);

    return card;
}

QWidget* About::createSystemInfoCard()
{
    QWidget *card = new QWidget();
    card->setStyleSheet(
        "QWidget {"
        "    background: rgba(255, 255, 255, 0.7);"
        "    border: 1px solid rgba(0, 0, 0, 0.05);"
        "    border-radius: 20px;"
        "}");

    // 添加阴影效果
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(60);
    shadow->setColor(QColor(0, 0, 0, 15));
    shadow->setOffset(0, 30);
    card->setGraphicsEffect(shadow);

    QVBoxLayout *layout = new QVBoxLayout(card);
    layout->setContentsMargins(32, 32, 32, 32);  // p-8 = 32px
    layout->setSpacing(24);  // space-y-6 = 24px

    // 标题
    QLabel *title = new QLabel("System Information");
    title->setStyleSheet(
        "QLabel {"
        "    color: #1e293b;"
        "    font-size: 20px;"            // text-xl
        "    font-weight: 600;"           // font-semibold
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background: transparent;"
        "}");

    // 信息网格
    QWidget *infoGrid = new QWidget();
    infoGrid->setStyleSheet("background: transparent;");
    QVBoxLayout *gridLayout = new QVBoxLayout(infoGrid);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->setSpacing(16);  // space-y-4 = 16px

    // 添加信息行
    gridLayout->addWidget(createInfoRow("Operating System", getOSVersion()));
    gridLayout->addWidget(createInfoRow("Qt Version", getQtVersion()));
    gridLayout->addWidget(createInfoRow("Architecture", getArchitecture()));
    gridLayout->addWidget(createInfoRow("Build Type",
#ifdef QT_DEBUG
        "Debug"
#else
        "Release"
#endif
    ));

    layout->addWidget(title);
    layout->addWidget(infoGrid);

    return card;
}

QWidget* About::createLinksCard()
{
    QWidget *card = new QWidget();
    card->setStyleSheet(
        "QWidget {"
        "    background: rgba(255, 255, 255, 0.7);"
        "    border: 1px solid rgba(0, 0, 0, 0.05);"
        "    border-radius: 20px;"
        "}");

    // 添加阴影效果
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(60);
    shadow->setColor(QColor(0, 0, 0, 15));
    shadow->setOffset(0, 30);
    card->setGraphicsEffect(shadow);

    QVBoxLayout *layout = new QVBoxLayout(card);
    layout->setContentsMargins(24, 24, 24, 24);  // p-6 = 24px
    layout->setSpacing(16);  // space-y-4 = 16px

    // 标题
    QLabel *title = new QLabel("Resources");
    title->setStyleSheet(
        "QLabel {"
        "    color: #1e293b;"
        "    font-size: 18px;"            // text-lg
        "    font-weight: 600;"           // font-semibold
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background: transparent;"
        "}");

    // 链接网格 (2列)
    QWidget *linksGrid = new QWidget();
    linksGrid->setStyleSheet("background: transparent;");
    QGridLayout *gridLayout = new QGridLayout(linksGrid);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->setHorizontalSpacing(16);  // gap-4 = 16px
    gridLayout->setVerticalSpacing(12);    // gap-3 = 12px

    gridLayout->addWidget(createLinkButton("🌐 Website", "https://remotedesk.io"), 0, 0);
    gridLayout->addWidget(createLinkButton("📖 Documentation", "https://docs.remotedesk.io"), 0, 1);
    gridLayout->addWidget(createLinkButton("💻 GitHub", "https://github.com/remotedesk"), 1, 0);
    gridLayout->addWidget(createLinkButton("📄 License", "https://remotedesk.io/license"), 1, 1);

    layout->addWidget(title);
    layout->addWidget(linksGrid);

    return card;
}

QWidget* About::createInfoRow(const QString &label, const QString &value, bool mono)
{
    QWidget *row = new QWidget();
    row->setStyleSheet("background: transparent;");

    QHBoxLayout *layout = new QHBoxLayout(row);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(16);  // gap-4 = 16px

    // 标签
    QLabel *labelWidget = new QLabel(label);
    labelWidget->setStyleSheet(
        "QLabel {"
        "    color: #64748b;"              // text-slate-500
        "    font-size: 14px;"             // text-sm
        "    font-weight: 400;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background: transparent;"
        "}");
    labelWidget->setMinimumWidth(140);

    // 值
    QLabel *valueWidget = new QLabel(value);
    QString fontFamily = mono ? "'Consolas', 'Monaco', monospace" : "'Segoe UI', Arial, sans-serif";
    valueWidget->setStyleSheet(QString(
        "QLabel {"
        "    color: #1e293b;"              // text-slate-900
        "    font-size: 14px;"             // text-sm
        "    font-weight: 500;"            // font-medium
        "    font-family: %1;"
        "    background: transparent;"
        "}").arg(fontFamily));

    layout->addWidget(labelWidget);
    layout->addWidget(valueWidget, 1);

    return row;
}

QWidget* About::createLinkButton(const QString &text, const QString &url)
{
    QPushButton *button = new QPushButton(text);
    button->setCursor(Qt::PointingHandCursor);
    button->setStyleSheet(
        "QPushButton {"
        "    background: rgba(255, 255, 255, 0.6);"
        "    border: 1px solid rgba(0, 0, 0, 0.05);"
        "    border-radius: 14px;"
        "    padding: 12px 16px;"          // py-3 px-4
        "    color: #1e293b;"
        "    font-size: 14px;"
        "    font-weight: 500;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    text-align: left;"
        "}"
        "QPushButton:hover {"
        "    background: rgba(0, 0, 0, 0.03);"
        "}"
        "QPushButton:pressed {"
        "    background: rgba(0, 0, 0, 0.05);"
        "}");

    // 连接点击事件打开链接
    connect(button, &QPushButton::clicked, [url]() {
        QDesktopServices::openUrl(QUrl(url));
    });

    return button;
}

// 辅助函数实现
QString About::getAppVersion()
{
    return "1.0.0";  // 可以从宏定义或版本文件读取
}

QString About::getBuildDate()
{
    return QString(__DATE__) + " " + QString(__TIME__);
}

QString About::getOSVersion()
{
    return QSysInfo::prettyProductName();
}

QString About::getQtVersion()
{
    return QString(QT_VERSION_STR);
}

QString About::getArchitecture()
{
    return QSysInfo::currentCpuArchitecture();
}
