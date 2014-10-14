#define AMS_RULE_ACTION_TYPE_DIRUPTIVE 0 
#define AMS_RULE_ACTION_TYPE_NON_DIRUPTIVE 1
#define AMS_RULE_ACTION_TYPE_FLOW 2
#define AMS_RULE_ACTION_TYPE_META_DATA 3
#define AMS_RULE_ACTION_TYPE_DATA 4

struct ams_rule_action_s{
    ngx_str_t name;
    int type;
    ams_rule_action action;
    ngx_str_t *data;
    ngx_array_t *datas;
};

struct ams_rule_action_cooked_s{
    ngx_str_t name;
    int type;
    ams_rule_action action;
    ngx_str_t *data;
    ngx_array_t *datas;
};

typedef struct ams_rule_action_s ams_rule_action_t;
typedef struct ams_rule_action_cooked_s ams_rule_action_cooked_t;

typedef void (*ams_rule_action)(ams_rule_t *areq, void *data);

#define AMS_RULE_NULL_ACTION  { ngx_null_string, NULL }
#define AMS_RULE_ACTION(arg1, type)              \
    {                                            \
        ngx_string(#arg1),                       \
        AMS_RULE_ACTION_TYPE_##type,             \
        ams_rule_action_##arg1,                  \
        NULL,                                    \
        NULL                                     \
    },

void ams_rule_action_allow(ams_rule_t *areq, void *data);

extern ams_rule_action_t ams_rule_actions[];

ams_rule_action ngx_ams_find_rule_action(ngx_str_t name);
