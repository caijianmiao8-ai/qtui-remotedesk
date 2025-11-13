#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QDebug>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),
    m_loginMode("password"),
    m_darkMode(false),
    m_language("zh"),
    m_passwordVisible(false),
    m_countdown(0)
{
    ui->setupUi(this);

    // 创建定时器
    m_countdownTimer = new QTimer(this);
    m_countdownTimer->setInterval(1000);

    setupUI();
    setupConnections();
    updateUIForMode();
    updateUIForLanguage();
    updateUIForTheme();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::setupUI()
{
    // 设置窗口属性
    setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
    setModal(true);

    // 初始化按钮组（模拟 radio button 行为）
    ui->btnPasswordMode->setCheckable(true);
    ui->btnOtpMode->setCheckable(true);
    ui->btnPasswordMode->setChecked(true);

    // 设置初始页面
    ui->stackedWidget->setCurrentIndex(0);

    // 错误标签初始隐藏
    ui->lblError->hide();
}

void LoginDialog::setupConnections()
{
    // 模式切换
    connect(ui->btnPasswordMode, &QPushButton::clicked, this, &LoginDialog::onPasswordModeClicked);
    connect(ui->btnOtpMode, &QPushButton::clicked, this, &LoginDialog::onOtpModeClicked);

    // 登录按钮
    connect(ui->btnLogin, &QPushButton::clicked, this, [this]() {
        if (m_loginMode == "password") {
            onPasswordLogin();
        } else {
            onOtpLogin();
        }
    });

    // 发送验证码
    connect(ui->btnSendCode, &QPushButton::clicked, this, &LoginDialog::onSendCode);

    // 密码可见性切换
    connect(ui->btnTogglePassword, &QPushButton::clicked, this, &LoginDialog::onTogglePasswordVisibility);

    // 主题和语言
    connect(ui->btnTheme, &QPushButton::clicked, this, &LoginDialog::onToggleTheme);
    connect(ui->btnLanguage, &QPushButton::clicked, this, &LoginDialog::onToggleLanguage);

    // 忘记密码和注册
    connect(ui->btnForgot, &QPushButton::clicked, this, &LoginDialog::onForgotPassword);
    connect(ui->btnRegister, &QPushButton::clicked, this, &LoginDialog::onCreateAccount);

    // 回车键登录
    connect(ui->edtPassword, &QLineEdit::returnPressed, this, &LoginDialog::onPasswordLogin);
    connect(ui->edtCode, &QLineEdit::returnPressed, this, &LoginDialog::onOtpLogin);

    // 倒计时定时器
    connect(m_countdownTimer, &QTimer::timeout, this, &LoginDialog::onCountdownTick);
}

void LoginDialog::onPasswordModeClicked()
{
    if (m_loginMode == "password") return;

    m_loginMode = "password";
    ui->btnPasswordMode->setChecked(true);
    ui->btnOtpMode->setChecked(false);
    updateUIForMode();
    ui->lblError->hide();
}

void LoginDialog::onOtpModeClicked()
{
    if (m_loginMode == "otp") return;

    m_loginMode = "otp";
    ui->btnPasswordMode->setChecked(false);
    ui->btnOtpMode->setChecked(true);
    updateUIForMode();
    ui->lblError->hide();
}

void LoginDialog::onPasswordLogin()
{
    ui->lblError->hide();

    if (!validateAccount()) {
        showError(m_language == "zh" ? "请输入账号" : "Please enter account");
        return;
    }

    if (!validatePassword()) {
        showError(m_language == "zh" ? "请输入不少于 6 位的密码" : "Password must be at least 6 characters");
        return;
    }

    m_account = ui->edtAccount->text().trimmed();
    QString password = ui->edtPassword->text();

    // TODO: 实际的登录 API 调用
    qDebug() << "Password login:" << m_account << password;

    // 模拟登录成功
    emit loginSuccessful(m_account, m_loginMode);
    accept();
}

void LoginDialog::onOtpLogin()
{
    ui->lblError->hide();

    if (!validateAccount()) {
        showError(m_language == "zh" ? "请输入账号" : "Please enter account");
        return;
    }

    if (!validateCode()) {
        showError(m_language == "zh" ? "请输入 6 位验证码" : "Enter 6-digit code");
        return;
    }

    m_account = ui->edtAccount->text().trimmed();
    QString code = ui->edtCode->text().trimmed();

    // 开发环境兜底：000000 / 123456 直接通过
    if (code == "000000" || code == "123456") {
        qDebug() << "Dev OTP login success:" << m_account << code;
        emit loginSuccessful(m_account, m_loginMode);
        accept();
        return;
    }

    // TODO: 实际的验证码验证 API 调用
    qDebug() << "Verify OTP:" << m_account << code;

    // 模拟验证成功
    emit loginSuccessful(m_account, m_loginMode);
    accept();
}

void LoginDialog::onSendCode()
{
    ui->lblError->hide();

    if (!validateAccount()) {
        showError(m_language == "zh" ? "请输入账号" : "Please enter account");
        return;
    }

    m_account = ui->edtAccount->text().trimmed();

    // TODO: 实际的发送验证码 API 调用
    qDebug() << "Send OTP to:" << m_account;

    // 启动倒计时
    m_countdown = 60;
    m_countdownTimer->start();
    onCountdownTick(); // 立即更新一次
}

void LoginDialog::onTogglePasswordVisibility()
{
    m_passwordVisible = !m_passwordVisible;

    if (m_passwordVisible) {
        ui->edtPassword->setEchoMode(QLineEdit::Normal);
        ui->btnTogglePassword->setText("🙈");
    } else {
        ui->edtPassword->setEchoMode(QLineEdit::Password);
        ui->btnTogglePassword->setText("👁");
    }
}

void LoginDialog::onToggleTheme()
{
    m_darkMode = !m_darkMode;
    updateUIForTheme();
}

void LoginDialog::onToggleLanguage()
{
    m_language = (m_language == "zh") ? "en" : "zh";
    updateUIForLanguage();
}

void LoginDialog::onForgotPassword()
{
    emit gotoForgotPassword();
    // 可以在这里打开忘记密码对话框
    QMessageBox::information(this,
        m_language == "zh" ? "忘记密码" : "Forgot Password",
        m_language == "zh" ? "找回密码功能开发中..." : "Password recovery coming soon...");
}

void LoginDialog::onCreateAccount()
{
    emit gotoRegister();
    // 可以在这里打开注册对话框
    QMessageBox::information(this,
        m_language == "zh" ? "创建账号" : "Create Account",
        m_language == "zh" ? "注册功能开发中..." : "Registration coming soon...");
}

void LoginDialog::onCountdownTick()
{
    if (m_countdown <= 0) {
        m_countdownTimer->stop();
        ui->btnSendCode->setEnabled(true);
        ui->btnSendCode->setText(m_language == "zh" ? "发送验证码" : "Send code");
        return;
    }

    ui->btnSendCode->setEnabled(false);
    QString text = m_language == "zh"
        ? QString("重新发送 %1秒").arg(m_countdown)
        : QString("Resend %1s").arg(m_countdown);
    ui->btnSendCode->setText(text);

    m_countdown--;
}

void LoginDialog::updateUIForMode()
{
    if (m_loginMode == "password") {
        ui->stackedWidget->setCurrentIndex(0);
    } else {
        ui->stackedWidget->setCurrentIndex(1);
    }
}

void LoginDialog::updateUIForLanguage()
{
    // 更新语言按钮文本
    ui->btnLanguage->setText(m_language == "zh" ? "中 / EN" : "EN / 中");

    // 更新所有文本
    if (m_language == "zh") {
        ui->lblTagline->setText("随时随地，掌控全局");
        ui->btnPasswordMode->setText("密码登录");
        ui->btnOtpMode->setText("验证码登录");
        ui->lblAccount->setText("账号");
        ui->edtAccount->setPlaceholderText("手机号 / 邮箱");
        ui->lblPassword->setText("密码");
        ui->edtPassword->setPlaceholderText("请输入密码");
        ui->lblCode->setText("验证码");
        ui->edtCode->setPlaceholderText("6位数字验证码");
        ui->btnSendCode->setText(m_countdown > 0 ? QString("重新发送 %1秒").arg(m_countdown) : "发送验证码");
        ui->lblSecurityNotice->setText("如果该账号存在，我们已发送验证码。为保护隐私，不提示账号是否存在。");
        ui->btnLogin->setText("登录");
        ui->btnForgot->setText("忘记密码？");
        ui->btnRegister->setText("创建新账号");
        ui->lblHint->setText("同一账号登录到手机和电脑后，设备会自动互相发现，无需手动添加。");
    } else {
        ui->lblTagline->setText("Control everything, anywhere");
        ui->btnPasswordMode->setText("Password");
        ui->btnOtpMode->setText("Code");
        ui->lblAccount->setText("Account");
        ui->edtAccount->setPlaceholderText("Phone / Email");
        ui->lblPassword->setText("Password");
        ui->edtPassword->setPlaceholderText("Enter password");
        ui->lblCode->setText("Verification code");
        ui->edtCode->setPlaceholderText("6-digit code");
        ui->btnSendCode->setText(m_countdown > 0 ? QString("Resend %1s").arg(m_countdown) : "Send code");
        ui->lblSecurityNotice->setText("If the account exists, a verification code has been sent. We don't reveal existence for privacy.");
        ui->btnLogin->setText("Sign in");
        ui->btnForgot->setText("Forgot password?");
        ui->btnRegister->setText("Create new account");
        ui->lblHint->setText("Sign in with the same account on both phone and desktop. Devices pair automatically — no manual add.");
    }
}

void LoginDialog::updateUIForTheme()
{
    // 更新主题按钮
    ui->btnTheme->setText(m_darkMode ? "☀️" : "🌙");

    QString styleSheet;

    if (m_darkMode) {
        // 深色主题 - Apple 风格
        styleSheet = R"(
            QDialog {
                background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                    stop:0 rgba(30, 30, 35, 255),
                    stop:1 rgba(15, 15, 18, 255));
            }

            QWidget#mainContainer {
                background: rgba(255, 255, 255, 0.04);
                border: 1px solid rgba(255, 255, 255, 0.1);
                border-radius: 24px;
            }

            QLabel {
                color: #E5E5EA;
                background: transparent;
            }

            QLabel#lblAppName {
                font-size: 28px;
                font-weight: bold;
                color: white;
            }

            QLabel#lblTagline {
                font-size: 14px;
                color: #98989D;
            }

            QLabel#lblLogo {
                font-size: 48px;
                background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                    stop:0 #0A84FF, stop:1 #0051C7);
                border-radius: 20px;
            }

            QLabel#lblError {
                color: #FF453A;
                font-size: 13px;
            }

            QLabel#lblSecurityNotice, QLabel#lblHint {
                color: #8E8E93;
                font-size: 11px;
            }

            QPushButton {
                background: rgba(255, 255, 255, 0.08);
                border: 1px solid rgba(255, 255, 255, 0.15);
                border-radius: 14px;
                color: white;
                font-size: 14px;
                font-weight: 500;
                padding: 8px 16px;
            }

            QPushButton:hover {
                background: rgba(255, 255, 255, 0.12);
            }

            QPushButton:pressed {
                background: rgba(255, 255, 255, 0.06);
            }

            QPushButton#btnPasswordMode:checked, QPushButton#btnOtpMode:checked {
                background: rgba(255, 255, 255, 0.18);
                border: 1px solid rgba(255, 255, 255, 0.25);
            }

            QPushButton#btnLogin {
                background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                    stop:0 #0A84FF, stop:1 #0051C7);
                border: none;
                color: white;
                font-weight: 600;
            }

            QPushButton#btnLogin:hover {
                background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                    stop:0 #0A95FF, stop:1 #0061D7);
            }

            QPushButton#btnForgot, QPushButton#btnRegister {
                background: transparent;
                border: none;
                color: #0A84FF;
                text-align: left;
                font-size: 13px;
            }

            QPushButton#btnForgot:hover, QPushButton#btnRegister:hover {
                color: #409CFF;
            }

            QPushButton:disabled {
                background: rgba(255, 255, 255, 0.04);
                color: #636366;
            }

            QLineEdit {
                background: rgba(255, 255, 255, 0.07);
                border: 1px solid rgba(255, 255, 255, 0.2);
                border-radius: 14px;
                color: white;
                font-size: 14px;
                padding: 12px 16px;
                selection-background-color: #0A84FF;
            }

            QLineEdit:focus {
                border: 2px solid rgba(10, 132, 255, 0.6);
                background: rgba(255, 255, 255, 0.1);
            }

            QLineEdit::placeholder {
                color: #636366;
            }
        )";
    } else {
        // 浅色主题 - Apple 风格
        styleSheet = R"(
            QDialog {
                background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                    stop:0 rgba(250, 250, 252, 255),
                    stop:1 rgba(226, 232, 240, 255));
            }

            QWidget#mainContainer {
                background: rgba(255, 255, 255, 0.7);
                border: 1px solid rgba(0, 0, 0, 0.05);
                border-radius: 24px;
            }

            QLabel {
                color: #1C1C1E;
                background: transparent;
            }

            QLabel#lblAppName {
                font-size: 28px;
                font-weight: bold;
                color: #000000;
            }

            QLabel#lblTagline {
                font-size: 14px;
                color: #636366;
            }

            QLabel#lblLogo {
                font-size: 48px;
                background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                    stop:0 #0A84FF, stop:1 #0051C7);
                border-radius: 20px;
            }

            QLabel#lblError {
                color: #FF3B30;
                font-size: 13px;
            }

            QLabel#lblSecurityNotice, QLabel#lblHint {
                color: #8E8E93;
                font-size: 11px;
            }

            QPushButton {
                background: rgba(255, 255, 255, 0.8);
                border: 1px solid rgba(0, 0, 0, 0.08);
                border-radius: 14px;
                color: #1C1C1E;
                font-size: 14px;
                font-weight: 500;
                padding: 8px 16px;
            }

            QPushButton:hover {
                background: rgba(255, 255, 255, 0.95);
            }

            QPushButton:pressed {
                background: rgba(240, 240, 245, 0.9);
            }

            QPushButton#btnPasswordMode:checked, QPushButton#btnOtpMode:checked {
                background: white;
                border: 1px solid rgba(0, 0, 0, 0.12);
            }

            QPushButton#btnLogin {
                background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                    stop:0 #0A84FF, stop:1 #0051C7);
                border: none;
                color: white;
                font-weight: 600;
            }

            QPushButton#btnLogin:hover {
                background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                    stop:0 #0A95FF, stop:1 #0061D7);
            }

            QPushButton#btnForgot, QPushButton#btnRegister {
                background: transparent;
                border: none;
                color: #0A84FF;
                text-align: left;
                font-size: 13px;
            }

            QPushButton#btnForgot:hover, QPushButton#btnRegister:hover {
                color: #409CFF;
            }

            QPushButton:disabled {
                background: rgba(0, 0, 0, 0.03);
                color: #C7C7CC;
            }

            QLineEdit {
                background: rgba(255, 255, 255, 0.8);
                border: 1px solid rgba(0, 0, 0, 0.1);
                border-radius: 14px;
                color: #1C1C1E;
                font-size: 14px;
                padding: 12px 16px;
                selection-background-color: #0A84FF;
            }

            QLineEdit:focus {
                border: 2px solid rgba(10, 132, 255, 0.5);
                background: white;
            }

            QLineEdit::placeholder {
                color: #C7C7CC;
            }
        )";
    }

    setStyleSheet(styleSheet);
}

QString LoginDialog::tr_custom(const QString &key)
{
    // 简单的翻译函数
    // 在实际应用中，可以使用 Qt 的翻译系统
    return key;
}

void LoginDialog::showError(const QString &message)
{
    ui->lblError->setText(message);
    ui->lblError->show();
}

bool LoginDialog::validateAccount()
{
    QString account = ui->edtAccount->text().trimmed();
    return !account.isEmpty();
}

bool LoginDialog::validatePassword()
{
    QString password = ui->edtPassword->text();
    return password.length() >= 6;
}

bool LoginDialog::validateCode()
{
    QString code = ui->edtCode->text().trimmed();

    // 移除所有非数字字符
    QString pureCode = code;
    pureCode.remove(QRegularExpression("[^0-9]"));

    return pureCode.length() == 6;
}
