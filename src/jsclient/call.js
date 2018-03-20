process.env.NODE_TLS_REJECT_UNAUTHORIZED = "0";

var grpc = require('grpc-web-client').grpc;
var Pb = require('./crashing_this_plane_pb.js');
var Service = require('./crashing_this_plane_pb_service.js').WithNoSurvivors;

const ip = 'https://127.0.0.1';
const port = '8005';
const host = `${ip}:${port}`;

const callProcessReq = new Pb.CallProcessRequest();
const returnMeReq = new Pb.ReturnMeRequest();

grpc.unary(Service.CallProcess, {
    host,
    onEnd: ({status, statusMessage, message, headers}) => {
        console.log('CALL PROCESS END');
    },
    request: callProcessReq
});

grpc.unary(Service.ReturnMe, {
    host,
    onEnd: ({status, statusMessage, message, headers}) => {
        console.log('RETURN ME END');
    },
    request: returnMeReq
});