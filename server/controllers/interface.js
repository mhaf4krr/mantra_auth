const MFS100 = require("../build/Release/mantra");
const EventEmitter = require("events").EventEmitter;
let fingerScannerEmitter = new EventEmitter();

const Socket = require("socket.io");

module.exports = (io = Socket.Server) => {
  io.on("connection", (socket) => {
    console.log("device client connected");

    //Handle socket events inside this

    socket.on("start_identification", () => {
      console.log("RECEIVED ON  DEVICE SOCKET");
      fingerScannerEmitter.on("finger_identification", (evt) => {
        console.log(evt);
      });

      fingerScannerEmitter.on("finger_scan_quality", (evt) => {
        console.log("INTERFACE QUALITY:", evt);

        let { quality } = evt;

        console.log("MAIN BLOCKED");

        socket.emit("finger_scan_quality_progress", quality);

        console.log("MAIN BLOCKED");
      });

      fingerScannerEmitter.on("fingerprint_image", (imageArrayBuffer) => {
        let imageData =
          "data:image/bmp;base64," +
          Buffer.from(imageArrayBuffer).toString("base64");
        socket.emit("fingerprint_image_client", imageData);
      });

      let fingerMatchResult = MFS100.identifySpecial(
        fingerScannerEmitter.emit.bind(fingerScannerEmitter)
      );
      console.log(fingerMatchResult);
    });
  });
};
