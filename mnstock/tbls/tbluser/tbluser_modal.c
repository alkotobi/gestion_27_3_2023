//
// Created by merhab on 2023/4/3.
//

#include "tbluser_modal.h"

tbluser_modal *tbluser_modal_init(tbluser_modal *modal) {
    if (!modal) modal= CQSqlModal_new(0);
    CQSqlModal_fnc_row_count(modal,)
    return modal;
}
