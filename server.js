const express = require('express');
const http = require('http');
const socketIo = require('socket.io');

const app = express();
const server = http.createServer(app);
const io = socketIo(server);
const PORT = 8000;

io.on('connection', (socket) => {

    socket.on('registerName', (clientName) => {
        socket.clientName = clientName;
        console.log(`User ${clientName} connected`);
    });

    socket.on('message', (data) => {
        console.log(`${socket.clientName}: ${data.msg}`);
        const message = `${socket.clientName}: ${data.msg}`;
        socket.broadcast.emit('message', message);
    });

    socket.on("disconnect", (reason) => {
        if (socket.clientName) {
            io.emit('message', `<SERVER : ${socket.clientName} disconnected>`);
            console.log(`User ${socket.clientName} disconnected: ${reason}`);
        } else {
            console.log(`User disconnected: ${reason}`);
        }
    });
});

server.listen(PORT, () => {
  console.log(`listening on : ${PORT}`);
});

