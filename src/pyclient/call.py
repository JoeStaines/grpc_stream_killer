import grpc
import crashing_this_plane_pb2_grpc as crash_pb_grpc
import crashing_this_plane_pb2 as crash_pb

from concurrent.futures import ThreadPoolExecutor

if __name__ == "__main__":
    channel = grpc.insecure_channel('127.0.0.1:8004')
    stub = crash_pb_grpc.WithNoSurvivorsStub(channel)

    with ThreadPoolExecutor() as executor:
        future = executor.submit(lambda: stub.CallProcess(crash_pb.CallProcessRequest()))
        ret = stub.ReturnMe(crash_pb.ReturnMeRequest(text="testy"))
        print(ret.text)
        future.result()