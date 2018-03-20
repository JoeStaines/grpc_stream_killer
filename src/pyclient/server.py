import grpc
import crashing_this_plane_pb2_grpc as crash_pb_grpc
import crashing_this_plane_pb2 as crash_pb

from concurrent.futures import ThreadPoolExecutor
from subprocess import Popen, PIPE, STDOUT
import time

class Servicer(crash_pb_grpc.WithNoSurvivorsServicer):
    def CallProcess(self, request, context):
        p = Popen(["C:\\Windows\\System32\\help.exe"], stdout=PIPE, stderr=STDOUT)
        output = p.communicate()
        print(output)
        return crash_pb.CallProcessResponse()

    def Streamer(self, request, context):
        for i in range(1000):
            yield crash_pb.StreamerResponse()
            time.sleep(1)

    def ReturnMe(self, request, context):
        res = crash_pb.ReturnMeResponse()
        res.text = request.text
        return res

if __name__ == "__main__":
    server = grpc.server(ThreadPoolExecutor(max_workers=10))
    crash_pb_grpc.add_WithNoSurvivorsServicer_to_server(Servicer(), server)
    server.add_insecure_port('[::]:8004')
    server.start()
    while True:
        time.sleep(10)