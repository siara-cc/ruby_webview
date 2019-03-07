# Loads mkmf which is used to make makefiles for Ruby extensions
require 'mkmf'

$CFLAGS = '-DWEBVIEW_GTK=1 `pkg-config --cflags gtk+-3.0 webkit2gtk-4.0`'
$LDFLAGS = '`pkg-config --libs gtk+-3.0 webkit2gtk-4.0`'

# Give it a name
extension_name = 'WebView'

# The destination
dir_config(extension_name)

# Do the work
create_makefile(extension_name)
