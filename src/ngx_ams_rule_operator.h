
//typedef int (*ams_rule_operate_cb)(ngx_str_t *arg, ngx_str_t *data);
//typedef int (*ams_rule_operate)(ams_rule_t *rule);

int ams_rule_operator_parse(ams_rule_operate_cooked_t* operator_cooked, ngx_str_t str);
ams_rule_operator_t* ams_rule_operator_find(ngx_str_t name);
typedef int (*ams_rule_operate)(ngx_http_request_t *r, ams_rule_var_cooked_t *var, ngx_str_t str);

struct ams_rule_operator_s
{
    ngx_str_t name;
    ams_rule_operate op;
};

struct ams_rule_operator_cooked_s
{
    ngx_str_t name;
    ngx_str_t arg;
    bool negative;
    ams_rule_operate op;
};

typedef struct ams_rule_operator_s ams_rule_operator_t;
typedef struct ams_rule_operator_cooked_s ams_rule_operator_cooked_t;


#define ams_rule_null_operator { ngx_null_string, NULL }
#define AMS_RULE_OPERATOR(name)                             \
    {                                                       \
        ngx_string(#name),                                  \
        ams_rule_operate_##name                             \
    },

