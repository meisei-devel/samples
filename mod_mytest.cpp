#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "ap_config.h"
#include "http_log.h"
#include "util_script.h"
#include <string>

extern "C" {

#ifdef APLOG_USE_MODULE
APLOG_USE_MODULE(mytest);
#endif

};

/* The sample content handler */
static int mytest_handler(request_rec *r)
{
    if (strcmp(r->handler, "mytest")) {
        return DECLINED;
    }
//    r->content_type = "application/json; charset=utf-8";
    r->content_type = "text/plain; charset=utf-8";

	if (r->header_only){
		return OK;
	}

	struct timeval tv_fr,tv_to;
	double tm_fr,tm_to;
	gettimeofday(&tv_fr, NULL);

    ap_rputs("The sample page from mod_mytest.c\n", r);

	std::string s = std::string("てすとばる");

	ap_rprintf(r, "てすときー = [%s]\n", s.c_str());

	gettimeofday(&tv_to, NULL);

	tm_fr = (((double)tv_fr.tv_sec)*((double)1000000)+((double)tv_fr.tv_usec));
	tm_to = (((double)tv_to.tv_sec)*((double)1000000)+((double)tv_to.tv_usec));
 
	ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, "time: %lf MICROSEC (%lf MSEC)",tm_to - tm_fr,(tm_to - tm_fr) / 1000);

    return OK;
}

static void mytest_register_hooks(apr_pool_t *p)
{
    ap_hook_handler(mytest_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

extern "C" {

/* Dispatch list for API hooks */
module AP_MODULE_DECLARE_DATA mytest_module = {
    STANDARD20_MODULE_STUFF, 
    NULL,                  /* create per-dir    config structures */
    NULL,                  /* merge  per-dir    config structures */
    NULL,                  /* create per-server config structures */
    NULL,                  /* merge  per-server config structures */
    NULL,                  /* table of config file commands       */
    mytest_register_hooks  /* register hooks                      */
};

};
