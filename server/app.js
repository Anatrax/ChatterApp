const WebSocket = require('ws');
const uuid = require('uuid');

// Get port number argument (Defaults to 8080)
const portNumber = process.argv[2] || 8080;

// Start websocket server on port number
const wss = new WebSocket.Server({port: portNumber});

const connectedUsers = {};
const unames = [];

// TODO: Make sure to exclude sender somehow
const broadcast = (data, ws) => {
  wss.clients.forEach((client) => {
    if (client.readyState === WebSocket.OPEN && client !== wss) {
      client.send(JSON.stringify(data));
    }
  });
};

wss.on('connection', (ws, request) => {
  ws.client_id = uuid.v4();

  // Send client an ID token
  ws.send(JSON.stringify({
    type: 'TOKEN',
    id: ws.client_id,
  }));

  ws.on('message', (message) => {
    const data = JSON.parse(message);
    switch (data.type) {
      case 'UN_REQ':
        console.log('Username request: ', data.uname);
        console.log(`Check if username "${data.uname}" is not in use.`);

        // Check if the username is already in use
        if ( unames.indexOf(data.name) > -1 ) {
          console.log(`Username "${data.uname}" is in use.
                        Send login failure message.`);
          // Send login failure message back to client
          ws.send(JSON.stringify({type: 'LOGIN_FAIL'}));
          break; // Exit out of switch statement
        }

        console.log(`Username "${data.uname}" is not in use.
        Add "${data.uname}" to connected users list.`);

        // Create a user object with requested username
        // var new_user = {uname: data.uname};
        // Add user object to connected users list, indexed by user's client ID
        connectedUsers[ws.client_id] = {uname: data.uname};

        // Send login success message back to client
        // along with a list of the connected users
        ws.send(JSON.stringify({
          type: 'LOGIN_SUCCESS',
          unames,
        }));

        // Add username to list
        unames.push(data.uname);

        // Let everyone know that a new user has connected
        broadcast({
          type: 'ADD_UN',
          uname: data.uname,
        }, ws);
        break;

      case 'ADD_MSG':
        // TODO: Make sure author matches username of ws.clientID
        // TODO: Instead of broadcast, should forward message
        broadcast({
          type: 'ADD_MSG',
          author: data.author,
          timestamp: data.timestamp,
          message: data.message,
        }, ws);
        break;

      default:
        break;
    }
  });

  ws.on('close', () => {
    console.log('Client dropped:', ws.client_id);

    // Remove client from connected users list
    delete connectedUsers[ws.client_id];
    // unames.splice(index, 1); // Remove client from username list

    // Let everyone know that the user has disconnected
    broadcast({
      type: 'USERS_LIST',
      connectedUsers,
    }, ws);
  });
});
