cmd_Release/mantra.node := ln -f "Release/obj.target/mantra.node" "Release/mantra.node" 2>/dev/null || (rm -rf "Release/mantra.node" && cp -af "Release/obj.target/mantra.node" "Release/mantra.node")
