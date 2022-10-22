// Header guard
#ifndef NGX_HTTP_PROXY_MODULE_H
#define NGX_HTTP_PROXY_MODULE_H


// Check if SOCKS proxy is defined
#ifdef SOCKS_PROXY

	// Definitions
		
	// SOCKS proxy module
	#define ngx_http_proxy_module ngx_http_socks_proxy_module
	
	// Module
	extern ngx_module_t ngx_http_proxy_module;
#endif


// Structures

typedef struct {
    ngx_str_t                      key_start;
    ngx_str_t                      schema;
    ngx_str_t                      host_header;
    ngx_str_t                      port;
    ngx_str_t                      uri;

	// Check if SOCKS proxy is defined
	#ifdef SOCKS_PROXY
	
		// Destination host
		ngx_str_t destinationHost;
		
		// Destination port
		u_short destinationPort;
		
		// Destination URI
		ngx_str_t destinationUri;
	#endif

} ngx_http_proxy_vars_t;

typedef struct {
    ngx_http_status_t              status;
    ngx_http_chunked_t             chunked;
    ngx_http_proxy_vars_t          vars;
    off_t                          internal_body_length;

    ngx_chain_t                   *free;
    ngx_chain_t                   *busy;

    unsigned                       head:1;
    unsigned                       internal_chunked:1;
    unsigned                       header_sent:1;
} ngx_http_proxy_ctx_t;


#endif
