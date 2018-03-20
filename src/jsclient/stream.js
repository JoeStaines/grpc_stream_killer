process.env.NODE_TLS_REJECT_UNAUTHORIZED = "0";

var grpc = require('grpc-web-client').grpc;
var Pb = require('./crashing_this_plane_pb.js');
var Service = require('./crashing_this_plane_pb_service.js').WithNoSurvivors;

const ip = 'https://127.0.0.1';
const port = '8005';
const host = `${ip}:${port}`;

const streamReq = new Pb.StreamerRequest();

grpc.invoke(Service.Streamer, {
    host,
    onEnd: (code, message) => {
    console.log('INVOKE | STREAM END', code, message);
  },
  onHeaders: (header) => {
      console.log('INVOKE | GOT HEADER');
  },
  onMessage : (res) => {
      console.log('INVOKE | GOT MESSAGE');
  },
  request: streamReq
});