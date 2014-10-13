#include "nginx_ams_rule_action.h"

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

