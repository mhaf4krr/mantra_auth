import { BACKEND } from "../../CONSTANTS";

import { Socket, io } from "socket.io-client";

// "undefined" means the URL will be computed from the `window.location` object
export const socket: Socket = io(`${BACKEND}`,{
    autoConnect:true,
    transports:["websocket"]
});
