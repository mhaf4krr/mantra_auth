const MFS100 = require("./build/Release/mantra");
const EventEmitter = require("events").EventEmitter;

fingerScannerEmitter = new EventEmitter();

fingerScannerEmitter.on("start", () => {
  console.log("### START ...");
});

fingerScannerEmitter.on("end", () => {
  console.log("### END ###");
});

console.log(MFS100.getDeviceInfo());

console.log(
  MFS100.identifySpecial(fingerScannerEmitter.emit.bind(fingerScannerEmitter))
);
