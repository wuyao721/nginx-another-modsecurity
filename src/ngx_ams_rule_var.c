#include "ngx_ams_rule_var.h"

#define AMS_RULE_VAR_PARSE_STATE_NAME 1
#define AMS_RULE_VAR_PARSE_STATE_SELETION 2

int ams_rule_var_get_collection_count_args(ngx_http_request_t *r)
{
    
}

void* ams_rule_var_get_collection_iter_args(ngx_http_request_t *r)
{
    
}

int ams_rule_var_get_collection_next_args(ngx_http_request_t *r, void *iter)
{
    
}


// REQUEST_COOKIES|!REQUEST_COOKIES:/__utm/|REQUEST_COOKIES_NAMES|ARGS_NAMES|ARGS|XML:/*

int ams_rule_var_parse(ngx_array_t *vars, ngx_str_t str)
{
    char*                  start     = NULL;
    int                    pos       = 0; 
    ams_rule_var_t*        var       = NULL;
    ams_rule_var_cooked_t* varck     = NULL;
    ngx_str_t              varname   = ngx_null_string;
    ngx_str_t              selection = ngx_null_string;
    bool                   exclusive = false;
    bool                   count     = false;
    int                    state     = AMS_RULE_VAR_PARSE_STATE_NAME;
    
    for (start=str.data;start+pos<=str.data+str.len;) {
        if (start+pos >= str.data+str.len) {
            switch (state) {
                case AMS_RULE_VAR_PARSE_STATE_VAR:
                    if (exclusive == true) {
                        if (NULL == (varck = ams_rule_var_cooked_find(vars, varname))) {
                            return NGX_ERROR;                              
                        }
                        varck->selection = selection;
                    }
                    pos++;
                    goto init_state;
                    break;
                case AMS_RULE_VAR_PARSE_STATE_SELECTION:
                    pos++;
                    goto add_var_cooked;
                    break;
                default:
                    return NGX_ERROR;
            }
        }
        switch (state) {
            case AMS_RULE_VAR_PARSE_STATE_VAR:
                switch(*(start+pos)){
                    case '&':
                        if (pos != 0) {
                            return NGX_ERROR;
                        }
                        count = true;
                        break;
                    case '!':
                        if (pos != 0) {
                            return NGX_ERROR;
                        }
                        exclusive = true;
                        break;
                    case ':':
                        varname->data = start;
                        varname->len = pos;
                        start += pos+1;
                        pos = 0;
                        state = AMS_RULE_VAR_PARSE_STATE_SELETION;
                        break;
                    case '|':
                        varname->data = start;
                        varname->len = pos;
                        start += pos+1;
                        pos = 0;
                        goto add_var_cooked;
                        break;
                    default:
                        pos++;
                        break;
                }
                break;
            case AMS_RULE_VAR_PARSE_STATE_SELECTION:
                if (*(start+pos) == '|') {
                    selection->data = start;
                    selection->len = pos;
                    start += pos+1;
                    pos = 0;

                    if (exclusive == true) {
                        if (NULL == (varck = ams_rule_var_cooked_find(vars, varname))) {
                            return NGX_ERROR;                              
                        }
                        varck->selection = selection;
                    }
                    goto init_state;
                }
                break;

        }
      add_var_cooked:
        if (NULL == (var = ams_rule_var_find(varname)))
        {
            // TODO
            return NGX_ERROR;
        }
        if (NULL == (varck = ngx_array_push(vars)))
        {
            return NGX_ERROR;
        }
        ams_rule_var_cooked_init(varck);
        if (NULL != var->get) {
            varck->get = var->get;
        }
        else if (count == true) {
            varck->count = var->count;
        }
        else {
            varck->selection = selection;
            varck->iter = var->iter;
            varck->next = var->next;
        }                            
      init_state:
        varname = ngx_null_string;
        selection = ngx_null_string;
        exclusive = false;
        count = false;
        state = AMS_RULE_VAR_PARSE_STATE_VAR;
    }

    return NGN_OK;
}

void ams_rule_var_cooked_init(ams_rule_var_cooked_t* var)
{
    var->selection = ngx_null_string;
    var->count = NULL;
    var->iter = NULL;
    var->next = NULL;
    var->get = NULL;
    var->exclusions = NULL;
}

ams_rule_var_t ams_rule_vars[] = {
    AMS_RULE_VAR(ARGS, COLLECTION)
    AMS_RULE_NULL_VAR
}

