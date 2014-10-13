#include "ngx_ams_rule_operator.h"

int ams_rule_operate_request_cookies(ngx_http_request_t *r, ams_rule_t *rule)
{
    r.headers_in->cookies;
    item;
    int i;
    // TODO check cb not NULL
    for (item=r.headers_in->cookies->elts, i=0; i < nelts; i++) {
        item+i;
        // TODO get cookies's data
        ngx_str_t data;
        if (1 == rule.cb(&rule->operator_arg, &data) ){
            return 1;
        }
    }
}

int ams_rule_operate_cb_rx(ngx_str_t *arg, ngx_str_t *data)
{
    // TODO regular expression match
}

