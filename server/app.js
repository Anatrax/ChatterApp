const WebSocket = require('ws');
const uuid = require('uuid');

// Get port number argument (Defaults to 8080)
const portNumber = process.argv[2] || 8080;

// Start websocket server on port number
const wss = new WebSocket.Server({port: portNumber});

const connectedUsers = {};

const broadcast = (data, ws) => {
  wss.clients.forEach((client) => {
    if (client.readyState === WebSocket.OPEN && client !== ws) {
      client.send(JSON.stringify(data));
    }
  });
};

const forward = (data, recipient) => {
  wss.clients.forEach((client) => {
    if (client.readyState === WebSocket.OPEN &&
    connectedUsers[client.client_id].uname === recipient) {
      client.send(JSON.stringify(data));
    }
  });
  // if (recipient.readyState === WebSocket.OPEN) {
  //   recipient.send(JSON.stringify(data));
  // }
};

wss.on('connection', (ws, request) => {
  // Send client an ID token on connect
  ws.client_id = uuid.v4();
  ws.send(JSON.stringify({
    type: 'TOKEN',
    id: ws.client_id,
  }));

  ws.on('message', (message) => {
    console.log('Server received: ', message);
    const data = JSON.parse(message);
    switch (data.type) {
      case 'UN_REQ':
        console.log(`Username requested: "${data.uname}"`);

        // Check if the username is already in use
        console.log(`Checking if username "${data.uname}" is not in use...`);
        for (const client in connectedUsers) {
          if (Object.prototype.hasOwnProperty.call(connectedUsers, client) &&
            (connectedUsers[client].uname === data.uname)) {
            console.log(`Username "${data.uname}" is in use.`);
            console.log(`Send login failure message.`);
            // Send login failure message back to client
            ws.send(JSON.stringify({type: 'LOGIN_FAIL'}));
            break;
          }
        }

        console.log(`Username "${data.uname}" is not in use!`);
        console.log(`Add "${data.uname}" to connected users list.`);

        // Send login success message back to client
        // along with a list of the connected users
        ws.send(JSON.stringify({
          type: 'LOGIN_SUCCESS',
          unames: Object.values(connectedUsers),
        }));

        // Add username to connected users list, indexed by user's client ID
        connectedUsers[ws.client_id] = {uname: data.uname};

        // Let everyone know that a new user has connected
        broadcast({
          type: 'ADD_UN',
          uname: data.uname,
        }, ws);
        break;

      case 'ADD_MSG':
        // Make sure the sender's name isn't spoofed
        if (data.author !== connectedUsers[ws.client_id].uname) break;
        // Check if reciever exists
        console.log(`Checking if recipient "${data.uname}" exists...`);
        for (const client in connectedUsers) {
          if (Object.prototype.hasOwnProperty.call(connectedUsers, client) &&
            (connectedUsers[client].uname === data.recipient)) {
            console.log(`Recipient "${data.recipient}" exists!`);
            console.log(`Sending message to "${data.recipient}"...`);
            // Forward message to specified recipient
            forward(data, data.recipient);
            break;
          }
        }
        break;

      default:
        break;
    }
  });

  ws.on('close', () => {
    console.log('Client dropped:', ws.client_id);

    // Let everyone know that the user has disconnected
    broadcast({
      type: 'DEL_UN',
      uname: connectedUsers[ws.client_id].uname,
    }, ws);

    // Remove client from connected users list
    delete connectedUsers[ws.client_id];
  });
});
