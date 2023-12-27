const MFS100 = require("../build/Release/mantra");
const EventEmitter = require("events").EventEmitter;
let fingerScannerEmitter = new EventEmitter();

const Socket = require("socket.io");

module.exports = (io = Socket.Server, webSocket) => {
  io.on("connection", (socket) => {
    console.log("device client connected");

    //Handle socket events inside this

    socket.on("start_identification", () => {
      console.log("RECEIVED ON  DEVICE SOCKET");
      fingerScannerEmitter.on("finger_identification", (evt) => {
        console.log(evt);
        webSocket.emit("identification_progress", evt);
      });

      let fingerMatchResult = MFS100.identifySpecial(
        fingerScannerEmitter.emit.bind(fingerScannerEmitter)
      );
      console.log(fingerMatchResult);
    });
  });
};
