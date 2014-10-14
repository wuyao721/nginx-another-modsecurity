#include "nginx_ams_rule_action.h"

void ams_rule_action_allow(ams_rule_t *areq, void *data)
{
    areq->allow = true;
}

void ams_rule_action_block(ams_rule_t *areq, void *data)
{
    areq->allow = true;
}

void ams_rule_action_append(ams_rule_t *areq, void *data)
{
    areq->append = *(ngx_str_t*)data;
}

void ams_rule_action_auditlog(ams_rule_t *areq, void *data)
{
    areq->append = *(ngx_str_t*)data;
}

void ams_rule_action_phase(ams_rule_t *areq, void *data)
{
    areq->phase = *(char *)data;
}

void ams_rule_action_rev(ams_rule_t *areq, void *data)
{
    areq->phase = *(char *)data;
}

void ams_rule_action_tag(ams_rule_t *areq, void *data)
{
    
}

void ams_rule_action_ver(ams_rule_t *areq, void *data)
{
    
}

void ams_rule_action_t(ams_rule_t *areq, void *data)
{
    
}

void ams_rule_action_msg(ams_rule_t *areq, void *data)
{
    
}

void ams_rule_action_capture(ams_rule_t *areq, void *data)
{
    
}

void ams_rule_action_logdata(ams_rule_t *areq, void *data)
{
    
}


struct ams_rule_action{
};
ams_rule_action
//SecRule REQUEST_COOKIES|!REQUEST_COOKIES:/__utm/|REQUEST_COOKIES_NAMES|ARGS_NAMES|ARGS|XML:/* "(/\*!?|\*/|[';]--|--[\s\r\n\v\f]|(?:--[^-]*?-)|([^\-&])#.*?[\s\r\n\v\f]|;?\\x00)" "phase:2,rev:'2',ver:'OWASP_CRS/2.2.9',maturity:'8',accuracy:'8',id:'981231',t:none,t:urlDecodeUni,block,msg:'SQL Comment Sequence Detected.',severity:'2',capture,logdata:'Matched Data: %{TX.0} found within %{MATCHED_VAR_NAME}: %{MATCHED_VAR}',tag:'OWASP_CRS/WEB_ATTACK/SQL_INJECTION',tag:'WASCTC/WASC-19',tag:'OWASP_TOP_10/A1',tag:'OWASP_AppSensor/CIE1',tag:'PCI/6.5.2',setvar:tx.anomaly_score=+%{tx.critical_anomaly_score},setvar:tx.sql_injection_score=+1,setvar:'tx.msg=%{rule.msg}',setvar:tx.%{rule.id}-OWASP_CRS/WEB_ATTACK/SQL_INJECTION-%{matched_var_name}=%{tx.0}"

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

ams_rule_action_t ams_rule_actions[] = {
    AMS_RULE_ACTION(allow, DIRUPTIVE)
    AMS_RULE_ACTION(accuracy, META_DATA)
    AMS_RULE_ACTION(append, NON_DIRUPTIVE)
    AMS_RULE_ACTION(auditlog, NON_DIRUPTIVE)
    AMS_RULE_ACTION(block, DIRUPTIVE)
    AMS_RULE_ACTION(capture, NON_DIRUPTIVE)
    AMS_RULE_ACTION(chain, FLOW)
    AMS_RULE_ACTION(ctl, NON_DIRUPTIVE)
    AMS_RULE_ACTION(deny, DIRUPTIVE)
    AMS_RULE_ACTION(deprecatevar, NON_DIRUPTIVE)
    AMS_RULE_ACTION(drop, DIRUPTIVE)
    AMS_RULE_ACTION(exec, NON_DIRUPTIVE)
    AMS_RULE_ACTION(expirevar, NON_DIRUPTIVE)
    AMS_RULE_ACTION(id, META_DATA)
    AMS_RULE_ACTION(initcol, NON_DIRUPTIVE)
    AMS_RULE_ACTION(log, NON_DIRUPTIVE)
    AMS_RULE_ACTION(logdata, NON_DIRUPTIVE)
    AMS_RULE_ACTION(msg, META_DATA)
    AMS_RULE_ACTION(multiMatch, NON_DIRUPTIVE)
    AMS_RULE_ACTION(noauditlog, NON_DIRUPTIVE)
    AMS_RULE_ACTION(nolog, NON_DIRUPTIVE)
    AMS_RULE_ACTION(pass, DIRUPTIVE)
    AMS_RULE_ACTION(pause, NON_DIRUPTIVE)
    AMS_RULE_ACTION(maturity, META_DATA)
    AMS_RULE_ACTION(phase, META_DATA)
    AMS_RULE_ACTION(prepend, NON_DIRUPTIVE)
    AMS_RULE_ACTION(proxy, DIRUPTIVE)
    AMS_RULE_ACTION(redirect, DIRUPTIVE)
    AMS_RULE_ACTION(rev, META_DATA)
    AMS_RULE_ACTION(sanitiseArg, NON_DIRUPTIVE)
    AMS_RULE_ACTION(sanitiseMatched, NON_DIRUPTIVE)
    AMS_RULE_ACTION(sanitiseRequestHeader, NON_DIRUPTIVE)
    AMS_RULE_ACTION(sanitiseResponseHeader, NON_DIRUPTIVE)
    AMS_RULE_ACTION(severity, META_DATA)
    AMS_RULE_ACTION(setuid, NON_DIRUPTIVE)
    AMS_RULE_ACTION(setsid, NON_DIRUPTIVE)
    AMS_RULE_ACTION(setenv, NON_DIRUPTIVE)
    AMS_RULE_ACTION(setvar, NON_DIRUPTIVE)
    AMS_RULE_ACTION(skip, FLOW)
    AMS_RULE_ACTION(skipAfter, FLOW)
    AMS_RULE_ACTION(status, DATA)
    AMS_RULE_ACTION(t, NON_DIRUPTIVE)
    AMS_RULE_ACTION(tag, META_DATA)
    AMS_RULE_ACTION(ver, META_DATA)
    AMS_RULE_ACTION(status, DATA)
    AMS_RULE_NULL_ACTION
};
