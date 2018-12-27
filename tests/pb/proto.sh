#!/usr/bin/env bash
protoc -I ./protos --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ./protos/*.proto
protoc -I ./protos --cpp_out=. ./protos/*.proto