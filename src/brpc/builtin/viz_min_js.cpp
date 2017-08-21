// Baidu RPC - A framework to host and access services throughout Baidu.
// Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved

// Author: The baidu-rpc authors (pbrpc@baidu.com)
// Date: 2014/10/30 15:57:02

#include <pthread.h>
#include "base/logging.h"
#include "brpc/policy/gzip_compress.h"
#include "brpc/builtin/viz_min_js.h"


namespace brpc {

static pthread_once_t s_viz_min_buf_once = PTHREAD_ONCE_INIT; 
static base::IOBuf* s_viz_min_buf = NULL;
static void InitVizMinBuf() {
    s_viz_min_buf = new base::IOBuf;
    s_viz_min_buf->append(viz_min_js());
}
const base::IOBuf& viz_min_js_iobuf() {
    pthread_once(&s_viz_min_buf_once, InitVizMinBuf);
    return *s_viz_min_buf;
}

// viz.js is huge. We separate the creation of gzip version from uncompress
// version so that at most time we only keep gzip version in memory.
static pthread_once_t s_viz_min_buf_gzip_once = PTHREAD_ONCE_INIT; 
static base::IOBuf* s_viz_min_buf_gzip = NULL;
static void InitVizMinBufGzip() {
    base::IOBuf viz_min;
    viz_min.append(viz_min_js());
    s_viz_min_buf_gzip = new base::IOBuf;
    CHECK(policy::GzipCompress(viz_min, s_viz_min_buf_gzip, NULL));
}
const base::IOBuf& viz_min_js_iobuf_gzip() {
    pthread_once(&s_viz_min_buf_gzip_once, InitVizMinBufGzip);
    return *s_viz_min_buf_gzip;
}

const char* viz_min_js() {
return "function Ub(nr){throw nr}var cc=void 0,wc=!0,xc=null,ee=!1;function bk(){return(function(){})}"



}

} // namespace brpc
