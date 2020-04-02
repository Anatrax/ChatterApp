const WebSocket = require('ws');
const uuid = require('uuid');

// Get port number argument (Defaults to 8080)
const port_number = process.argv[2] || 8080;

// Start websocket server on port number
const wss = new WebSocket.Server({ port: port_number });

var connected_users = {};

wss.on('connection', (ws, request) => {
  let index;
  ws.client_id = uuid.v4();
  ws.send(JSON.stringify({
    type: 'TOKEN',
    id: ws.client_id
  }));

  ws.on('message', (message) => {
    const data = JSON.parse(message);
    switch (data.type) {

      default:
        break;
    }
  })

  ws.on('close', () => {
    console.log('Client dropped:', ws.client_id);
    // Remove client from connected users list
  });

});