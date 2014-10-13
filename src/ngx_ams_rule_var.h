#define AMS_RULE_VAR_TYPE_REGULAR_VAR 1
#define AMS_RULE_VAR_TYPE_COLLECTION 2
//#define AMS_RULE_VAR_ZONE_REQUEST 1
//#define AMS_RULE_VAR_ZONE_SERVER 2
//#define AMS_RULE_VAR_ZONE_RESPONSE 3

int ngx_ams_rule_var_parse(ngx_array_t *vars, ngx_str_t &string);
typedef ngx_str_t (*ams_var_get_reg)(ngx_http_request_t *r);
typedef int (*ams_var_get_collection_count)(ngx_http_request_t *r);
typedef void* (*ams_var_get_collection_iter)(ngx_http_request_t *r);
typedef ngx_str_t (*ams_var_get_collection_iter)(ngx_http_request_t *r, void *iter);

// eg
//ARGS collection or var
//ARGS:p
//!ARGS:p
//&ARGS
//!args:/re/

struct ams_rule_var_s{
    ngx_str_t name;
    int type;
    ams_rule_var_get_collection_count count;
    ams_rule_var_get_collection_iter iter;
    ams_rule_var_get_collection_next next;
    ams_rule_var_get_reg get;
}

struct ams_rule_var_cooked_s{
    ngx_str_t selection;
    ams_rule_var_get_collection_count count;
    ams_rule_var_get_collection_iter iter;
    ams_rule_var_get_collection_next next;
    ams_rule_var_get_reg get;
    ngx_array_t *exclusions;
}


typedef struct ams_rule_var_s ams_rule_var_t;
typedef struct ams_rule_var_cooked_s ams_rule_var_cooked_t;

#define AMS_RULE_NULL_VAR  { ngx_null_string, ngx_null_string, 0, 0, 0, NULL, NULL, NULL, NULL }
#define AMS_RULE_VAR(name, type, count, iter, next, get)    \
    {                                                       \
        ngx_string(#name),                                  \
        AMS_RULE_ACTION_TYPE_##type,                        \
        ams_rule_var_get_collection_count_##arg1,           \
        ams_rule_var_get_collection_iter_##arg1,            \
        ams_rule_var_get_collection_next_##arg1,            \
        ams_rule_var_get_reg_##arg1                         \
    },

