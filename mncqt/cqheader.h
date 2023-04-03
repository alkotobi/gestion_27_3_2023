#pragma once
#define Qt_LeftToRight 0
#define Qt_RightToLeft 1
#define Qt_LayoutDirectionAuto 2
typedef void QApplication ;
typedef void QString ;
typedef void QWidget ;
typedef void QLayout ;
typedef void QBoxLayout ;
typedef void QLayoutItem;
typedef void QVBoxLayout ;
typedef void QHBoxLayout ;
typedef void QVariant;
typedef void QFormLayout;
typedef void QGridLayout;
typedef void QLabel;
typedef void QPushButton; 
typedef void QIcon;
typedef void QAbstractButton;
typedef void QLineEdit;
typedef void QTableView;
typedef void QAbstractItemModel;
typedef void QSqlModal ;
typedef void QObject ;
//enum Qt::WindowTypeflags Qt::WindowFlags
//window_flags
#define Qt_Widget 0x00000000//This is the default type for QWidget. Widgets of this type are child widgets if they have a parent, and independent windows if they have no parent. See also Qt::Window and Qt::SubWindow.
#define Qt_Window 0x00000001//Indicates that the widget is a window, usually with a window system frame and a title bar, irrespective of whether the widget has a parent or not. Note that it is not possible to unset this flag if the widget does not have a parent.
#define Qt_Dialog (0x00000002 | Qt_Window)//Indicates that the widget is a window that should be decorated as a dialog (i.e., typically no maximize or minimize buttons in the title bar). This is the default type for QDialog. If you want to use it as a modal dialog, it should be launched from another window, or have a parent and used with the QWidget::windowModality property. If you make it modal, the dialog will prevent other top-level windows in the application from getting any input. We refer to a top-level window that has a parent as a secondary window.
#define Qt_Sheet ((0x00000004 | Qt_Window))//Indicates that the window is a sheet on macOS. Since using a sheet implies window modality, the recommended way is to use QWidget::setWindowModality(), or QDialog::open(), instead.
#define Qt_Drawer (Qt_Sheet | Qt_Dialog)//Indicates that the widget is a drawer on macOS.
#define Qt_Popup (0x00000008 | Qt_Window)//Indicates that the widget is a pop-up top-level window, i.e. that it is modal, but has a window system frame appropriate for pop-up menus.
#define Qt_Tool (Qt_Popup | Qt_Dialog)//Indicates that the widget is a tool window. A tool window is often a small window with a smaller than usual title bar and decoration, typically used for collections of tool buttons. If there is a parent, the tool window will always be kept on top of it. If there isn't a parent, you may consider using Qt::WindowStaysOnTopHint as well. If the window system supports it, a tool window can be decorated with a somewhat lighter frame. It can also be combined with Qt::FramelessWindowHint. On macOS, tool windows correspond to the NSPanel class of windows. This means that the window lives on a level above normal windows making it impossible to put a normal window on top of it. By default, tool windows will disappear when the application is inactive. This can be controlled by the Qt::WA_MacAlwaysShowToolWindow attribute.
#define Qt_ToolTip (Qt_Popup | Qt_Sheet)//Indicates that the widget is a tooltip. This is used internally to implement tooltips.
#define Qt_SplashScreen (Qt_ToolTip | Qt_Dialog)//Indicates that the window is a splash screen. This is the default type for QSplashScreen.
#define Qt_Desktop (0x00000010 | Qt_Window)//Indicates that this widget is the desktop. This is the type for QDesktopWidget.
#define Qt_SubWindow 0x00000012//Indicates that this widget is a sub-window, such as a QMdiSubWindow widget.
#define Qt_ForeignWindow (0x00000020 | Qt_Window)//Indicates that this window object is a handle representing a native platform window created by another process or by manually using native code.
#define Qt_CoverWindow (0x00000040 | Qt_Window)//Indicates that the window represents a cover window, which is shown when the application is minimized on some platforms.

//alignement

#define Qt_AlignLeft 0x0001//Aligns with the left edge.
#define Qt_AlignRight 0x0002//Aligns with the right edge.
#define Qt_AlignHCenter 0x0004//Centers horizontally in the available space.
#define Qt_AlignJustify 0x0008//Justifies the text in the available space.
#define Qt_AlignTop 0x0020//Aligns with the top.
#define Qt_AlignBottom 0x0040//Aligns with the bottom.
#define Qt_AlignVCenter 0x0080//Centers vertically in the available space.
#define Qt_AlignBaseline 0x0100//Aligns with the baseline
#define Qt_AlignCenter (Qt_AlignVCenter | Qt_AlignHCenter)//Centers in both dimensions
#define Qt_AlignAbsolute 0x0010//If  the widget's layout direction is Qt::RightToLeft (instead of Qt::LeftToRight, the default), Qt::AlignLeft refers to the right edge and Qt::AlignRight to the left edge. This is normally the desired behavior. If you want Qt::AlignLeft to always mean "left" and Qt::AlignRight to always mean "right", combine the flag with Qt::AlignAbsolute.
#define Qt_AlignLeading Qt_AlignLeft //Synonym for Qt::AlignLeft.
#define Qt_AlignTrailing Qt_AlignRight //Synonym for Qt::AlignRight.

//directions

#define QBoxLayout_LeftToRight 0//Horizontal from left to right.
#define QBoxLayout_RightToLeft 1//Horizontal from right to left.
#define QBoxLayout_TopToBottom 2//Vertical from top to bottom.
#define QBoxLayout_BottomToTop 3//Vertical from bottom to top.

//qInfo is qt5.5+ only.

