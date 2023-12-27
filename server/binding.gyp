{
    "targets":[
        {
            "target_name":"mantra",
            "sources":["mantra.cc"],
            'include_dirs': ["<!@(node -p \"require('node-addon-api').include\")"],
            'dependencies': ["<!(node -p \"require('node-addon-api').gyp\")"],
            'cflags!': [ '-fno-exceptions' ],
            'cflags_cc!': [ '-fno-exceptions' ],
            "libraries":["-liengine_ansi_iso","-lMFS100V9022"]
        }
    ]
}