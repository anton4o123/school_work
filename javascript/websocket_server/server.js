var WebSocketServer = require('websocket').server;
var http = require('http');
console.log("ok");

var server = http.createServer(function(request, response) {
	console.log((new Date()) + ' Received request for ' + request.url);
	response.writeHead(404);
	response.end();
});
server.listen(80, function() {
	console.log((new Date()) + "Server is listening on port 80");
});

wsServer = new WebSocketServer({
	httpServer: server,
	autoAcceptConnections: false
});

wsServer.on('request', function(request) {
	var connection = request.accept('echo-protocol', request.origin);
	console.log((new Date()) + 'Connection accepted');

	connection.on('message', function(message) {
		if(message.type === 'utf8') {
			console.log('Received message: ' + message.utf8Data);
			connection.send(message.utf8Data);
		} else if(message.type === 'binary') {
			console.log('Received binary message of ' + message.binaryData.length + 'bytes');
			connection.sendBytes(message.binaryData);
		}
	});

	connection.on('close', function(reasonCode, description) {
		console.log((new Date()) + ' Peer ' + connection.remoteAddress + ' disconected.');
	});
});
