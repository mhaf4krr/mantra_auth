cmd_Makefile := cd ..; /usr/local/lib/node_modules/node-gyp/gyp/gyp_main.py -fmake --ignore-environment "-Dlibrary=shared_library" "-Dvisibility=default" "-Dnode_root_dir=/root/.cache/node-gyp/20.10.0" "-Dnode_gyp_dir=/usr/local/lib/node_modules/node-gyp" "-Dnode_lib_file=/root/.cache/node-gyp/20.10.0/<(target_arch)/node.lib" "-Dmodule_root_dir=/app" "-Dnode_engine=v8" "--depth=." "-Goutput_dir=." "--generator-output=build" -I/app/build/config.gypi -I/usr/local/lib/node_modules/node-gyp/addon.gypi -I/root/.cache/node-gyp/20.10.0/include/node/common.gypi "--toplevel-dir=." binding.gyp
