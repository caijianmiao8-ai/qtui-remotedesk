# RemoteDesk UI 设计规范（基于React代码）

## 主窗口布局

### 外层容器 (hostWrapperClass)
- **padding**: `p-6 md:p-10` = 移动端24px, 桌面端40px
- **背景**: 径向渐变
  - 浅色: `radial-gradient(circle at 20% 20%, rgba(255,255,255,0.9) 0%, rgba(226,232,240,0.6) 40%, rgba(226,232,240,0.3) 70%)`
  - 深色: `radial-gradient(circle at 20% 20%, rgba(80,80,90,0.4) 0%, rgba(10,10,12,0.9) 60%)`

### 主Shell (appShellClass)
- **尺寸**: `max-w-[1280px]`, `h-[96vh]`, `max-h-[1200px]`
- **圆角**: `rounded-[24px]`
- **背景**: `rgba(255, 255, 255, 0.6)` (浅色) / `rgba(255, 255, 255, 0.04)` (深色)
- **边框**: `1px solid rgba(0, 0, 0, 0.05)` (浅色) / `rgba(255, 255, 255, 0.1)` (深色)
- **阴影**: `shadow-[0_30px_80px_rgba(0,0,0,0.8)]` (深色) / `shadow-[0_30px_60px_rgba(0,0,0,0.06)]` (浅色)

### 侧边栏 (Sidebar)
- **宽度**: `w-64` = 256px
- **背景**: 与主Shell相同
- **边框**: 左侧圆角

#### 品牌区
- **padding**: `p-6` = 24px
- **Logo容器**: `w-12 h-12` = 48x48px
- **Logo圆角**: `rounded-[16px]`
- **Logo背景**: `linear-gradient(to bottom right, #0A84FF, #0051C7)`
- **标题字体**: `text-base` = 16px, `font-semibold`
- **版本字体**: `text-[11px]`

#### 菜单按钮
- **padding**: `px-4 py-3` = 水平16px, 垂直12px
- **圆角**: `rounded-[14px]`
- **字体**: `text-[14px]`, `font-medium`
- **间距**: `space-y-2` = 8px垂直间距
- **普通状态**: 透明背景
- **激活状态**: `rgba(0, 0, 0, 0.04)` (浅色) / `rgba(255, 255, 255, 0.08)` (深色)
- **悬停状态**: `rgba(0, 0, 0, 0.03)` (浅色) / `rgba(255, 255, 255, 0.07)` (深色)

#### 底部控制按钮
- **padding**: `p-4` = 16px容器, `px-4 py-3` = 按钮
- **样式**: 与菜单按钮相同
- **退出按钮颜色**: `text-red-400`, hover时 `bg-red-500/10`

### 右上角控制按钮
- **位置**: `top-5 right-6` = 距离顶部20px, 右侧24px
- **尺寸**: `w-8 h-8` = 32x32px
- **圆角**: `rounded-[10px]`
- **间距**: `gap-2` = 8px
- **字体**: `text-[13px]`
- **关闭按钮**: 红色 `text-red-400`

---

## Home 页面布局

### 容器
- **最大宽度**: `max-w-6xl` = 1152px
- **padding**: `p-8` = 32px
- **顶部边距**: `mt-5` = 20px

### 1. 标题区
- **主标题**:
  - 文本: "欢迎回来"
  - 字体: `text-4xl` = 36px, `font-semibold` = 600
  - 颜色: `#1e293b` (浅色) / `#f1f5f9` (深色)
  - 下边距: `mb-2` = 8px

- **副标题**:
  - 文本: "此电脑已准备好被远程接管（被控端）"
  - 字体: `text-base` = 16px
  - 颜色: `#64748b` (浅色) / `#94a3b8` (深色)
  - 下边距: `mb-4` = 16px

### 2. 提示卡片 (PairingHintCard)
- **容器**:
  - 背景: `rgba(255, 255, 255, 0.7)` (浅色) / `rgba(255, 255, 255, 0.05)` (深色)
  - 边框: `1px solid rgba(0, 0, 0, 0.05)` (浅色) / `rgba(255, 255, 255, 0.1)` (深色)
  - 圆角: `rounded-[20px]`
  - 阴影: `shadow-[0_30px_60px_rgba(0,0,0,0.06)]` (浅色)
  - padding: `p-4` = 16px
  - 下边距: `mb-8` = 32px

- **图标容器**:
  - 尺寸: `w-8 h-8` = 32x32px
  - 圆角: `rounded-[14px]`
  - 背景: `rgba(10, 132, 255, 0.12)`
  - 图标: Info, 尺寸 16px, 颜色 `#0A84FF`

- **文本**:
  - 字体: `text-[12px]`, `leading-relaxed`
  - 颜色: `#64748b` (浅色)
  - 内容: "提示：请在手机端使用同一账号登录，即可从手机远程接管本电脑。"

### 3. 统计卡片网格
- **网格**: `grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 xl:grid-cols-4`
- **间距**: `gap-6` = 24px
- **下边距**: `mb-8` = 32px

#### 单个统计卡片 (在线设备)
- **容器**: GlassCard, `p-6` = 24px
- **图标容器**:
  - 尺寸: `w-12 h-12` = 48x48px
  - 圆角: `rounded-[14px]`
  - 背景: `bg-orange-500/10` = `rgba(249, 115, 22, 0.1)`
  - 图标: Monitor, 尺寸 24px, 颜色 `text-orange-400` = `#fb923c`
  - 下边距: `mb-3` = 12px

- **标签**:
  - 文本: "在线设备"
  - 字体: `text-sm` = 14px
  - 颜色: `#64748b`
  - 下边距: `mb-1` = 4px

