const MFS100 = require("./build/Release/mantra");
const EventEmitter = require("events").EventEmitter;

customEmitter = new EventEmitter();

customEmitter.on("start", () => {
  console.log("### START ...");
});
customEmitter.on("data", (evt) => {
  console.log(evt);
});

customEmitter.on("end", () => {
  console.log("### END ###");
});

console.log(MFS100.getDeviceInfo());

console.log(MFS100.callEmit(customEmitter.emit.bind(customEmitter)));
