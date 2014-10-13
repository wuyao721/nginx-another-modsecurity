
#include <ngx_http.h>
#include "ngx_ams_cmd.h"
//#include <ngx_pool_context.h>

typedef struct {
    //ngx_flag_t                  enable;
    //directory_config            *config;
    ngx_array_t                 rules;

    ngx_str_t                   *file;
    ngx_uint_t                   line;
} ngx_http_ams_loc_conf_t;

static ngx_int_t ngx_http_ams_handler(ngx_http_request_t *r);
static ngx_int_t ngx_http_ams_preconfiguration(ngx_conf_t *cf);
static ngx_int_t ngx_http_ams_init(ngx_conf_t *cf);
static ngx_int_t ngx_http_ams_init_process(ngx_cycle_t *cycle);
static void *ngx_http_ams_create_loc_conf(ngx_conf_t *cf);
static char *ngx_http_ams_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child);
static char *ngx_http_ams_secrule(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);

static void ngx_http_ams_terminate(ngx_cycle_t *cycle);
static void ngx_http_ams_cleanup(void *data);

/* command handled by the module */
static ngx_command_t  ngx_http_ams_commands[] =  {
  { ngx_string("SecRule"),
    NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE3,
    ngx_http_ams_secrule,
    NGX_HTTP_LOC_CONF_OFFSET,
    0,
    NULL },
  ngx_null_command
};

/*
** handlers for configuration phases of the module
*/

static ngx_http_module_t ngx_http_ams_ctx = {
    ngx_http_ams_preconfiguration, /* preconfiguration */
    ngx_http_ams_init, /* postconfiguration */

    NULL, /* create main configuration */
    NULL, /* init main configuration */

    NULL, /* create server configuration */
    NULL, /* merge server configuration */

    ngx_http_ams_create_loc_conf, /* create location configuration */
    ngx_http_ams_merge_loc_conf /* merge location configuration */
};


ngx_module_t ngx_http_ams = {
    NGX_MODULE_V1,
    &ngx_http_ams_ctx, /* module context */
    ngx_http_ams_commands, /* module directives */
    NGX_HTTP_MODULE, /* module type */
    NULL, /* init master */
    NULL, /* init module */
    ngx_http_ams_init_process, /* init process */
    NULL, /* init thread */
    NULL, /* exit thread */
    ngx_http_ams_terminate, /* exit process */
    ngx_http_ams_terminate, /* exit master */
    NGX_MODULE_V1_PADDING
};

static ngx_inline ngx_int_t
ngx_http_ams_status(ngx_http_request_t *r, int status)
{
    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0, "Ams: status %d", status);

    if (status == DECLINED || status == APR_SUCCESS) {
        return NGX_DECLINED;
    }

    /* nginx known status */
    if ( (status >= 300 && status < 308)       /* 3XX */
            || (status >= 400 && status < 417) /* 4XX */
            || (status >= 500 && status < 508) /* 5XX */
            || (status == NGX_HTTP_CREATED || status == NGX_HTTP_NO_CONTENT) ) {

        return status;
    }

    return NGX_HTTP_INTERNAL_SERVER_ERROR;
}


/* create loc conf struct */
static void *
ngx_http_ams_create_loc_conf(ngx_conf_t *cf)
{
    ngx_http_ams_loc_conf_t  *conf;

    conf = (ngx_http_ams_loc_conf_t  *)
           ngx_palloc(cf->pool, sizeof(ngx_http_ams_loc_conf_t));
    if (conf == NULL)
        return NULL;

    if( NGX_OK != ngx_array_init(&conf->rules, ncf->pool, 16, sizeof(ams_rule_t)) ){
        return NULL;
    }

    //conf->config = NGX_CONF_UNSET_PTR;
    //conf->enable = NGX_CONF_UNSET;

    return conf;
}

/* merge loc conf */
static char *
ngx_http_ams_merge_loc_conf(ngx_conf_t *cf, void *parent,
                                    void *child)
{
//    ngx_http_ams_loc_conf_t  *prev = parent;
//    ngx_http_ams_loc_conf_t  *conf = child;
//
//    ngx_conf_merge_value(conf->enable, prev->enable, 0);
//    ngx_conf_merge_ptr_value(conf->config, prev->config, NULL);
//
//    if (conf->enable && conf->config == NULL) {
//        ngx_log_error(NGX_LOG_EMERG, cf->log, 0,
//                      "\"AmsEnabled\" in %V:%ui is set to \"on\""
//                      " while directive \"AmsConfig\" is not found"
//                      " in the same location",
//                      conf->file, conf->line);
//        return NGX_CONF_ERROR;
//    }

    return NGX_CONF_OK;
}