- **数值**:
  - 字体: `text-3xl` = 30px, `font-semibold` = 600
  - 颜色: `text-orange-400` = `#fb923c`

### 4. 本机信息卡片
- **容器**: GlassCard, `p-8` = 32px, `mb-6` = 24px

- **标题**:
  - 文本: "本机信息"
  - 字体: `text-2xl` = 24px, `font-semibold` = 600
  - 颜色: `#1e293b`
  - 下边距: `mb-6` = 24px

- **信息网格**:
  - 布局: `grid grid-cols-2`
  - 间距: `gap-6` = 24px
  - 字体: `text-sm` = 14px

#### 信息项
- **标签**:
  - 颜色: `#64748b`
  - 下边距: `mb-2` = 8px

- **数值**:
  - 字体: `text-lg` = 18px, `font-medium` = 500
  - 颜色: `#1e293b`
  - 特殊: Device ID 使用 `font-mono`

#### 网络状态特殊处理
- **指示点**:
  - 尺寸: `w-2.5 h-2.5` = 10x10px
  - 圆角: `rounded-full`
  - 颜色: `bg-green-400` = `#4ade80`
  - 动画: `animate-pulse`

- **状态文本**:
  - 字体: `text-lg` = 18px, `font-medium` = 500
  - 颜色: `text-green-400` = `#4ade80`

### 5. 快速操作卡片
- **容器**: GlassCard, `p-6` = 24px

- **标题**:
  - 文本: "快速操作"
  - 字体: `text-lg` = 18px, `font-semibold` = 600
  - 颜色: `#1e293b`
  - 下边距: `mb-4` = 16px

- **按钮网格**:
  - 布局: `grid grid-cols-2`
  - 间距: `gap-4` = 16px

#### 单个操作按钮
- **容器**:
  - padding: `p-4` = 16px
  - 圆角: `rounded-[14px]`
  - 背景: `rgba(255, 255, 255, 0.6)` (浅色)
  - 边框: `1px solid rgba(0, 0, 0, 0.05)`
  - 悬停: `bg-black/[0.03]`
  - 对齐: `text-left`

- **图标**:
  - 尺寸: 24px
  - 颜色: 根据类型（Grid/Settings）
  - 下边距: `mb-2` = 8px

- **标题**:
  - 字体: `font-medium`
  - 颜色: `#1e293b`

- **描述**:
  - 字体: `text-sm` = 14px
  - 颜色: `#64748b`
  - 上边距: `mt-1` = 4px

---

## GlassCard 样式定义

### 浅色模式
- **背景**: `bg-white/70` = `rgba(255, 255, 255, 0.7)`
- **边框**: `border-black/5` = `rgba(0, 0, 0, 0.05)`
- **圆角**: `rounded-[20px]`
- **阴影**: `shadow-[0_30px_60px_rgba(0,0,0,0.06)]`

### 深色模式
- **背景**: `bg-white/[0.05]` = `rgba(255, 255, 255, 0.05)`
- **边框**: `border-white/10` = `rgba(255, 255, 255, 0.1)`
- **圆角**: `rounded-[20px]`
- **阴影**: `shadow-[0_30px_80px_rgba(0,0,0,0.8)]`

---

## 颜色系统

### 文本颜色（浅色模式）
- **主文本**: `text-slate-900` = `#1e293b`
- **次要文本**: `text-slate-500` = `#64748b`

### 文本颜色（深色模式）
- **主文本**: `text-slate-100` = `#f1f5f9`
- **次要文本**: `text-slate-400` = `#94a3b8`

### 强调色
- **蓝色渐变起始**: `#0A84FF`
- **蓝色渐变结束**: `#0051C7`
- **橙色**: `#fb923c` (orange-400)
- **绿色**: `#4ade80` (green-400) 或 `#22c55e` (green-500)
- **红色**: `#f87171` (red-400) 或 `#ef4444` (red-500)

---

## 间距系统

| Tailwind类 | 像素值 |
|-----------|--------|
| `gap-1`, `space-x-1`, `space-y-1`, `mb-1` | 4px |
| `gap-2`, `space-x-2`, `space-y-2`, `mb-2` | 8px |
| `gap-3`, `space-x-3`, `space-y-3`, `mb-3` | 12px |
| `gap-4`, `space-x-4`, `space-y-4`, `mb-4` | 16px |
| `gap-6`, `space-x-6`, `space-y-6`, `mb-6` | 24px |
| `gap-8`, `space-x-8`, `space-y-8`, `mb-8` | 32px |

---

## 圆角系统

| Tailwind类 | 像素值 |
|-----------|--------|
| `rounded-[10px]` | 10px |
| `rounded-[14px]` | 14px |
| `rounded-[16px]` | 16px |
| `rounded-[20px]` | 20px |
| `rounded-[24px]` | 24px |

---

## 阴影系统

### 浅色模式
- **卡片阴影**: `0 30px 60px rgba(0,0,0,0.06)`
- **容器阴影**: `0 30px 60px rgba(0,0,0,0.06)`

### 深色模式
- **卡片阴影**: `0 30px 80px rgba(0,0,0,0.8)`
- **容器阴影**: `0 30px 80px rgba(0,0,0,0.8)`

---

## 滚动条样式

- **宽度**: 4px (vertical) / 4px (horizontal)
- **背景**: 透明
- **滑块颜色**: `rgba(60,60,67,0.18)` (浅色) / `rgba(235,235,245,0.18)` (深色)
- **滑块hover**: `rgba(60,60,67,0.36)` (浅色) / `rgba(235,235,245,0.36)` (深色)
- **圆角**: `border-radius: 999px`
