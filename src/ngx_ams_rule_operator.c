#include "ngx_ams_rule_operator.h"

int ams_rule_operate_beginsWith(ngx_http_request_t *r, ams_rule_var_cooked_t *var, ngx_str_t str)
{
    ngx_str_t value = ngx_null_string;
    void*     iter  = NULL;

    if (var->get) {
        value = var->get(r);
        if (str.len > value.len) {
            return false;
        }
        if (0 == strncmp(str.data, value.data, str.len)) {
            return true;
        }else{
            return false;
        }
    }

    if (var->get_selection) {
        value = var->get_selection(r, var->selection);
        if (str.len > value.len) {
            return false;
        }
        if (0 == strncmp(str.data, value.data, str.len)) {
            return true;
        }else{
            return false;
        }
    }

    if (var->iter && var->next) {
        if (NULL == (iter = var->iter(r))) {
            return false;
        }
        for (value = var->next(r, iter); value != ngx_null_string; value=var->next(r,iter)) // TODO check null string equal
        {
            if (str.len > value.len) {
                continue;
            }
            if (0 == strncmp(str.data, value.data, str.len)) {
                return true;
            }else{
                continue;
            }
        }
        return false;
    }

    return false;
}

ams_rule_operator_t *ams_rule_operators[] = {
    AMS_RULE_OPERATOR(beginsWith)
    ams_rule_null_operator
};

int ams_rule_operator_parse(ams_rule_operate_cooked_t* operator_cooked, ngx_str_t str)
{
    char*                       start           = str.data;
    int                         pos             = 0; 
    ams_rule_operator_t*        operator        = NULL;
    bool                        negative        = false;
    int                         ret             = NGX_ERROR;
    
    if (str.len == 0) {
        goto end;
    }
    if (str.len>=2 && *start == '!' && *(start+1) == '@') {
        operator_cooked->negative = true;
        start++;
    }
    if (*start == '@') {
        start++;
        for ( ;start+pos < str.data+str.len; pos++) { 
            if (*(start+pos) == ' ' || *(start+pos) == '\t') {
                break;
            }
        }
        if (start+pos >=str.data+str.len) {
            goto end;
        }
        operate_cooked->name = { start, pos };
        start += pos+1;
        goto parse_arg;
    }else{
        if (NULL == (operator = ams_rule_operator_find(ngx_string("rx")))) {
            goto end;
        }
        operator_cooked->name = ngx_string("rx");
        operator_cooked->op = operator->op;
        goto parse_arg;
    }

  parse_arg:
    operator_cooked.arg = {start, str.data-start}
    ret = NGX_OK;

  end:
    return ret;
}
