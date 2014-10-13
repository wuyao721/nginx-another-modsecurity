#include "ngx_ams_rule.h"

char *ngx_http_ams_cmd_secrule(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_ams_loc_conf_t *alcf = conf;
    ngx_str_t arg1, arg2;
    ams_rule_t *rule;
    char *p;
    char *start;
    ngx_str_t *var;
    
    // TODO strdup arg1, arg2
    if (NULL == (rule = ngx_palloc(cf->pool, sizeof(ams_rule_t)))) {
        return NULL;
    }
    if (NGX_OK != ngx_init_array(rule->vars, 4, sizeof(ngx_str_t))) {
        return NULL;
    }
    ngx_ams_rule_var_parse(&rule->vars, &arg1);
    ngx_ams_rule_operator_parse(&rule->vars, &arg2);
    ngx_ams_rule_action_parse(&rule, &arg3);
}

