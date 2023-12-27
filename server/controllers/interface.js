const Socket = require("socket.io");
module.exports = (io = Socket.Server) => {
  io.on("connection", (socket) => {
    console.log("interface client connected");
    socket.on("start_identification", () => {
      //Call Matra Device for Fingerprint scanning
      console.log("INTERFACE REQUESTED TO START");
    });
  });
};
