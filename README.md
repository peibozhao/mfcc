# librosa_mfcc
* librosa MFCC特征提取的C++实现
* 仅实现了demo/main.cpp的函数和对应参数
* librosa版本0.8.0

## DEMO:
### 编译:
```
mkdir build
cd build
cmake -DMFCC_BUILD_DEMO=ON ..
make
```
### 执行:
```
./demo FILE
```
* 输出:
    * audio.txt: 音频的采样点数据
    * mfcc.txt: 特征数据
