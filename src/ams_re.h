
#include "pcre.h"

ams_regex_t *ams_re_compile(ngx_str_t *pattern);
int ams_re_match(ams_regex_t *regex, ngx_str_t *s);
//int ams_re_match(ngx_str_t *pattern, ngx_str_t *s);


