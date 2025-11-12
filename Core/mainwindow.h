#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include <QColor>

#include "iconhelper.h"

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
    void onToggleFullscreen();

private:
    Ui::MainWindow *ui;

    QToolButton *m_currentActiveButton = nullptr;
    bool m_isDarkMode = false;
    bool m_useEnglish = false;
    bool m_isFullscreen = false;

    void initializeFrame();
    void setupTopBar();
    void setupBranding();
    void setupNavigation();
    void setupSidebarButton(QToolButton *button, const QString &text, IconGlyph glyph);
    void setButtonActive(QToolButton *button);
    void setButtonNormal(QToolButton *button);
    void setupBottomButtons();
    void updateLanguageButton();
    void updateDarkModeButton();
    void switchToPage(int pageIndex);
    void applyShadow(QWidget *target, qreal blurRadius, qreal yOffset, const QColor &color);
};

#endif // MAINWINDOW_H
