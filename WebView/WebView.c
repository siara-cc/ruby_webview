#include "ruby.h"
#define WEBVIEW_IMPLEMENTATION
#include "webview.h"

char *callback_fn;
void my_cb(struct webview *w, const char *arg);
struct webview wv = {
  .title = "Title",
  .url = "data:text/html,%3C%21doctype%20html%3E%3Chtml%3EHello%20World%3C%2Fhtml%3E",
  .width = 800,
  .height = 600,
  .debug = 1,
  .resizable = 1,
  .external_invoke_cb = my_cb,
};

VALUE WebView = Qnil;

void Init_WebView();
VALUE method_webview(VALUE self, VALUE url, VALUE cb_fn);
VALUE method_webview_eval(VALUE self, VALUE scr);

void Init_WebView() {
  WebView = rb_define_module("WebView");
  rb_define_global_function("webview", method_webview, 2);
  rb_define_global_function("webview_eval", method_webview_eval, 1);
  //rb_define_method(MyTest, "test1", method_test1, 0);	
}

VALUE slf;
void my_cb(struct webview *w, const char *arg) {
  //printf("Hello: %s\n", arg);
  VALUE ret = rb_funcall(slf,
           rb_intern(callback_fn),
           1,
           rb_str_new2(arg));
  if (RB_TYPE_P(ret, T_STRING) == 1) {
    if (RSTRING_LEN(ret) > 0)
      webview_eval(&wv, RSTRING_PTR(ret));
  }
}

VALUE method_webview(VALUE self, VALUE url, VALUE cb_fn) {
  slf = self;
  wv.url = RSTRING_PTR(url);
  callback_fn = RSTRING_PTR(cb_fn);
  int blocking = 0;
  // Create webview window using the provided options
  webview_init(&wv);
  // Main app loop, can be either blocking or non-blocking
  while (webview_loop(&wv, blocking) == 0);
  // Destroy webview window, often exits the app
  webview_exit(&wv);
  // To change window title later:
  //webview_set_title(&wv, "New title");
  // To terminate the webview main loop:
  webview_terminate(&wv);
  // To print logs to stderr, MacOS Console or DebugView:
  webview_debug("exited: %d\n", 1);
  return Qnil;
}

VALUE method_webview_eval(VALUE self, VALUE scr) {
  webview_eval(&wv, RSTRING_PTR(scr));
  return Qnil;
}

