# 登录功能说明 / Login Feature Documentation

## 概述 / Overview

本次更新为 Qt RemoteDesktop 应用添加了一个现代化的登录界面，设计风格参考了 Apple 的 UI 设计语言。

This update adds a modern login interface to the Qt RemoteDesktop application, inspired by Apple's UI design language.

## 功能特性 / Features

### 1. 双登录模式 / Dual Login Modes
- **密码登录** / Password Login: 使用账号和密码登录
- **验证码登录** / OTP Login: 使用账号和一次性验证码登录

### 2. 多语言支持 / Multi-language Support
- 中文 (Chinese)
- English
- 点击右上角语言按钮切换 / Click the language button in the top-right corner to switch

### 3. 深浅色主题 / Light/Dark Theme
- 浅色模式 (Light mode)
- 深色模式 (Dark mode)
- 点击右上角月亮/太阳图标切换 / Click the moon/sun icon in the top-right corner to toggle

### 4. 界面元素 / UI Elements
- 账号输入框 (支持手机号/邮箱) / Account input (phone/email)
- 密码输入框 (带显示/隐藏切换) / Password input (with show/hide toggle)
- 验证码输入框 (6位数字) / OTP input (6-digit)
- 发送验证码按钮 (带60秒倒计时) / Send code button (with 60s countdown)
- 忘记密码链接 / Forgot password link
- 创建新账号链接 / Create account link

### 5. 输入验证 / Input Validation
- 账号不能为空 / Account cannot be empty
- 密码至少6位 / Password must be at least 6 characters
- 验证码必须是6位数字 / OTP must be 6 digits

### 6. 开发模式 / Development Mode
在开发环境中，使用以下验证码可以直接登录：
- `000000`
- `123456`

In development, use these codes to login directly:
- `000000`
- `123456`

## 文件结构 / File Structure

```
Core/
├── logindialog.h       # 登录对话框头文件 / Login dialog header
├── logindialog.cpp     # 登录对话框实现 / Login dialog implementation
├── logindialog.ui      # 登录对话框UI设计 / Login dialog UI design
└── main.cpp            # 主程序入口(已更新) / Main entry point (updated)
```

## 使用方法 / Usage

### 编译 / Build

```bash
qmake RemoteDesk.pro
make
```

### 运行 / Run

启动应用后，会首先显示登录对话框。登录成功后才能进入主界面。

When the application starts, the login dialog will be shown first. After successful login, the main window will appear.

### 集成说明 / Integration Notes

在 `main.cpp` 中，登录逻辑如下：

```cpp
LoginDialog loginDialog;

// 监听登录成功信号
connect(&loginDialog, &LoginDialog::loginSuccessful,
        [&](const QString &account, const QString &mode) {
    // 处理登录成功
    qDebug() << "User logged in:" << account << "Mode:" << mode;
});

// 显示登录对话框
if (loginDialog.exec() == QDialog::Accepted) {
    // 登录成功，显示主窗口
    MainWindow w;
    w.show();
    return a.exec();
}
```

## TODO: 后端集成 / Backend Integration

目前登录功能是前端实现，需要集成实际的后端 API：

Currently, the login is frontend-only. Backend API integration needed:

### 1. 密码登录 API / Password Login API
```cpp
// 在 onPasswordLogin() 中添加
// POST /auth/login
// Body: { "account": "...", "password": "..." }
```

### 2. 发送验证码 API / Send OTP API
```cpp
// 在 onSendCode() 中添加
// POST /auth/otp/send
// Body: { "account": "..." }
```

### 3. 验证码登录 API / OTP Login API
```cpp
// 在 onOtpLogin() 中添加
// POST /auth/otp/verify
// Body: { "account": "...", "code": "..." }
```

## 样式定制 / Style Customization

登录界面使用 Qt StyleSheet 实现 Apple 风格设计，所有样式都在 `logindialog.cpp` 的 `updateUIForTheme()` 方法中定义。

可以根据需要调整以下内容：
- 颜色方案 / Color schemes
- 圆角大小 / Border radius
- 间距和边距 / Spacing and margins
- 字体大小 / Font sizes

## 信号 / Signals

LoginDialog 提供以下信号：

```cpp
signals:
    void loginSuccessful(const QString &account, const QString &mode);
    void gotoRegister();
    void gotoForgotPassword();
```

可以在主程序中连接这些信号来实现相应的功能。

## 截图 / Screenshots

### 浅色模式 - 密码登录 / Light Mode - Password Login
- 渐变背景
- 毛玻璃效果面板
- 圆角按钮和输入框

### 深色模式 - 验证码登录 / Dark Mode - OTP Login
- 深色渐变背景
- 半透明面板
- 高对比度文字

## 依赖 / Dependencies

- Qt 5.x 或更高版本 / Qt 5.x or higher
- Qt Widgets 模块 / Qt Widgets module
- Qt Core 模块 / Qt Core module
- Qt GUI 模块 / Qt GUI module

## 许可证 / License

遵循项目原有许可证 / Follows the original project license

## 贡献者 / Contributors

- 登录界面设计参考 Apple Human Interface Guidelines
- UI implementation based on Apple design principles
