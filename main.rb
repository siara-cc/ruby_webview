require_relative 'WebView/WebView'

include WebView

def RubyFunction(arg)
   webview_eval("document.write('<div id=d1>First script run from PHP</div>')");
   puts "In Ruby " + arg
   return "document.body.innerHTML += 'Second script run from Ruby';"
   #return ""
end

webview("file://" + Dir.pwd + "/index.html", "RubyFunction")

