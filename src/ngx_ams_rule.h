#include "ngx_ams_rule_var.h"
#include "ngx_ams_rule_action.h"
#include "ngx_ams_rule_operator.h"

struct ams_rule_s{
    //ngx_pool_t *pool;
    ngx_str_t id;
    ngx_str_t filepath;
    int lineno;
    ngx_str_t append;
    char phase;
    char rev;
    char maturity;
    char accuracy;
    ngx_array_t vars;
    ams_rule_operate_cb cb;
    ngx_str_t operator_arg;
    ngx_array_t actions;
}

struct ams_request_s{
    //ngx_pool_t *pool;
    char allow:1;
    char drop:1;
    char deny:1;
    ngx_str_t append;
    char phase;
    char rev;
    char maturity;
    char accuracy;
}

typedef struct ams_rule_s ams_rule_t;
