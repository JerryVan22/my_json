#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leptjson.h"
#include "my_json.h"
static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;


template<typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e)
{
    return stream << static_cast<typename std::underlying_type<T>::type>(e);
}

void EXPECT_EQ_INT(const my_json::TYPE & expect, const my_json::TYPE & actual,std::string file_name,int line){
    test_count++;
    if(expect==actual){
        test_pass++;
    }else{
        std::cout<<file_name<<":"<<line<<": expect: "<<expect<<" actual: "<<actual<<std::endl;
        main_ret=1;
    }
}

void EXPECT_EQ_INT(const my_json::PARSE_STATUS & expect, const my_json::PARSE_STATUS & actual,std::string file_name,int line){
    test_count++;
    if(expect==actual){
        test_pass++;
    }else{
        std::cout<<file_name<<":"<<line<<": expect: "<<expect<<" actual: "<<actual<<std::endl;
        main_ret=1;
    }
}


static void test_parse_null() {
    my_json::TYPE v=my_json::TYPE::Bool;
 
    EXPECT_EQ_INT(my_json::PARSE_STATUS::OK, my_json::parse("null",v),__FILE__,__LINE__ );
    EXPECT_EQ_INT(my_json::TYPE::Null, v,__FILE__,__LINE__);
}

static void test_parse_expect_value() {
    my_json::TYPE v=my_json::TYPE::Bool;

    EXPECT_EQ_INT(my_json::PARSE_STATUS::EXPECT_VALUE, my_json::parse( "",v),__FILE__,__LINE__);
    EXPECT_EQ_INT(my_json::TYPE::Null, v,__FILE__,__LINE__);

    v = my_json::TYPE::Bool;
    EXPECT_EQ_INT(my_json::PARSE_STATUS::EXPECT_VALUE, my_json::parse(" ",v),__FILE__,__LINE__);
    EXPECT_EQ_INT(my_json::TYPE::Null, v,__FILE__,__LINE__);
}

static void test_parse_invalid_value() {
      my_json::TYPE v=my_json::TYPE::Bool;
  
    EXPECT_EQ_INT(my_json::PARSE_STATUS::INVALID_VALUE, my_json::parse( "nul",v),__FILE__,__LINE__);
    EXPECT_EQ_INT(my_json::TYPE::Null, v,__FILE__,__LINE__);


    EXPECT_EQ_INT(my_json::PARSE_STATUS::INVALID_VALUE, my_json::parse("?",v),__FILE__,__LINE__);
    EXPECT_EQ_INT(my_json::TYPE::Null, v,__FILE__,__LINE__);
}

static void test_parse_root_not_singular() {
      my_json::TYPE v=my_json::TYPE::Bool;
   
    EXPECT_EQ_INT(my_json::PARSE_STATUS::ROOT_NOT_SING, my_json::parse( "null x",v),__FILE__,__LINE__);
    EXPECT_EQ_INT(my_json::TYPE::Null, v,__FILE__,__LINE__);
}

static void test_parse() {
    test_parse_null();
    test_parse_expect_value();
    test_parse_invalid_value();
    test_parse_root_not_singular();
}

int main() {
    test_parse();
    printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}