//
// Created by merhab on 2023/4/3.
//

#pragma once


typedef enum  {
    color0,
    color1,
    black,
    white,
    darkGray,
    gray,
    lightGray,
    red,
    green,
    blue,
    cyan,
    magenta,
    yellow,
    darkRed,
    darkGreen,
    darkBlue,
    darkCyan,
    darkMagenta,
    darkYellow,
    transparent
}GlobalColor;
typedef enum AlignmentFlag {
    AlignLeft = 0x0001,
    AlignLeading = AlignLeft,
    AlignRight = 0x0002,
    AlignTrailing = AlignRight,
    AlignHCenter = 0x0004,
    AlignJustify = 0x0008,
    AlignAbsolute = 0x0010,
    AlignHorizontal_Mask = AlignLeft | AlignRight | AlignHCenter | AlignJustify | AlignAbsolute,

    AlignTop = 0x0020,
    AlignBottom = 0x0040,
    AlignVCenter = 0x0080,
    AlignBaseline = 0x0100,
    // Note that 0x100 will clash with Qt::TextSingleLine = 0x100 due to what the comment above
    // this enum declaration states. However, since Qt::AlignBaseline is only used by layouts,
    // it doesn't make sense to pass Qt::AlignBaseline to QPainter::drawText(), so there
    // shouldn't really be any ambiguity between the two overlapping enum values.
    AlignVertical_Mask = AlignTop | AlignBottom | AlignVCenter | AlignBaseline,

    AlignCenter = AlignVCenter | AlignHCenter
}AlignmentFlag;

typedef enum  {
    Unchecked,
    PartiallyChecked,
    Checked
}CheckState;
