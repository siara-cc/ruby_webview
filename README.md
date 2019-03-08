# Cross Platform WebView extension for Ruby lovers

This WebView extension for Ruby is built upon [WebView for C and Go](https://github.com/zserge/webview) written by Serge Zaitsev.

# Why WebView for Ruby

The Ruby Programming language is a general purpose programming language, developed by Yukihiro Matsumoto (Matz) in the mid-90's. Ruby is a powerful, flexible language with an excellent web framework in Rails.

Ruby has a considerable deployment base and developer base, so it makes sense to make it available on the Front-end to build rich and responsive desktop applications.

# How it works

This repository makes WebView available as a Ruby extension.  There are two functions provided by the extension: `webview()` and `webview_eval()`.

Giving below is the Ruby code of `main.rb` which makes the API self-explanatory:

```ruby
require_relative 'WebView/WebView'

include WebView

def RubyFunction(arg)
   webview_eval("document.write('<div id=d1>First script run from Ruby</div>')"
);
   puts "In Ruby: " + arg
   return "document.body.innerHTML += 'Second script run from Ruby';"
   #return ""
end

webview("file://" + Dir.pwd + "/index.html", "RubyFunction")
```

`RubyFunction()` is passed as second parameter to `webview()` function, which opens the URL specified in the first parameter. Whenever the script (JS) in the HTML page (index.html) calls `window.external.invoke(arg)`, the Ruby callback function (`RubyFunction()`) is invoked with the argument.

The callback function can choose to call `webview_eval()` as shown above.  Whatever string returned by this function is run as script.  If empty string is returned, it is not evaluated.

The callback function acts as a bridge between Javascript and Ruby and may be called using JSON string as argument and may indicate the context of call (such as onload, onclick etc.) and corresponding data for the request or callback.

# Usage

The procedure to build the extension differs from OS to OS.

## Mac OS

Ensure Ruby is installed, clone this repository and run following commands:

```sh
cd ruby_webview/WebView
ruby extconf_osx.rb
make
cd ..
ruby main.rb
```

## Windows

Install Ruby stable version with DevKit (MSys2). On command prompt, add path to MSys2 executable folders by running `MSys\AutoRebase.bat`.  Then clone this repository and run:

```bat
cd ruby_webview/WebView
ruby extconf_win.rb
make
cd ..
ruby main.rb
```

## Linux

The procedure to build on Linux is almost same as of MacOS.  Before running following scripts, ensure `pkg-config`, `gtk+-3.0` and `webkit2gtk-4.0` are installed using `apt`. After cloning this repository, run:

```sh
cd ruby_webview/WebView
ruby extconf_linux.rb
make
cd ..
ruby main.rb
```

# Screenshot

![](ss_ruby_1.png?raw=true) ![](ss_ruby_2.png?raw=true)
