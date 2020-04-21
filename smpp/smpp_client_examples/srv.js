var smpp = require('smpp');
var server = smpp.createServer(function(session) {
	session.on('bind_transmitter', function(pdu) {
		// we pause the session to prevent further incoming pdu events,
		// untill we authorize the session with some async operation.
		// session.pause();
		// checkAsyncUserPass(pdu.system_id, pdu.password, function(err) {
		// 	if (err) {
		// 		session.send(pdu.response({
		// 			command_status: smpp.ESME_RBINDFAIL
		// 		}));
		// 		session.close();
		// 		return;
		// 	}
			session.send(pdu.response());
	    	//	session.resume();
		});
       session.on('submit_sm', function(pdu) {
           session.send(pdu.response());
       });
});
server.listen(2775);
