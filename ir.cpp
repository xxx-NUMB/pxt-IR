#include "pxt.h"
#include <map>
#include <vector>
#include "ReceiverIR.h"
using namespace pxt;
typedef vector<Action> vA;

enum class Pins{
  P0=  3,
  P1=  2,
  P2=  1,
  P3=  4,
  P4=  5,
  P5=  17,
  P6=  12,
  P7=  11,
  P8=  18,
  P9=  10,
  P10= 6,
  P11= 26,
  P12= 20,
  P13= 23,
  P14= 22,
  P15= 21,
  P16= 16,
  P19= 0,
  P20= 30
};

enum class RemoteButton {
    //% block="num0" 
    num0 = 0x19,
    //% block="num1" 
	  num1 = 0x45,
    //% block="num2" 
	  num2 = 0x46,
    //% block="num3" 
	  num3 = 0x47,
    //% block="num4" 
	  num4 = 0x44,
    //% block="num5" 
	  num5 = 0x40,
    //% block="num6" 
	  num6 = 0x43,
    //% block="num7" 
	  num7 = 0x7,
    //% block="num8" 
	  num8 = 0x15,
    //% block="num9" 
	  num9 = 0x9,
    //% block="redR" 
	  redR = 0xd,
    //% block="redL" 
	  redL = 0x16,
    //% block="up" 
	  up = 0x18,
    //% block="left" 
	  left = 0x8,
    //% block="ok" 
	  ok = 0x1c,
    //% block="right" 
	  right = 0x5a,
    //% block="down" 
	  down = 0x52,

};

//% color=50 weight=19 block="Mbit_IR"
//% icon="\uf1eb"
namespace Mbit_IR { 
  map<RemoteButton, vA> actions;
  map<RemoteButton, uint32_t> lastact;
  Timer tsb; 
  uint8_t buf[32];
  uint32_t now;
  ReceiverIR *rx;
  RemoteIR::Format fmt = RemoteIR::UNKNOWN;

  /**
  * 判断遥控器的按键是否按下
  */
  //% block="on |%btn| button pressed"
  void onPressEvent(RemoteButton btn, Action body) {
    //if(actions.find(btn) == actions.end()) actions[btn] = new vector();
    actions[btn].push_back(body);
  }

  void cA(vA runner){for(int i=0;i<runner.size();i++){runAction0(runner[i]);} }

  void onReceivable(){
    int x = rx->getData(&fmt, buf, 32 * 8);
    if(actions.find((RemoteButton)buf[2]) == actions.end()) return;
    now = tsb.read_ms();
    if(now - lastact[(RemoteButton)buf[2]] < 100) return;
    lastact[(RemoteButton)buf[2]] = now;
    cA(actions[(RemoteButton)buf[2]]); 
  }

  void monitorIR(){
    while(1){
      while(rx->getState() != ReceiverIR::Received){ 
        uBit.sleep(50);
      }
      onReceivable();
    }
  }

  /**
  * 选择红外接收头连接的引脚
  */
  //% block="connect ir receiver to %pin"
  void init(Pins pin){
    rx = new ReceiverIR((PinName)pin);
    tsb.start(); //interrupt timer for debounce
    create_fiber(monitorIR);
  }
}