static void
modsecLog(void *obj, int level, char *str)
{
    if (obj != NULL) {
        level = (level & APLOG_LEVELMASK) + NGX_LOG_EMERG - APLOG_EMERG;
        if (level > NGX_LOG_DEBUG) {
            level = NGX_LOG_DEBUG;
        }
        ngx_log_error((ngx_uint_t)level, (ngx_log_t *)obj, 0, "%s", str);
    }
}

static ngx_int_t
ngx_http_ams_preconfiguration(ngx_conf_t *cf)
{
    /*  XXX: temporary hack, nginx uses pcre as well and hijacks these two */
    //pcre_malloc = modsec_pcre_malloc;
    //pcre_free = modsec_pcre_free;
    //
    //modsecSetLogHook(cf->log, modsecLog);
    //modsecSetDropAction(ngx_http_ams_drop_action);
    //
    ///* TODO: server_rec per server conf */
    //modsec_server = modsecInit();
    //if (modsec_server == NULL) {
    //    return NGX_ERROR;
    //}
    //
    ///* set host name */
    //modsec_server->server_hostname = ngx_palloc(cf->pool, ngx_cycle->hostname.len + 1);
    //if (modsec_server->server_hostname == NULL) {
    //    return NGX_ERROR;
    //}
    //ngx_memcpy(modsec_server->server_hostname, ngx_cycle->hostname.data, ngx_cycle->hostname.len);
    //modsec_server->server_hostname[ ngx_cycle->hostname.len] = '\0';
    //
    //modsecStartConfig();
    return NGX_OK;
}


static void
ngx_http_ams_terminate(ngx_cycle_t *cycle)
{
}


static ngx_int_t
ngx_http_ams_init(ngx_conf_t *cf)
{
    ngx_http_handler_pt *h;
    ngx_http_core_main_conf_t *cmcf;

    //modsecFinalizeConfig();

    cmcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_core_module);

    h = ngx_array_push(&cmcf->phases[NGX_HTTP_PREACCESS_PHASE].handlers);
    if (h == NULL) {
        return NGX_ERROR;
    }
    *h = ngx_http_ams_handler;

    return NGX_OK;
}


static ngx_int_t
ngx_http_ams_init_process(ngx_cycle_t *cycle)
{
    return NGX_OK;
}


/*
** [ENTRY POINT] does : this function called by nginx from the request handler
*/
static ngx_int_t
ngx_http_ams_handler(ngx_http_request_t *r)
{
    return NGX_DECLINED;
#if 0
    ngx_http_ams_loc_conf_t *cf;
    ngx_http_ams_ctx_t      *ctx;
    ngx_int_t                        rc;

    cf = ngx_http_get_module_loc_conf(r, ngx_http_ams);

    /* Process only main request */
    if (r != r->main || !cf->enable) {
        return NGX_DECLINED;
    }

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0, "ams: handler");

    /* create / retrive request ctx */
    if (r->internal) {
        
        ctx = ngx_http_get_module_pool_ctx(r, ngx_http_ams);

        if (ctx) {
            /* we have already processed the request headers */
            ngx_http_set_ctx(r, ctx, ngx_http_ams);
            return NGX_DECLINED;
        }

        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0, "ams: request pool ctx empty");
    }

    ctx = ngx_http_ams_create_ctx(r);
    if (ctx == NULL) {

        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    ngx_http_set_ctx(r, ctx, ngx_http_ams);

    if (ngx_http_set_pool_ctx(r, ctx, ngx_http_ams) != NGX_OK) {
        return NGX_ERROR;
    }

    /* load request to request rec */
    if (ngx_http_ams_load_request(r) != NGX_OK
        || ngx_http_ams_load_headers_in(r) != NGX_OK) {

        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    /* processing request headers */
    rc = ngx_http_ams_status(r, modsecProcessRequestHeaders(ctx->req));

    if (rc != NGX_DECLINED) {
        return rc;
    }

    if (modsecContextState(ctx->req) == MODSEC_DISABLED) {
        return NGX_DECLINED;
    }

    if (r->method == NGX_HTTP_POST 
            && modsecIsRequestBodyAccessEnabled(ctx->req) ) {

        /* read POST request body, should we process PUT? */
        rc = ngx_http_read_client_request_body(r, ngx_http_ams_body_handler);
        if (rc >= NGX_HTTP_SPECIAL_RESPONSE) {
            return rc;
        }

        return NGX_DONE;
    }
    
    /* other method */
    return ngx_http_ams_status(r, modsecProcessRequestBody(ctx->req));
#endif
}

