# Loads mkmf which is used to make makefiles for Ruby extensions
require 'mkmf'

$CFLAGS = '-DWEBVIEW_WINAPI=1'
$LDFLAGS = '-lole32 -lcomctl32 -loleaut32 -luuid -mwindows'

# Give it a name
extension_name = 'WebView'

# The destination
dir_config(extension_name)

# Do the work
create_makefile(extension_name)
