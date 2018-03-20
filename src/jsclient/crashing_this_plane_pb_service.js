// package: 
// file: crashing_this_plane.proto

var jspb = require("google-protobuf");
var crashing_this_plane_pb = require("./crashing_this_plane_pb");
var WithNoSurvivors = {
  serviceName: "WithNoSurvivors"
};
WithNoSurvivors.Streamer = {
  methodName: "Streamer",
  service: WithNoSurvivors,
  requestStream: false,
  responseStream: true,
  requestType: crashing_this_plane_pb.StreamerRequest,
  responseType: crashing_this_plane_pb.StreamerResponse
};
WithNoSurvivors.CallProcess = {
  methodName: "CallProcess",
  service: WithNoSurvivors,
  requestStream: false,
  responseStream: false,
  requestType: crashing_this_plane_pb.CallProcessRequest,
  responseType: crashing_this_plane_pb.CallProcessResponse
};
WithNoSurvivors.ReturnMe = {
  methodName: "ReturnMe",
  service: WithNoSurvivors,
  requestStream: false,
  responseStream: false,
  requestType: crashing_this_plane_pb.ReturnMeRequest,
  responseType: crashing_this_plane_pb.ReturnMeResponse
};
module.exports = {
  WithNoSurvivors: WithNoSurvivors,
};

