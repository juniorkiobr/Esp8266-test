const http = require('http');
const ws = require('ws');

const server = http.createServer();
const wss = new ws.WebSocketServer({ server });

server.listen(3000, () => {
  console.log('Server listening on port 3000');
});

wss.on('connection', function connection(ws) {
  ws.on('message', function message(data) {
    ws.send(""+data);
    console.log('received: %s', data);
    wss.clients.forEach(function each(client) {
      if (client.readyState === ws.OPEN) {
        client.send(""+data);
      }
    })
  });

  ws.send('something');
});
