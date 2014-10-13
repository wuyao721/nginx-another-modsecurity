//SecRule REQUEST_COOKIES|!REQUEST_COOKIES:/__utm/|REQUEST_COOKIES_NAMES|ARGS_NAMES|ARGS|XML:/* "(/\*!?|\*/|[';]--|--[\s\r\n\v\f]|(?:--[^-]*?-)|([^\-&])#.*?[\s\r\n\v\f]|;?\\x00)" "phase:2,rev:'2',ver:'OWASP_CRS/2.2.9',maturity:'8',accuracy:'8',id:'981231',t:none,t:urlDecodeUni,block,msg:'SQL Comment Sequence Detected.',severity:'2',capture,logdata:'Matched Data: %{TX.0} found within %{MATCHED_VAR_NAME}: %{MATCHED_VAR}',tag:'OWASP_CRS/WEB_ATTACK/SQL_INJECTION',tag:'WASCTC/WASC-19',tag:'OWASP_TOP_10/A1',tag:'OWASP_AppSensor/CIE1',tag:'PCI/6.5.2',setvar:tx.anomaly_score=+%{tx.critical_anomaly_score},setvar:tx.sql_injection_score=+1,setvar:'tx.msg=%{rule.msg}',setvar:tx.%{rule.id}-OWASP_CRS/WEB_ATTACK/SQL_INJECTION-%{matched_var_name}=%{tx.0}"

#include "ngx_string.h"

#define PARSE_ACTION_STATE_PARSE_NAME 1
#define PARSE_ACTION_STATE_PARSE_VALUE 2
#define PARSE_ACTION_STATE_PARSE_VALUE_STRING 3

int ngx_ams_rule_init(ams_rule_t *rule)
{
    
}

struct ams_rule_action{
};
ams_rule_action
int ngx_ams_rule_parse_action(ams_rule_t *rule, ngx_str_t *s)
{
    char *start = NULL;
    int  pos    = 0;
    ngx_str_t actname;
    ngx_str_t actvalue;
    int state;
    ams_rule_action action;
    begin;
    
    state = PARSE_ACTION_STATE_PARSE_NAME;
    for (start=s,pos=0; start+pos<s->data+s->len;) {
        switch(state){
            case PARSE_ACTION_STATE_PARSE_NAME:
            {
                if (*(start+pos) == ':') {
                    actname->data = start;
                    actname->len = pos;
                    ngx_strip(&actname);
                    start = ++pos;
                    state = PARSE_ACTION_STATE_PARSE_VALUE;
                }
            }
            break;
            case PARSE_ACTION_STATE_PARSE_VALUE:
            {
                if (*(start+pos) == ',') {
                    actvalue->data = start;
                    actvalue->len = pos;
                    ngx_strip(&actvalue);
                    action = ngx_ams_find_rule_action(actname);
                    switch (action.type) {
                        case AMS_RULE_ACTION_TYPE_META_DATA:
                        {
                            action.action(rule, actvalue)                            
                        }
                        break;
                        case AMS_RULE_ACTION_TYPE_DIRUPTIVE:
                        {
                            
                        }
                        break;
                        case AMS_RULE_ACTION_TYPE_NON_DIRUPTIVE:

                    }
                    if (action.type == AMS_RULE_ACTION_TYPE_META_DATA) {
                        
                    }
                    ngx_arry_push(rule->actions)

                    start = ++pos;
                    state = PARSE_ACTION_STATE_PARSE_NAME;
                }
            }
            break;
            case PARSE_ACTION_STATE_PARSE_VALUE_STRING:
            {
                
            }
            break;
        }
    }
}
