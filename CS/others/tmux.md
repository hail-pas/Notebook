# reference cards

## 常用
```shell
tmux ls  # 列出所有会话
tmux new -s <session-name> -n <window-name>  # 创建新会话
tmux a -t <session-name>  # 连接到会话
tmux kill-session -t <session-name>  # 关闭会话
tmux ls | grep : | cut -d. -f1 | awk '{print substr($1, 0, length($1)-1)}' | xargs kill # 关闭所有会话

# tmux内 C-b
C-b :    # 进入命令模式
    setw -g mode-keys emacs    # 设置命令模式为emacs风格
    set -g mouse on            # 开启鼠标

## session
C-b ?    # 显示快捷键帮助
C-b s    # 列出所有会话
C-b :new -s <session-name> -n <window-name>  # 创建新会话
C-b $    # 重命名当前会话
C-b d    # 断开当前会话


## window
C-b c    # 创建新窗口
C-b &    # 关闭当前窗口
C-b n    # 切换到下一个窗口
C-b p    # 切换到上一个窗口
C-b f    # 查找窗口
C-b ,    # 重命名当前窗口

### pane
C-b x    # 关闭当前窗格
C-b w    # 列出所有窗格
C-b t    # 显示时钟
C-b %    # 竖直分割窗口
C-b "    # 水平分割窗口
C-b o    # 光标切换窗格
C-b q    # 显示窗格编号,并可以根据序号选择窗口
C-b z    # 最大/小化当前窗格
C-b {    # 向前置换窗格   } 向后置换窗格


### 编辑
C-b [       # 复制模式

```