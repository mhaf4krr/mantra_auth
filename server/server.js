//setup up web socket connection to interact with UI
// two functions needed

// const MFS100 = require("./build/Release/mantra");
// console.log(MFS100.getDeviceInfo());

const { Server } = require("socket.io");

const express = require("express");
const app = express();

let PORT = 3010;

if (process.env.ENV_CURRENT === "DEV") {
  PORT = 3010;
}

const expressServer = app.listen(PORT, () => {
  console.log("LISTENING ON " + PORT);
});

const io = new Server(expressServer, {
  cors: "*",
});

const WEB_INTERFACE = require("./controllers/interface")(io.of("/interface"));
const DEVICE = require("./controllers/device")(io.of("/device"));
