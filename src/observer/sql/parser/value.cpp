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
// Created by WangYunlai on 2023/06/28.
//

#include "sql/parser/value.h"
#include "common/lang/comparator.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "storage/field/field.h"
#include <sstream>
#include <cmath>
#include "value.h"

const char* ATTR_TYPE_NAME[] = { "undefined", "chars", "ints", "dates", "floats", "null", "booleans", "texts" };

const char* attr_type_to_string(AttrType type)
{
    if (type >= UNDEFINED && type <= TEXTS) {
        return ATTR_TYPE_NAME[type];
    }
    return "unknown";
}
AttrType attr_type_from_string(const char* s)
{
    for (unsigned int i = 0; i < sizeof(ATTR_TYPE_NAME) / sizeof(ATTR_TYPE_NAME[0]); i++) {
        if (0 == strcmp(ATTR_TYPE_NAME[i], s)) {
            return (AttrType)i;
        }
    }
    return UNDEFINED;
}

Value::Value(int val)
{
    set_int(val);
}

Value::Value(float val)
{
    set_float(val);
}

Value::Value(bool val)
{
    set_boolean(val);
}

Value::Value(date_t val)
{
    set_date(val);
}

Value::Value(null_t val)
{
    set_null();
}

Value::Value(const char* s, int len /*= 0*/)
{
    set_string(s, len);
}

void Value::set_data(char* data, int length)
{
    switch (attr_type_) {
    case TEXTS:
    case CHARS: {
        set_string(data, length);
    } break;
    case INTS: {
        num_value_.int_value_ = *(int*)data;
        length_ = length;
    } break;
    case FLOATS: {
        num_value_.float_value_ = *(float*)data;
        length_ = length;
    } break;
    case DATES: {
        num_value_.date_value_ = *(date_t*)data;
        length_ = length;
    } break;
    case BOOLEANS: {
        num_value_.bool_value_ = *(int*)data != 0;
        length_ = length;
    } break;
    case NULLS:{
    } break;
    default: {
        LOG_WARN("unknown data type: %d", attr_type_);
    } break;
    }
}
void Value::set_int(int val)
{
    attr_type_ = INTS;
    num_value_.int_value_ = val;
    length_ = sizeof(val);
}

void Value::set_float(float val)
{
    attr_type_ = FLOATS;
    num_value_.float_value_ = val;
    length_ = sizeof(val);
}

void Value::set_date(date_t val)
{
    attr_type_ = DATES;
    num_value_.date_value_ = val;
    length_ = sizeof(val);
}

void Value::set_null()
{
    attr_type_ = NULLS;
    num_value_.null_value_ = 0;
    length_ = sizeof(null_t);
}

void Value::set_boolean(bool val)
{
    attr_type_ = BOOLEANS;
    num_value_.bool_value_ = val;
    length_ = sizeof(val);
}
void Value::set_string(const char* s, int len /*= 0*/)
{
    attr_type_ = CHARS;
    if (len > 0) {
        len = strnlen(s, len);
        str_value_.assign(s, len);
    } else {
        str_value_.assign(s);
    }
    length_ = str_value_.length();
}

void Value::set_value(const Value& value)
{
    switch (value.attr_type_) {
    case INTS: {
        set_int(value.get_int());
    } break;
    case FLOATS: {
        set_float(value.get_float());
    } break;
    case DATES: {
        set_date(date_t(value.get_int()));
    } break;
    case TEXTS:
    case CHARS: {
        set_string(value.get_string().c_str());
    } break;
    case BOOLEANS: {
        set_boolean(value.get_boolean());
    } break;
    case UNDEFINED: {
        ASSERT(false, "got an invalid value type");
    } break;
    }
}

const char* Value::data() const
{
    switch (attr_type_) {
    case TEXTS:
    case CHARS: {
        return str_value_.c_str();
    } break;
    default: {
        return (const char*)&num_value_;
    } break;
    }
}

std::string Value::to_string() const
{
    std::stringstream os;
    switch (attr_type_) {
    case INTS: {
        os << num_value_.int_value_;
    } break;
    case FLOATS: {
        os << common::double_to_str(num_value_.float_value_);
    } break;
    case DATES: {
        os << common::date_to_str(num_value_.date_value_.date_hash);
    } break;
    case BOOLEANS: {
        os << num_value_.bool_value_;
    } break;
    case TEXTS:
    case CHARS: {
        os << str_value_;
    } break;
    case NULLS: {
        os << "null";
        break;
    }
    default: {
        LOG_WARN("unsupported attr type: %d", attr_type_);
    } break;
    }
    return os.str();
}

