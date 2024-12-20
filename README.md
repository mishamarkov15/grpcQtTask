# Quick start

Чтобы запустить проект выполните следующие команды
```shell
mkdir -p build
pushd build
cmake ..
cmake --build . -j4
```
Эта последовательность команд сгенерирует следующие файлы в папке `build/`:
1. `gRPCTestTaskClient` - исполняемый файл с GUI для клиента. (Тут отображается таблица с доступными ip для connect по grpc).
2. `gRPCTestTaskServer` - исполняемый файл с GUI для сервера. Тут можно вводить порт, который будет высылаться клиентам по broadcast UDP.
3. `server_grpc` - исполняемый сервер, который принимает grpc ping запросы, в ответ отдает pong. По умолчанию запускается на порту `50051`. ЧТобы запустить на другом порту: `./server_grpc -port=50052`
4. `api.grpc.pb.cc`, `api.grpc.pb.h`, `api.pb.cc`, `api.pb.h` - сгенерированные protobuf файлы с помощью cmake.

# Troubleshooting

Очень вероятно, что у Вас будет ругаться на `absl::` при компиляции. Чтобы устранить проблему следуйте инструкциям тут: https://grpc.io/docs/languages/cpp/quickstart/. 