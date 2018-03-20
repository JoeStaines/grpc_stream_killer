#ifndef GRPCXX_IMPL_CODEGEN_EXCEPTION_CALLBACK_H
#define GRPCXX_IMPL_CODEGEN_EXCEPTION_CALLBACK_H

#include <exception>

namespace grpc {

extern void (*unhandled_exception_callback)(std::exception_ptr eptr);

}

#endif // GRPCXX_IMPL_CODEGEN_EXCEPTION_CALLBACK_H