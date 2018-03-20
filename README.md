# gRPC stream cancelling with subprocessing and async on Windows

This is a small project which reproduces a problem within gRPC on Windows systems where connected streams will be closed down if you asyncronously call into an rpc which calls a subprocess, while calling another rpc call.

In this case, the combination of things that will close the streams (and where we noticed it first) is a C++ server and a JavaScript client (running through [grpcwebproxy](https://github.com/improbable-eng/grpc-web/tree/master/go/grpcwebproxy)). A C++ server with a Python client will also fail if the grpcio version is 1.4 or below, so a fix seems to be in place for later versions. A C++ server and C++ client doesn't seem to fail

Another combination like a Python server and JavaScript client will not fail.

Interestingly, the stream will NOT close if the output streams are not piped from the subprocess. This can be tested if you comment out the three lines in the `boost::process::child` call that handles piping input and output.

Also, running the two client calls syncronously instead of asyncronously will also keep the stream open.

# Installation
### C++ (Visual Studio)
```
mkdir build
cd build
cmake -Ax64 ..
```

Open GrpcStreamKiller.sln and build

### JavaScript/Node
```
cd src\jsclient
npm i
```

### Python 3
(Assumes Python is already in your PATH)
```
cd src\pyclient
python -m venv .venv
.\.venv\Scripts\python.exe -m pip install -r requirements.txt
```

# Running the program

For the remainder of the instructions, it is assumed that the enviornment variable PROJ_DIR points to the root of the project

### C++ (server) and Node (client)
Open a command terminal in the root directory of the project and run:
```
set PATH=%PATH%;%PROJ_DIR%\extlibs\lib 
.\build\src\server\Debug\server.exe
```

Open another terminal and run:
```
.\extlibs\bin\grpcwebproxy.exe --server_tls_cert_file=.\\extlibs\\bin\\grpcweb-localhost.crt --server_tls_key_file=./extlibs/bin/grpcweb-localhost.key --backend_addr=127.0.0.1:8004 --backend_tls_noverify --backend_tls=false --server_http_tls_port=8005 --server_http_debug_port=0 --server_tls_client_cert_verification=none --server_http_max_write_timeout=0 --server_http_max_read_timeout=0
```

And another terminal:
```
cd src\jsclient
node stream.js
```
Stream messages should now be coming through

Only one more terminal, i promise:
```
cd src\jsclient
node call.js
```

Run this last command a few times and you should see the stream closed with the message `INVOKE | STREAM END 14 transport is closing`
