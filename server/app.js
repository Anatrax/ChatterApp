const WebSocket = require('ws');
const uuid = require('uuid');

// Get port number argument (Defaults to 8080)
const portNumber = process.argv[2] || 8080;

// Start websocket server on port number
const wss = new WebSocket.Server({port: portNumber});

const connectedUsers = {};
const unames = [];
const uname_strings = [];

const broadcast = (data, ws) => {
  wss.clients.forEach((client) => {
    if (client.readyState === WebSocket.OPEN && client !== ws) {
      client.send(JSON.stringify(data));
    }
  });
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
        if ( uname_strings.includes(data.uname) ) {
          console.log(`Username "${data.uname}" is in use.
          Send login failure message.`);
          // Send login failure message back to client
          ws.send(JSON.stringify({type: 'LOGIN_FAIL'}));
          break;
        }

        console.log(`Username "${data.uname}" is not in use!`);
        console.log(`Add "${data.uname}" to connected users list.`);

        // Add username to connected users list, indexed by user's client ID
        connectedUsers[ws.client_id] = data.uname;

        // Send login success message back to client
        // along with a list of the connected users
        ws.send(JSON.stringify({
          type: 'LOGIN_SUCCESS',
          unames,
        }));

        // Add username to list
        unames.push({uname: data.uname});
        uname_strings.push(data.uname);

        // Let everyone know that a new user has connected
        broadcast({
          type: 'ADD_UN',
          uname: data.uname,
        }, ws);
        break;

      case 'ADD_MSG':
        if (data.author === connectedUsers[ws.client_id]) {
          // TODO: Instead of broadcast, should forward message
          broadcast({
            type: 'ADD_MSG',
            author: data.author,
            timestamp: data.timestamp,
            message: data.message,
          }, ws);
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
      uname: connectedUsers[ws.client_id],
    }, ws);

    // Remove client from username list
    let index = uname_strings.indexOf(connectedUsers[ws.client_id]);
    if (index > -1) {
      uname_strings.splice(index, 1);
    }

    // Remove client from users list
    index = unames.indexOf({uname: connectedUsers[ws.client_id]});
    if (index > -1) {
      unames.splice(index, 1);
    }

    // Remove client from connected users list
    delete connectedUsers[ws.client_id];
  });
});
