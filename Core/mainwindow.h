#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>

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

private:
    Ui::MainWindow *ui;

    // 存储当前选中的按钮
    QToolButton* m_currentActiveButton=nullptr;
    //导航管理部分
    void setupNavigation();
    void setupButtonWithIcon(QToolButton* button, const QString& text, const QString& iconPath);
    void switchToPage(int pageIndex);
    void setButtonActive(QToolButton* button);
    void setButtonNormal(QToolButton* button);
    //顶部信息部分
    void setupSoftwareInfo();
    void setupSoftwareInfoLayout();
    //底部管理部分
    void setupBottomButtons();
    void setupBottomButtonWithIcon(QToolButton *button, const QString &text, const QString &iconPath);


};
#endif // MAINWINDOW_H
