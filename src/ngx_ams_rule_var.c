
ams_rule_var_t ams_rule_vars[] = {
    AMS_RULE_VAR(ARGS, COLLECTION)
    AMS_RULE_NULL_VAR
}

int ngx_ams_rule_var_parse(ngx_array_t *vars, ngx_str_t *string)
{
    ams_rule_t *rule;
    char *p;
    char *start;
    ngx_str_t *var;
    
    start = arg1.data;
    p = arg1.data;
    while (1) {
        if (p >= arg1.data+arg1.len) {
            if ( p > start ){
                var = ngx_array_push(rule->args);
                var->data = start;
                var->len = p - start;
            }
            break;
        }
        if (*p == '|') {
            if ( p > start ){
                var = ngx_array_push(rule->args);
                var->data = start;
                var->len = p - start;
            }
            start = ++p;
        }
    }
    return NGN_OK;
}

