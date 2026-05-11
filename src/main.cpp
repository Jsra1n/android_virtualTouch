/*
                          _ooOoo_
                         o8888888o
                         88" . "88
                         (| -_- |)
                         O\  =  /O
                      ____/`---'\____
                    .'  \\|     |//  `.
                   /  \\|||  :  |||//  \
                  /  _||||| -:- |||||-  \
                  |   | \\\  -  /// |   |
                  | \_|  ''\---/''  |   |
                  \  .-\__  `-`  ___/-. /
                ___`. .'  /--.--\  `. . __
             ."" '<  `.___\_<|>_/___.'  >'"".
            | | :  `- \`.;`\ _ /`;.`/ - ` : | |
            \  \ `-.   \_ __\ /__ _/   .-` /  /
       ======`-.____`-.___\_____/___.-`____.-'======
                          `=---='
       ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
                佛祖保佑                  永无BUG
                佛祖镇楼                  BUG辟易
           佛曰:
                   写字楼里写字间，写字间里程序员；
                   程序人员写程序，又拿程序换酒钱。
                   酒醒只在网上坐，酒醉还来网下眠；
                   酒醉酒醒日复日，网上网下年复年。
                   但愿老死电脑间，不愿鞠躬老板前；
                   奔驰宝马贵者趣，公交自行程序员。
                   别人笑我忒疯癫，我笑自己命太贱；
                   不见满街漂亮妹，哪个归得程序员？
                         ！！BUG退散！！
 */
// #include <iostream>
// #include <unistd.h>
// #include "tools.h"

// void monitorTest(int slot,Vector2 data,int type)
// {
//     std::cout<<"slot: "<<slot<<"  "<<"xy: "<<data.x<<"  "<<data.y<<"  "<<"type: "<<type<<std::endl;
// }

// int main()
// {
//     touch touchTest;
//     touchTest.touchDown(110, {100, 200});
//     sleep(2);
//     touchTest.touchMove(110, {200, 300});
//     sleep(2);
//     touchTest.touchUp(110);
//     touchTest.monitorEvent(monitorTest);
//     sleep(15);
//     return 0;
// }



#include <iostream>
#include <string>
#include <vector>
#include <random> // 引入随机数库
#include <chrono>
#include "tools.h"

int main(int argc, char* argv[]) {
    touch touchInstance;

    if (argc < 2) {
        std::cout << "使用方法:" << std::endl;
        std::cout << "  点击: ./touch tap x y" << std::endl;
        std::cout << "  滑动: ./touch swipe x1 y1 x2 y2 duration_ms" << std::endl;
        return 0;
    }

    std::string cmd = argv[1];

    // 初始化随机数生成器
    std::random_device rd;
    std::mt19937 gen(rd());
    // 定义 45 到 60 之间的均匀分布
    std::uniform_int_distribution<> dis(45, 60);

    if (cmd == "tap" && argc == 4) {
        float x = std::stof(argv[2]);
        float y = std::stof(argv[3]);
        
        // 生成随机时长
        int random_sleep = dis(gen);

        touchInstance.touchDown(0, {x, y});
        
        // usleep 的参数是微秒 (1毫秒 = 1000微秒)
        usleep(random_sleep * 1000); 
        
        touchInstance.touchUp(0);
        
        std::cout << "已执行点击: (" << x << ", " << y << ") 时长: " << random_sleep << "ms" << std::endl;

    } else if (cmd == "swipe" && argc == 7) {
        float x1 = std::stof(argv[2]), y1 = std::stof(argv[3]);
        float x2 = std::stof(argv[4]), y2 = std::stof(argv[5]);
        int duration = std::stoi(argv[6]);

        touchInstance.touchDown(0, {x1, y1});
        for (int i = 0; i <= 20; i++) {
            float currX = x1 + (x2 - x1) * i / 20.0;
            float currY = y1 + (y2 - y1) * i / 20.0;
            touchInstance.touchMove(0, {currX, currY});
            usleep(duration * 1000 / 20); 
        }
        touchInstance.touchUp(0);
        std::cout << "已执行滑动" << std::endl;
    }

    return 0;
}
