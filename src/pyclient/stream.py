import grpc
import crashing_this_plane_pb2_grpc as crash_pb_grpc
import crashing_this_plane_pb2 as crash_pb

if __name__ == "__main__":
    channel = grpc.insecure_channel('127.0.0.1:8004')
    stub = crash_pb_grpc.WithNoSurvivorsStub(channel)

    pb = crash_pb.StreamerRequest()
    stream = stub.Streamer(pb)
    for val in stream:
        print("got stream")