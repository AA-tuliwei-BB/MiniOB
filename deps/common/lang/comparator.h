/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by wangyunlai on 2021/6/11
//

#pragma once

//     enum AttrType {
//     UNDEFINED,
//     CHARS, ///< 字符串类型
//     INTS, ///< 整数类型(4字节)
//     DATES, ///< 日期类型(4字节)
//     FLOATS, ///< 浮点数类型(4字节)
//     NULLS, ///< 空类型(4字节)
//     BOOLEANS, ///< boolean类型，当前不是由parser解析出来的，是程序内部使用的
//     TEXTS,
// };
#include <string>
namespace common {

inline bool field_type_compare_compatible_table[8][8] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 0, 1, 1, 1, 1,
    0, 1, 1, 0, 1, 1, 1, 1,
    0, 0, 0, 1, 0, 1, 1, 1,
    0, 1, 1, 0, 1, 1, 1, 1,
    0, 1, 1, 1, 1, 1, 1, 1,
    0, 1, 1, 1, 1, 1, 1, 1,
    0, 1, 1, 1, 1, 1, 1, 1,
};
int compare_int(void* arg1, void* arg2);
int compare_float(void* arg1, void* arg2);
int compare_string(void* arg1, int arg1_max_length, void* arg2, int arg2_max_length);
int compare_date(void* arg1, void* arg2);
bool like_match(const std::string &s1, const std::string &s2);
}