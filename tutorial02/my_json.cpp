#include "my_json.h"
#include <assert.h>

struct context{
    const char * json;
};

void EXPECT(context * c,char ch){
    assert(c->json[0]==ch);
    c->json++;
}

void parse_whitespace(context *c){
    const char * p=c->json;
    while (*p==' ' || *p=='\t' || *p=='\n' || *p=='\r')
    {
        p++;
        /* code */
    }
    c->json=p;
}

my_json::PARSE_STATUS parse_null(context * c,my_json::Value & value){
    EXPECT(c,'n');
    if(c->json[0]!='u' || c->json[1]!='l' || c->json[2]!='l'){
        return my_json::PARSE_STATUS::INVALID_VALUE;
    }
    c->json+=3;
    value=std::monostate{};
    return my_json::PARSE_STATUS::OK;
}


my_json::PARSE_STATUS parse_true(context * c,my_json::Value & value){
    EXPECT(c,'t');
    if(c->json[0]!='r' || c->json[1]!='u' || c->json[2]!='e'){
        return my_json::PARSE_STATUS::INVALID_VALUE;
    }
    c->json+=3;
    value=true;
    return my_json::PARSE_STATUS::OK;
}

my_json::PARSE_STATUS parse_false(context * c,my_json::Value & value){
    EXPECT(c,'f');
    if(c->json[0]!='a' || c->json[1]!='l' && c->json[2]!='s' || c->json[3]!='e'){
        return my_json::PARSE_STATUS::INVALID_VALUE;
    }
    c->json+=4;
    value=false;
    return my_json::PARSE_STATUS::OK;
}

my_json::PARSE_STATUS parse_value(context *c,my_json::Value & value){
    switch (*c->json)
    {
    case 'n':
        return parse_null(c,value);
    case 't':
        return parse_true(c,value);
    case 'f':
        return parse_false(c,value);
    case '\0':
        return my_json::PARSE_STATUS::EXPECT_VALUE;
    default:
        return my_json::PARSE_STATUS::INVALID_VALUE;
    }
}

namespace my_json{
my_json::PARSE_STATUS parse(const char *json,my_json::Value & value){
    context c;
    c.json=json;
    parse_whitespace(&c);
    value=std::monostate{};
    my_json::PARSE_STATUS status=parse_value(&c,value);
    if(status==my_json::PARSE_STATUS::OK){
        parse_whitespace(&c);
        if(*c.json==0){
            return status;
        }else{
            return my_json::PARSE_STATUS::ROOT_NOT_SING;
        }
    }

    return status;
}
}
