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
// Created by wangyunlai on 2021/6/11.
//

#include "common/defs.h"
#include <algorithm>
#include <string.h>

namespace common {

int compare_int(void* arg1, void* arg2)
{
    int v1 = *(int*)arg1;
    int v2 = *(int*)arg2;
    return v1 - v2;
}

int compare_date(void* arg1, void* arg2)
{
    int v1 = *(unsigned*)arg1;
    int v2 = *(unsigned*)arg2;
    return v1 - v2;
}

int compare_float(void* arg1, void* arg2)
{
    float v1 = *(float*)arg1;
    float v2 = *(float*)arg2;
    float cmp = v1 - v2;
    if (cmp > EPSILON) {
        return 1;
    }
    if (cmp < -EPSILON) {
        return -1;
    }
    return 0;
}

int compare_string(void* arg1, int arg1_max_length, void* arg2, int arg2_max_length)
{
    const char* s1 = (const char*)arg1;
    const char* s2 = (const char*)arg2;
    int maxlen = std::min(arg1_max_length, arg2_max_length);
    int result = strncmp(s1, s2, maxlen);
    if (0 != result) {
        return result;
    }

    if (arg1_max_length > maxlen) {
        return s1[maxlen] - 0;
    }

    if (arg2_max_length > maxlen) {
        return 0 - s2[maxlen];
    }
    return 0;
}

bool like_match(const std::string &s1, const std::string &s2){
  int l1 = s1.length(), l2 = s2.length();
  std::vector<uint8_t> state((l1 + 1) * (l2 + 1) + 1, 0);
  /*state ::=
  * first i characters in s2(i.e s2[0..i-1]) and first j characters in s1 can match -> state[i * (l1 + 1) + j] = true;
  * else state[i * (l1 + 1) + j] = false;
  * use uint8_t instead of bool to avoid unnecessary problems.
  */
  state[0] = 1;
  bool can_match = true;
  //i -> viewed part of s2
  //can_match -> reused as 
  for(int i = 0; i < l2 && can_match; ++i){
    can_match = false;
    switch (s2[i])
    {
    case '_':
      for(int j = 0; j < l1; ++j){
        can_match |= state[i * (l1 + 1) + j];
        state[(i + 1) * (l1 + 1) + j + 1] = state[i * (l1 + 1) + j];
      }
      break;
    case '%':
      for(int j = 0; j <= l1; ++j){
        can_match |= state[i * (l1 + 1) + j];
        state[(i + 1) * (l1 + 1) + j] = can_match;
      }
      state[(i + 1) * (l1 + 1) + l1] = can_match;
      break;
    default:
      for(int j = 0; j < l1; ++j){
        bool can_shift = state[i * (l1 + 1) + j] && s1[j] == s2[i];
        can_match |= can_shift;
        state[(i + 1) * (l1 + 1) + j + 1] = can_shift;
      }
      break;
    }
  }
  return state[l2 * (l1 + 1) + l1];
}
} // namespace common
