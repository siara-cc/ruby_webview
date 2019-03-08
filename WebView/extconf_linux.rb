# Loads mkmf which is used to make makefiles for Ruby extensions
require 'mkmf'

$CFLAGS = '-DWEBVIEW_COCOA=1 -DWEBVIEW_STATIC=1'
$LDFLAGS = '-framework WebKit'

# Give it a name
extension_name = 'WebView'

# The destination
dir_config(extension_name)

# Do the work
create_makefile(extension_name)
