const Socket = require("socket.io");
module.exports = (io = Socket.Server) => {
  io.on("connection", () => {
    console.log("device client connected");
  });
};
