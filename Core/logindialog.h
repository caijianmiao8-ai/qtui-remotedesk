#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QString>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    // 获取登录结果
    QString getAccount() const { return m_account; }
    QString getLoginMode() const { return m_loginMode; }

signals:
    void loginSuccessful(const QString &account, const QString &mode);
    void gotoRegister();
    void gotoForgotPassword();

private slots:
    // 登录模式切换
    void onPasswordModeClicked();
    void onOtpModeClicked();

    // 登录操作
    void onPasswordLogin();
    void onOtpLogin();
    void onSendCode();

    // 界面操作
    void onTogglePasswordVisibility();
    void onToggleTheme();
    void onToggleLanguage();
    void onForgotPassword();
    void onCreateAccount();

    // 倒计时
    void onCountdownTick();

private:
    Ui::LoginDialog *ui;

    // 状态变量
    QString m_loginMode;        // "password" or "otp"
    QString m_account;
    bool m_darkMode;
    QString m_language;         // "zh" or "en"
    bool m_passwordVisible;
    int m_countdown;
    QTimer *m_countdownTimer;

    // 初始化方法
    void setupUI();
    void setupConnections();
    void updateUIForMode();
    void updateUIForLanguage();
    void updateUIForTheme();

    // 工具方法
    QString tr_custom(const QString &key);
    void showError(const QString &message);
    bool validateAccount();
    bool validatePassword();
    bool validateCode();
};

#endif // LOGINDIALOG_H
