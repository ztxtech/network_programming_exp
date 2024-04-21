# 清除缓存
rm -rf ./build
# 创建bulid目录
mkdir ./build
cd ./build
# 编译
cmake ../
make
# 运行测试
./FileIOTest