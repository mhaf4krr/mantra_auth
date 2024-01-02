const MFS100 = require("../build/Release/mantra");
const EventEmitter = require("events").EventEmitter;
let fingerScannerEmitter = new EventEmitter();
let bindedFn = fingerScannerEmitter.emit.bind(fingerScannerEmitter);

//set max event listener

let lodash = require("lodash");

const Socket = require("socket.io");

module.exports = (io = Socket.Server) => {
  io.on("connection", (socket) => {
    console.log("device client connected");

    //Handle socket events inside this

    socket.on("start_identification", () => {
      console.log("RECEIVED ON  DEVICE SOCKET");
      fingerScannerEmitter.once("finger_identification", (evt) => {
        console.log(evt);
      });

      let counter = 0;

      let prev = null;

      fingerScannerEmitter.once("finger_scan_quality", (evt) => {
        //console.log("INTERFACE QUALITY:", evt);

        let { quality } = evt;

        //debounced dfunction
        //console.log("Involing Fn");

        if (prev === null) {
          prev = Date.now();
        } else {
          let current = Date.now();

          if (current - prev > 1000) {
            socket.emit("finger_scan_quality_progress", quality);

            prev = current;
          }
        }
      });

      fingerScannerEmitter.once("fingerprint_image", (imageArrayBuffer) => {
        let imageData =
          "data:image/bmp;base64," +
          Buffer.from(imageArrayBuffer).toString("base64");
        prev = null;

        socket.emit("fingerprint_image_client", imageData);
      });

      let fingerMatchResult = MFS100.identifySpecial(bindedFn);

      socket.emit("fingerprint_result_client", fingerMatchResult);
    });
  });
};
