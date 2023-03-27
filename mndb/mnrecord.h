//
// Created by merhab on 2023/3/18.
//

#pragma once
#include "mnvariantList.h"
#include "mn_db_const.h"

#ifdef __cplusplus
extern "C"
{
#endif
typedef mnvariantList mnrecord;
typedef mnarray mnrecordset;

mnrecordset* mnrecordset_new();
mnrecordset* mnrecordset_init(mnrecordset* rds);
mnrecord* mnrecordset_add(mnrecordset* rdset,mnrecord* rd);
mnrecordset* mnrecordset_clean(mnrecordset* rdset);
void mnrecordset_free(mnrecordset** rdset_hld);
void mnrecordset_clean_free(mnrecordset** rdset_hld);


#ifdef __cplusplus
}
#endif
