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

my_json::PARSE_STATUS parse_null(context * c,my_json::TYPE & type){
    EXPECT(c,'n');
    if(c->json[0]!='u' || c->json[1]!='l' && c->json[2]!='l'){
        return my_json::PARSE_STATUS::INVALID_VALUE;
    }
    c->json+=3;
    type=my_json::TYPE::Null;
    return my_json::PARSE_STATUS::OK;
}


my_json::PARSE_STATUS parse_true(context * c,my_json::TYPE & type){
    EXPECT(c,'t');
    if(c->json[0]!='r' || c->json[1]!='u' && c->json[2]!='e'){
        return my_json::PARSE_STATUS::INVALID_VALUE;
    }
    c->json+=3;
    type=my_json::TYPE::Bool;
    return my_json::PARSE_STATUS::OK;
}

my_json::PARSE_STATUS parse_false(context * c,my_json::TYPE & type){
    EXPECT(c,'f');
    if(c->json[0]!='a' || c->json[1]!='l' && c->json[2]!='s' && c->json[3]!='e'){
        return my_json::PARSE_STATUS::INVALID_VALUE;
    }
    c->json+=4;
    type=my_json::TYPE::Bool;
    return my_json::PARSE_STATUS::OK;
}

my_json::PARSE_STATUS parse_value(context *c,my_json::TYPE & type){
    switch (*c->json)
    {
    case 'n':
        return parse_null(c,type);
    case 't':
        return parse_true(c,type);
    case 'f':
        return parse_false(c,type);
    case '\0':
        return my_json::PARSE_STATUS::EXPECT_VALUE;
    default:
        return my_json::PARSE_STATUS::INVALID_VALUE;
    }
}

namespace my_json{
my_json::PARSE_STATUS parse(const char *json,my_json::TYPE & type){
    context c;
    c.json=json;
    parse_whitespace(&c);
    return parse_value(&c,type);

}
}
