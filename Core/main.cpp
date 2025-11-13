#include "mainwindow.h"
#include "home.h"
#include "logindialog.h"

#include <QApplication>
#include <QMessageBox>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 先显示登录对话框
    LoginDialog loginDialog;

    // 处理登录成功信号
    QString userAccount;
    QObject::connect(&loginDialog, &LoginDialog::loginSuccessful,
                     [&](const QString &account, const QString &mode) {
        userAccount = account;
        qDebug() << "User logged in:" << account << "Mode:" << mode;
    });

    // 显示登录对话框
    if (loginDialog.exec() == QDialog::Accepted) {
        // 登录成功，显示主窗口
        MainWindow w;
        w.setWindowTitle(QString("RemoteDesktop - %1").arg(userAccount));
        w.show();
        return a.exec();
    }

    // 用户取消登录，退出应用
    return 0;
}
