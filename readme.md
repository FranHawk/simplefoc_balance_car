![在这里插入图片描述](https://img-blog.csdnimg.cn/2553918bd69d43549042c8ce2c0facfc.jpeg)


# 前言
本科毕业于自动化，期间学习了各种电机运动控制原理，自动控制原理，但是只会考试而未究其理。最近接触到simplefoc这个基于arduino的开源无刷电机驱动库，想正好借此机会将本科学到的内容用于实际，于是就有了这个小项目，**基于无刷电机FOC的平衡小车**。
无刷电机相比于普通小车用的有刷电机，相同体积下扭矩更大，无刷电机驱动小车时可以直驱而不像有刷电机需要带减速器才能满足扭矩要求，且响应速度更快。采用无刷电机可以把小车做的更紧凑美观。
无刷电机的驱动电路和算法要更加复杂，无刷电机在低速工作时，算法层面上采用磁场定向控制算法FOC(Field-oriented control),可以精确控制电机的位置，速度乃至电流也就是转矩，由此可以做出很多好玩的东西。基于foc的无刷电机在机器人关节，相机云台电机控制等领域得到广泛应用。
# 主要功能
 - 板载双路无刷电机驱动及电流环芯片，每路最大电流2.5A，可驱动两个云台无刷电机，可控制到电流
 - 小车可自平衡，可通过手机app蓝牙连接控制进退，转向
 - 搭载双排RGB，每排共24个灯，可以扩展成更多，实现多种灯光特效且不影响车辆控制
 - 图传接口，通过外接ESP-CAM模块实现WIFI图传，可在手机上查看(20220421 插口画反用不了。。)
# 开源资料链接
博客文档链接
[https://blog.csdn.net/weixin_42487906/article/details/124898392](https://blog.csdn.net/weixin_42487906/article/details/124898392)

视频链接
[https://www.bilibili.com/video/BV1Sv4y137FG/](https://www.bilibili.com/video/BV1Sv4y137FG/)

github仓库，内有代码，3D打印文件，pcb制板文件：
[https://github.com/FranHawk/simplefoc_balance_car](https://github.com/FranHawk/simplefoc_balance_car)

立创eda工程 可在线查看原理图和pcb：
总共有三个板子
**主板(包括电机控制和驱动部分)**：[https://oshwhub.com/FranHawk/balance_car_esp32_simplefoc](https://oshwhub.com/FranHawk/balance_car_esp32_simplefoc)
**编码器板**：[https://oshwhub.com/FranHawk/as5600-16mm](https://oshwhub.com/FranHawk/as5600-16mm)
**RGB灯带板**：[https://oshwhub.com/FranHawk/rgb_strip](https://oshwhub.com/FranHawk/rgb_strip)
# 材料购买链接
所有的电子元件材料都可以对照BOM表或者工程里的原理图买，在淘宝或者立创上买均可，下面列出一些关键材料的链接

**AS5600 L6234PD INA240A1**：【淘宝】[https://m.tb.cn/h.ft947n2?tk=gn3u2P8IocI](https://m.tb.cn/h.ft947n2?tk=gn3u2P8IocI)「L6234PD L6234D L6234   HSOP 原装汽车IC 进口芯片热卖 质量超好」点击链接直接打开
电机部分的芯片 这个店家买到的货还算便宜
**其他的电子元器件**都可以在优信电子之类的找到，财力充足的可以直接立创，省事。
**2210云台电机（至少两个）**【淘宝】[https://m.tb.cn/h.fslSDE8?tk=G8Pk2P8HluO](https://m.tb.cn/h.fslSDE8?tk=G8Pk2P8HluO)「清仓HJ2210-75T无刷云台电机狗3云台专用 航拍电机 云台空心轴马」点击链接直接打开
**轮胎胎皮（至少两个）** 【淘宝】[https://m.tb.cn/h.ft9UFV4?tk=L8Ez2P8u1Ma](https://m.tb.cn/h.ft9UFV4?tk=L8Ez2P8u1Ma)「AXIAL 1比24车SCX24 90081小米吉姆尼通用橡胶攀爬轮胎皮直径52mm」点击链接直接打开
**电机支架（至少两个）** 【淘宝】[https://m.tb.cn/h.fsl86Kp?tk=i9Oo2P8FvxY](https://m.tb.cn/h.fsl86Kp?tk=i9Oo2P8FvxY)「390电机支架 385固定座 365安装底座 380马达固定架 送螺丝螺母 点击链接直接打开
**黑色亚克力板（至少两个）** 【淘宝】[https://m.tb.cn/h.fH9ybkd?tk=2OCV2P8vqAf](https://m.tb.cn/h.fH9ybkd?tk=2OCV2P8vqAf)「平衡小车DIY专用亚克力支架板扩展板」点击链接直接打开
**电池 900mah**【淘宝】[https://m.tb.cn/h.fGk2f0O?tk=33dF2PjbvTN](https://m.tb.cn/h.fGk2f0O?tk=33dF2PjbvTN)「航模电池5200mAh 11.1V足容高C7.4V车模船模 RC攀爬车质量保证」点击链接直接打开

**其他机械小零件**
 - sh1.0 mm的线，3P和4P的，**注意接线前一定要检查编码器板和主板的线顺序是不是对应的**直接买来的线是不能用的，需要自己焊一下改下顺序
 - m2.5的螺钉，至少8mm长，和m2.5的垫圈若干，用于固定编码器，电机与电机支架
 - m3 6mm长的螺钉，m3*5 6mm的铜柱，m3*20 6mm铜柱，m3螺母若干
 - AB胶或者同等强度的胶，用于将径向磁铁固定在电机轴线处
 - 绑带和魔术贴，用于固定主板和电池
 - 3.81mm插头，用于把电机线插到主板上，XT30公头接口，用于把主板连接电池，红黑电源线

# 制作步骤

## 1.电路部分
打开开源资料链接上的三个pcb工程，在嘉立创投板生产，把元器件都买到并焊上去
**主板**

![在这里插入图片描述](https://img-blog.csdnimg.cn/c1b63f5c3a5b486290ae9b9f2087a68b.png)
![在这里插入图片描述](https://img-blog.csdnimg.cn/3d51a3e105144783af2bc4dc3ce16640.png)
按照上图用红黑电源线焊接主板和XT30 公头插头

**编码器板**
![在这里插入图片描述](https://img-blog.csdnimg.cn/0c33da9c10694f9d81cf286af02ec82f.png)
编码器板没什么元器件，记得上面这个焊点要焊上，背面还有一个as5600芯片，总共要做两个
**RGB灯板**
![在这里插入图片描述](https://img-blog.csdnimg.cn/6070c22f78344c05914980c473964031.png)
把灯焊上去，没什么好说的，总共要做两个

**sh1.0 3P和4P的线**
分别做两条，用作连接RGB板和编码器板到主板，注意接线前一定要检查编码器板和主板的线顺序是不是对应的，我买到的反的，需要自己调换顺序

## 机械部分
制作两个电机部分
![在这里插入图片描述](https://img-blog.csdnimg.cn/1390a6c9559c43379d012e12835a7ac0.png)
先把径向磁铁粘在电机轴心
![在这里插入图片描述](https://img-blog.csdnimg.cn/776e5286dccd468a91849d3779c45e68.png)
把编码器板，电机支架和电机用m2.5螺钉按上图组装，中间加些垫片，防止相互间摩擦，如下图
![在这里插入图片描述](https://img-blog.csdnimg.cn/e152da44d1ec49599ccc305d1e1f34af.png)
3D打印轮毂，套在电机上，再套上胎皮，3D打印文件在github里
![在这里插入图片描述](https://img-blog.csdnimg.cn/5995e8291c984c08ac2c83cf8d778fd6.png)
## 组装
3D打印固定板，用魔术贴和扎带固定电池，用m3*5 铜柱和螺钉将3D打印固定板和主板组装
![在这里插入图片描述](https://img-blog.csdnimg.cn/c9fa85f59cc14ea497615953c75e4164.png)
![在这里插入图片描述](https://img-blog.csdnimg.cn/c8cc640e855e4ac3878b140ef145eed7.png)
将两个电机部分和主板部分用m3螺钉组装，电机线通过3.8mm 插头连接到主板，顺序随意。编码器板用sh1.0 mm 4P线连接，第一层亚克力板上装四个m3 20mm的铜柱，如下图
![在这里插入图片描述](https://img-blog.csdnimg.cn/382ce7778fa34447a7e6f7f551719a3b.png)
RGB灯板和第二层亚克力板粘在一起
![在这里插入图片描述](https://img-blog.csdnimg.cn/c6df3164039646af98ad22b271d40358.png)
连接RGB的线到主板，固定第一层和第二层亚克力板，完成组装
![在这里插入图片描述](https://img-blog.csdnimg.cn/0a8d61c3cb60432b9569f19d989af017.png)
## 烧写程序
通过vscode+platformio来烧写程序
第一次烧写程序前，先找到hw_bldc.cpp里的hw_bldc_init()函数里
有这样几句

```c
    motor_0.init();
    motor_1.init();
    
    motor_0.initFOC();
    motor_1.initFOC();
```
第一次烧写时，initFOC里不需要有参数，上电后simplefoc会运行自检程序，检测电机旋转方向和电角度，会在串口中输出，通过串口得到参数后填入initFOC

```c
	motor_0.init();
    motor_1.init();
    
    motor_0.initFOC(4.53, Direction::CW);
    motor_1.initFOC(0.64, Direction::CCW);
```
如上，每个人的这两个参数都是不一样的，然后第二次烧写代码。之后每次启动就不会消耗时间自检了。

## 手机控制
手机安装点灯APP，[https://diandeng.tech/dev](https://diandeng.tech/dev)
创建一个蓝牙设备，添加一个手柄控件，起名叫JoyKey
![在这里插入图片描述](https://img-blog.csdnimg.cn/114f8d1e5e1246d0b0ec0cb04a831fae.png)
![在这里插入图片描述](https://img-blog.csdnimg.cn/25a1ba34c1d84180a47d8b0d7eaa468b.png)
对于灯光效果的遥控可自行开发





# 硬件分析与概要设计
电路部分分为一个主板，两个编码器小板，两个RGB灯板
- 其中主板部分集成了无刷电机驱动，控制部分，MPU6050传感器，供电，串口和各种接口
- 驱动器板搭载AS5600磁编码器，通过IIC与主板通信
- 主板为RGB提供5V电源与控制信号
电机采用2210无刷云台电机，7对极
## 无刷电机驱动部分
驱动是小车的核心部分，是小车动起来的关键。无刷电机转动时需要分别控制电机的三相电压。采用FOC算法控制时，还需要位置传感器提供转子和定子的相对位置，如果要控制转矩，还需要电流传感器。初次学习FOC，我采用灯哥开源FOC驱动的方案，[灯哥github仓库地址](https://github.com/ToanTech/Deng-s-foc-controller)。
电机驱动采用L6234P三相H桥集成驱动芯片
![在这里插入图片描述](https://img-blog.csdnimg.cn/aa3bf61f177d4e66ba02504d87992ed8.png)
电流检测采用INA240A2芯片，放大增益为50，这个芯片也比较贵，可以用INA240A1代替，放大增益为20，我焊的时候用的就是这个，一样能用。
![在这里插入图片描述](https://img-blog.csdnimg.cn/059c7093859847729a65d2689aed91f7.png)
电机位置检测采用AS5600绝对值磁编码器芯片，IIC通讯，我为这个芯片画了个小板子附在电机轴处，与主板相连，同时还需要在电机轴线处固定一个径向磁铁。
![在这里插入图片描述](https://img-blog.csdnimg.cn/c9c6319b5b3f48b6b4f9b2ea9a7626ea.png)
![在这里插入图片描述](https://img-blog.csdnimg.cn/c55a46f9e6894498a386a35bacb9a910.png)

## 控制部分
由主要功能可知，需要MCU具有蓝牙和WIFI功能，还需要足够的性能用于FOC算法，同时控制RGB。最近看到的esp32可以说正合适，esp32有320K RAM，4M ROM，两个core，一个核专门用来跑foc算法，另外一个核用来跑其他程序包括RGB控制，simplefoc官网上说esp32单次foc运算能有1ms，引脚也足够多，满足平衡控制的需求。
![在这里插入图片描述](https://img-blog.csdnimg.cn/b79d9330c37c435da4602634e42aa553.png)
## 传感部分
平衡控制需要通过传感器检测到小车自身的姿态，我采用最常见的MPU6050 6轴加速度计陀螺仪芯片
![在这里插入图片描述](https://img-blog.csdnimg.cn/1d0987cd02ee4baea8537b2cb1abd857.png)
WIFI图传由主板通过2.54排母插接ESP-CAM模块实现
![在这里插入图片描述](https://img-blog.csdnimg.cn/664e2794b9c8465aa86ee419c0fd9102.png)
## 电源部分
- 电池选用3S 900mah航模电池，提供12V电压给电机
- TPS5430开关芯片将12V转5V，供给到RGB和ESP-CAM模块
- AMS1117将5V降到3.3V
 ![在这里插入图片描述](https://img-blog.csdnimg.cn/cbd1f5b6b458463fb5c9a55fc2bfce11.png)
 ![在这里插入图片描述](https://img-blog.csdnimg.cn/5069d076f74d4f7f96f87633691cd444.png)
## RGB部分
RGB采用WS1802B LED灯，MCU一个IO口就可以驱动一串RGB
![在这里插入图片描述](https://img-blog.csdnimg.cn/c4a366b2f0364de2a2aa8b501fd26ede.png)
![在这里插入图片描述](https://img-blog.csdnimg.cn/bda9584955c54e389939b6d9b367b194.png)

## 其他
其他一些接口和转串口芯片什么就不多介绍了，可以看我开源的电路工程了解

# 理论基础
无刷电机平衡小车的理论部分需要了解

1.无刷电机磁场定向控制FOC算法
2.平衡车建模和控制算法

理论部分网上有很多资料，讲解也非常清楚易懂，珠玉在前，我引出一些比较好的文章，供想要深究的读者查看
## 磁场定向控制FOC算法
FOC算法的内容比较多，初学者可以看下稚晖君这篇文章，比较通俗易懂
- [深入浅出讲解FOC算法与SVPWM技术](https://zhuanlan.zhihu.com/p/147659820)

simplefoc官方文档的介绍也比较详细，还有源码讲解，代码中也用到了simplefoc的库，所以最好去官网文档了解一些simplefoc的使用方法
[https://simplefoc.com/](https://simplefoc.com/)

其他比较好的文章
 - [BLDC电机控制算法——FOC简述](https://blog.csdn.net/qq_26285867/article/details/82079450)
 - [foc学习笔记1——准备工作](https://blog.csdn.net/jdhfusk/article/details/120395938?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522163505936616780271558836%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=163505936616780271558836&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~baidu_landing_v2~default-4-120395938.first_rank_v2_pc_rank_v29&utm_term=foc%E5%AD%A6%E4%B9%A0%E7%AC%94%E8%AE%B0&spm=1018.2226.3001.4187)
 ## 平衡车建模和控制算法
 - 平衡车建模部分首推 清华卓晴的平衡车参考方案 对平衡车的数学模型的建立有非常清晰的介绍，需要熟悉平衡车模型的可以多看几遍
- 平衡车平衡环和速度环pid的整定可以看这篇文章
 [平衡小车PID，就该这么调！！！](https://blog.csdn.net/best_xiaolong/article/details/105153978?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_utm_term~default-4.essearch_pc_relevant&spm=1001.2101.3001.4242.3)

# 软件部分
ESP32这款MCU有两个核心，我采用freertos来对两个核进行调度，整体软件框架基于arduino+freertos


## 用到的库
[Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel) 用于驱动RGB灯带
[blinker-library](https://github.com/blinker-iot/blinker-library)点灯科技的蓝牙库，可以通过手机app和平衡车蓝牙通讯
[MPU6050_light](https://github.com/rfetick/MPU6050_light)MPU6050驱动库
[Arduino-FOC](https://github.com/simplefoc/Arduino-FOC)simplefoc的arduino支持库


**0 core：**
task 0：simplefoc的电流环的运算、俯仰角数据读取的和电机电压的输出
**1 core：**
task 1：平衡环和速度环pid运算
task 2：RGB闪烁和通过蓝牙接收手机的控制命令

## TASK 0
这个任务的代码比较简单，loopFOC和move负责simplefoc电流环的运算和电压输出
mpu.update()读出MPU6050数据并返回俯仰角，俯仰角通过互补滤波结算得到就可以了
shaftVelocity返回电机速度，用于task 1速度环pid的运算

```c
void task_motor_move(void *pvParameters)
{
    while (1)
    {
        // iterative setting FOC phase voltage
        motor_1.loopFOC();
        motor_0.loopFOC();
        // Serial.printf("d:%f,%f\n",motor_1.shaftVelocity(),motor_0.shaftVelocity());
        motor_1.move(motor_output_left);
        motor_0.move(motor_output_right);

        // // iterative function setting the outter loop target
        mpu.update();

        speed_right = motor_0.shaftVelocity();
        speed_left = motor_1.shaftVelocity();
    }
}
```
## TASK 1
该任务主要是平衡环和速度环pid运算，用状态机的思维将平衡车状态分为STOP，RUNNING，PICKUP三个状态，这样做主要是为了避免平衡车被拿起时电机疯转。
开机时状态为STOP，把车扶正到平衡位置附近则进入RUNNING状态，当拿起倾斜角后过大，则进入PICKUP状态，逆时针旋转车体后进入STOP状态。
RUNNING状态运行平衡环，速度环和角度环。平衡环采用pd，速度环用pi，角度环仅用单p。

```c
void task_control(void *pvParameters)
{
    while (1)
    {
        angle_pitch = mpu.getAngleY();
        // Serial.printf("d:%f\n",angle_pitch);
        acc_Z = mpu.getAccZ();
        if (running_state == STATE_STOP)
        {
            if (abs(angle_pitch - angle_pitch_offset) < 0.5)
            {
                running_state = STATE_RUNNING;
            }
        }
        else if (running_state == STATE_RUNNING)
        {
            speed_average = (speed_right + speed_left) / 2;
            if (abs(angle_pitch - angle_pitch_offset) > 50 )
            {
                speed_I_sum=0;//清空积分系数
                running_state = STATE_PICKUP;
            }
            else
            {
                speed_target = translate_speed;

                speed_error = speed_target - speed_average;

                speed_I_sum+=(speed_error*speed_I);
                if(speed_I_sum>15){
                    speed_I_sum = 15;
                }
                if(speed_I_sum<-15){ 
                    speed_I_sum = -15;
                }
                angle_target_pitch = speed_P * speed_error + speed_I_sum;
  
                motor_output_left = angle_P * ((angle_pitch - angle_pitch_offset) - angle_target_pitch) + angle_D * mpu.getGyroY()+rotate_speed; //+ angle_D * mpu.getGyroY()
                motor_output_right = angle_P * ((angle_pitch - angle_pitch_offset) - angle_target_pitch) + angle_D * mpu.getGyroY()-rotate_speed;
                angle_last_pitch = angle_pitch;
            }
        }
        else if (running_state == STATE_PICKUP)
        {
            motor_output_left = 0;
            motor_output_right = 0;
            if (speed_right > 3.14 && speed_left < -3.14)
            {
                running_state = STATE_STOP;
            }
        }
        vTaskDelay(1);
    }
}
```

## TASK 2
task 2用于RGB效果显示，和接收手机blinker app通过蓝牙发送的数据。一般的RGB等效都有一个延时函数，普通的延时函数都是在原地死等，这样大大降低CPU效率，影响其他程序运行，这里我编写了一系列非阻塞式RGB灯效：在显示完灯效后不再原地延时，而是直接进行调度，切换到其他task。详细可看我代码。

```c
void task_neopixel(void *pvParameters)
{
    uint32_t neopixel_pattern_previous = 0;
    uint32_t neopixel_pattern_interval = 500;
    uint32_t neopixel_pattern_number = 0;
    while (1)
    {
        // 效果切换
        if((neopixel_count-neopixel_pattern_previous)>neopixel_pattern_interval){
            neopixel_pattern_previous = neopixel_count;
            neopixel_pattern_number++;
            neopixel_state_clear(strip_1_handler);
            neopixel_state_clear(strip_2_handler);
            if(neopixel_pattern_number>4){
                neopixel_pattern_number = 0;
            }
        }

        switch(neopixel_pattern_number){
            case 0:
                neopixel_police_style_2(strip_2_handler,10,5);
                neopixel_police_style_2(strip_1_handler,10,5);
                break;
            case 1:
                neopixel_police_style_1(strip_2_handler,10,5);
                neopixel_police_style_1(strip_1_handler,10,5);
                break;
            case 2:
                neopixel_loop(strip_2_handler, 255, 255, 255, 4, 4);
                neopixel_rainbow(strip_1_handler);
                break;
            case 3:
                neopixel_bounce(strip_1_handler, 0, 255, 0, 2, 3, 0);
                neopixel_fade_in_out(strip_2_handler, 255, 0, 255, 2, 1,25);
                break;
            case 4:
                neopixel_spread_out(strip_2_handler, strip_2_handler.strip.Color(0,255,0), strip_2_handler.strip.Color(0,0,255), 4, 10);
                neopixel_spread_out(strip_1_handler, strip_1_handler.strip.Color(255,0,0), strip_1_handler.strip.Color(255,255,0), 4, 10);
                break;
            default:
                break;
        }
        neopixel_count++;

#ifdef USE_BLINKER
        Blinker.run();
#endif

        vTaskDelay(10);
    }
}
```
