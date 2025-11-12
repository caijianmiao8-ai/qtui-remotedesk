#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onHomeButtonClicked();
    void onDeviceButtonClicked();
    void onSettingButtonClicked();
    void onAboutButtonClicked();

    void onLanguageButtonClicked();
    void onDarkModeButtonClicked();
    void onSignOutButtonClicked();

    void onMinimizeClicked();
    void onMaximizeClicked();
    void onCloseClicked();

private:
    Ui::MainWindow *ui;

    // 存储当前选中的按钮
    QToolButton* m_currentActiveButton = nullptr;

    // 主题管理
    bool m_darkMode = false;
    QString m_currentLang = "zh";

    // 窗口控制按钮
    QPushButton* m_minimizeBtn = nullptr;
    QPushButton* m_maximizeBtn = nullptr;
    QPushButton* m_closeBtn = nullptr;
    QWidget* m_controlsWidget = nullptr;  // 控制按钮容器

    // 初始化函数
    void setupUI();
    void setupWindowControls();
    void setupNavigation();
    void setupBottomButtons();
    void applyTheme();

    // 导航管理
    void setupButtonWithIcon(QToolButton* button, const QString& text, const QString& iconPath);
    void switchToPage(int pageIndex);
    void setButtonActive(QToolButton* button);
    void setButtonNormal(QToolButton* button);

    // 样式生成
    QString getLightThemeStyles();
    QString getDarkThemeStyles();
    QString getSidebarButtonStyle(bool isActive = false);
    QString getBottomButtonStyle(bool isSignOut = false);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
};
#endif // MAINWINDOW_H
