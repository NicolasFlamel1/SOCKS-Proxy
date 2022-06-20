# SOCKS Proxy

### Description
Nginx module that allows proxying request through a SOCKS proxy.

### Installing
Run the following commands to build and install this module.
```
wget "https://github.com/NicolasFlamel1/SOCKS-Proxy/archive/refs/heads/master.zip"
unzip "./master.zip"
wget "https://nginx.org/download/nginx-$(nginx -v 2>&1 | awk '{print $3}'  | awk -F'/' '{print $2}').tar.gz"
tar -xf "./nginx-$(nginx -v 2>&1 | awk '{print $3}'  | awk -F'/' '{print $2}').tar.gz"
cd "./nginx-$(nginx -v 2>&1 | awk '{print $3}'  | awk -F'/' '{print $2}')"
cp "./src/http/modules/ngx_http_proxy_module.c" "./src/http/ngx_http_upstream.c" "./src/http/ngx_http_upstream.h" "../SOCKS-Proxy-master/"
patch "../SOCKS-Proxy-master/ngx_http_proxy_module.c" < "../SOCKS-Proxy-master/ngx_http_proxy_module.c.diff"
patch "../SOCKS-Proxy-master/ngx_http_upstream.c" < "../SOCKS-Proxy-master/ngx_http_upstream.c.diff"
patch "../SOCKS-Proxy-master/ngx_http_upstream.h" < "../SOCKS-Proxy-master/ngx_http_upstream.h.diff"
echo $(nginx -V 2>&1 >/dev/null | grep -oP '(?<=^configure arguments: ).*?(?= --add-dynamic-module)') --add-dynamic-module="../SOCKS-Proxy-master" | xargs "./configure"
make modules
sudo mv "./objs/ngx_http_socks_proxy_module.so" "/usr/share/nginx/modules/"
```

Add the following line to the `top-level` context in your Nginx configuration file, `/etc/nginx/nginx.conf`, to enable this module.
```
load_module modules/ngx_http_socks_proxy_module.so;
```

### Usage
This module provides the following directives that can be used in a `location` context. This module also provides directives for all the [Nginx Proxy Module directives](http://nginx.org/en/docs/http/ngx_http_proxy_module.html) prefixed with `socks_`. For example, `socks_proxy_pass`, `socks_proxy_http_version`, etc. 
1. `socks_proxy_set_destination`: This directive accepts a parameter with the value of the destination's URL. 

For example, the following demonstrates how to setup a reverse proxy to make requests through a local Tor SOCKS proxy.
```
location ~ ^/tor/(https?)://?(.+/.*)$ {

	resolver 127.0.0.53;
	resolver_timeout 30s;
	
	socks_proxy_set_destination $1://$2;
	socks_proxy_pass http://localhost:9050$is_args$args;
}
```
