#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
}

About::~About()
{
    delete ui;
}

void About::initUi()
{
    // 超浅色透明滚动条设置
    ui->scrollArea->setStyleSheet(
        "QScrollArea {"
        "    border: none;"
        "    background-color: transparent;"
        "}"
        "QScrollBar:vertical {"
        "    background: transparent;"  // 垂直滚动条背景透明
        "    width: 8px;"
        "    margin: 0px;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: rgba(0, 0, 0, 0.15);"  // 更浅的颜色，透明度降低
        "    border-radius: 4px;"
        "    min-height: 20px;"
        "}"
        "QScrollBar::handle:vertical:hover {"
        "    background: rgba(0, 0, 0, 0.25);"  // 悬停时稍微加深
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "    border: none;"
        "    background: none;"
        "    height: 0px;"
        "}"
        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
        "    background: transparent;"  // 滑块前后区域也透明
        "}"
        "QScrollBar:horizontal {"
        "    background: transparent;"  // 水平滚动条背景透明
        "    height: 8px;"
        "    margin: 0px;"
        "}"
        "QScrollBar::handle:horizontal {"
        "    background: rgba(0, 0, 0, 0.15);"  // 更浅的颜色，透明度降低
        "    border-radius: 4px;"
        "    min-width: 20px;"
        "}"
        "QScrollBar::handle:horizontal:hover {"
        "    background: rgba(0, 0, 0, 0.25);"  // 悬停时稍微加深
        "}"
        "QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {"
        "    border: none;"
        "    background: none;"
        "    width: 0px;"
        "}"
        "QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {"
        "    background: transparent;"  // 滑块前后区域也透明
        "}");


}
