![V3S 核心板](https://github.com/rainbow-pi/rainbow-pi-sdk/raw/master/Docs/rainbow-pi-core.jpg)

![V3S 正面图](https://github.com/rainbow-pi/rainbow-pi-sdk/raw/master/Docs/rainbow-pi-frontview.png)

【全志V3S开发板 - 彩虹派简介】

	全志V3S开发板 - 彩虹派(Rainbow Pi)是一款模块化的系统，基于Allwinner V3S高性能ARM Cortex-A7 CPU，运行Linux系统，适合机器视觉 图像识别 物联网等

	我们提供软硬件设计资料和技术支持，帮助用户快速使用、上手、做项目

【软件】

	u-boot
	linux
	buildroot
		OpenCV
		FFMpeg
		等等.....
	
	H264硬件编解码 demo 程序

【联系方式】

	QQ群: 517453247 (开放的技术群，欢迎您的加入)

	淘宝: https://mvdevice.taobao.com

【编译SDK】

	1. 获取SDK源代码
	git clone https://github.com/rainbow-pi/rainbow-pi-sdk.git
	cd rainbow-pi-sdk
	
	2. 设置环境变量
	export RAINBOWPI_SDK_DIR=`pwd`/
	
	3. 编译buildroot
	cd ${RAINBOWPI_SDK_DIR}/buildroot
	./build-qt.sh 或者 ./build-baseline.sh
	
	编译过程比较长
	
	4. 编译u-boot, linux, 打包镜像文件
	cd ${RAINBOWPI_SDK_DIR}
	./build.sh all
	
	这个过程会自动下载 u-boot, linux并编译
	
	5. 最终镜像文件
	${RAINBOWPI_SDK_DIR}tools/pack/rainbow-pi.img

【安装烧写软件】

	Windows版
	
	文件位置
	${RAINBOWPI_SDK_DIR}tools/windows/PhoenixSuite_CN_V1.0.8.msi

	安装方式
	将上述安装文件拷贝到Windows安装

【烧写镜像文件】

	将 ${RAINBOWPI_SDK_DIR}tools/pack/rainbow-pi.img 拷贝到windows下烧写
	
	