int Value::compare(const Value &other) const
{
  if (this->attr_type_ == other.attr_type_) {
    switch (this->attr_type_) {
      case INTS: {
        return common::compare_int((void *)&this->num_value_.int_value_, (void *)&other.num_value_.int_value_);
      } break;
      case FLOATS: {
        return common::compare_float((void *)&this->num_value_.float_value_, (void *)&other.num_value_.float_value_);
      } break;
      case DATES: {
        return common::compare_int((void *)&this->num_value_.date_value_, (void *)&other.num_value_.date_value_);
      }
      case TEXTS:
      case CHARS: {
        return common::compare_string((void *)this->str_value_.c_str(),
            this->str_value_.length(),
            (void *)other.str_value_.c_str(),
            other.str_value_.length());
      } break;
      case BOOLEANS: {
        return common::compare_int((void *)&this->num_value_.bool_value_, (void *)&other.num_value_.bool_value_);
      }
      case NULLS: {
        return 0;
      }
      default: {
        LOG_WARN("unsupported type: %d", this->attr_type_);
      }
    }
  } else if (this->attr_type_ == NULLS || other.attr_type_ == NULLS) {
    return -1;
  } else if (this->attr_type_ == INTS && other.attr_type_ == FLOATS) {
    float this_data = this->num_value_.int_value_;
    return common::compare_float((void *)&this_data, (void *)&other.num_value_.float_value_);
  } else if (this->attr_type_ == FLOATS) {
    Value copy_other(other);
    bool cast_result = copy_other.try_cast(FLOATS);
    if (!cast_result) {
      return -1;
    }
    float other_data = copy_other.num_value_.float_value_;
    return common::compare_float((void *)&this->num_value_.float_value_, (void *)&other_data);
  } else if (this->attr_type_ == INTS) {
    Value copy_other(other);
    bool cast_result = copy_other.try_cast(INTS);
    if (!cast_result) {
      return -1;
    }
    int this_data = this->num_value_.int_value_;
    return common::compare_int((void *)&this_data, (void *)&copy_other.num_value_.int_value_);
  } else if (this->attr_type_ == CHARS || this->attr_type_ == TEXTS) {
    Value copy_this(*this);
    bool  cast_result = copy_this.try_cast(other.attr_type_);
    if (!cast_result) {
      return -1;
    }
    if (other.attr_type_ == FLOATS) {
      float other_data = other.num_value_.float_value_;
      return common::compare_float((void *)copy_this.data(), (void *)&other_data);
    } else {
      int other_data = other.num_value_.int_value_;
      return common::compare_int((void *)copy_this.data(), (void *)&other_data);
    }
  }
  LOG_WARN("not supported");
  return -1;  // TODO return rc?
}

int Value::get_int() const
{
    switch (attr_type_) {
    case CHARS: 
    case TEXTS:{
        try {
            return (int)(std::stol(str_value_));
        } catch (std::exception const& ex) {
            LOG_TRACE("failed to convert string to number. s=%s, ex=%s", str_value_.c_str(), ex.what());
            return 0;
        }
    }
    case INTS: case DATES:{
        return num_value_.int_value_;
    }
    case FLOATS: {
        return (int)(round(num_value_.float_value_));
    }
    case BOOLEANS: {
        return (int)(num_value_.bool_value_);
    }
    default: {
        LOG_WARN("unknown data type. type=%d", attr_type_);
        return 0;
    }
    }
    return 0;
}

float Value::get_float() const
{
    switch (attr_type_) {
    case CHARS: 
    case TEXTS: {
        try {
            return std::stof(str_value_);
        } catch (std::exception const& ex) {
            LOG_TRACE("failed to convert string to float. s=%s, ex=%s", str_value_.c_str(), ex.what());
            return 0.0;
        }
    } break;
    case INTS: {
        return float(num_value_.int_value_);
    } break;
    case FLOATS: {
        return num_value_.float_value_;
    } break;
    case BOOLEANS: {
        return float(num_value_.bool_value_);
    } break;
    default: {
        LOG_WARN("unknown data type. type=%d", attr_type_);
        return 0;
    }
    }
    return 0;
}

std::string Value::get_string() const
{
    return this->to_string();
}

bool Value::get_boolean() const
{
    switch (attr_type_) {
    case CHARS: 
    case TEXTS: {
        try {
            float val = std::stof(str_value_);
            if (val >= EPSILON || val <= -EPSILON) {
                return true;
            }

            int int_val = std::stol(str_value_);
            if (int_val != 0) {
                return true;
            }

            return !str_value_.empty();
        } catch (std::exception const& ex) {
            LOG_TRACE("failed to convert string to float or integer. s=%s, ex=%s", str_value_.c_str(), ex.what());
            return !str_value_.empty();
        }
    } break;
    case INTS: {
        return num_value_.int_value_ != 0;
    } break;
    case FLOATS: {
        float val = num_value_.float_value_;
        return val >= EPSILON || val <= -EPSILON;
    } break;
    case DATES: {
        return true;
    } break;
    case NULLS: {
        return false;
    } break;
    case BOOLEANS: {
        return num_value_.bool_value_;
    } break;
    default: {
        LOG_WARN("unknown data type. type=%d", attr_type_);
        return false;
    }
    }
    return false;
}

bool Value::is_null() const { return this->attr_type_ == AttrType::NULLS; }

bool Value::make_negative(){
    switch (attr_type_) {
        case INTS:
            num_value_.int_value_ = -num_value_.int_value_;
        break;
        case FLOATS:
            num_value_.float_value_ = -num_value_.float_value_;
        break;
        default:
            LOG_WARN("type=%d cannot make negative.", attr_type_);
            return false;
    }
    return true;
}

bool Value::try_cast(AttrType type){
    if(attr_type_ == AttrType::NULLS)
        return true;
    switch(type){
        case INTS:{
            num_value_.int_value_ = get_int();
            attr_type_ = type;
            break;
        }
        case FLOATS:{
            num_value_.float_value_ = get_float();
            attr_type_ = type;
            break;
        }
        case CHARS:
        case TEXTS: {
            str_value_ = get_string();
            if(str_value_.empty())
            return false;
            attr_type_ = type;
            break;
        }
        case BOOLEANS:{
            num_value_.bool_value_ = get_boolean();
            attr_type_ = type;
            break;
        }
        default:{
            LOG_WARN("cast undefined(id=%d)", static_cast<int>(type));
            return false;
        }
    }
    return true;
}
