#include "pxt.h"
#include <map>
#include <vector>
#include "ReceiverIR.h"
using namespace pxt;
typedef vector<Action> vA;

enum class Pins
{
  //% blockId="pinP0" block="P0"
  P0 = 3,
  //% blockId="pinP1" block="P1"
  P1 = 2,
  //% blockId="pinP2" block="P2"
  P2 = 1,
  //% blockId="pinP3" block="P3"
  P3 = 4,
  //% blockId="pinP4" block="P4"
  P4 = 5,
  //% blockId="pinP5" block="P5"
  P5 = 17,
  //% blockId="pinP6" block="P6"
  P6 = 12,
  //% blockId="pinP7" block="P7"
  P7 = 11,
  //% blockId="pinP8" block="P8"
  P8 = 18,
  //% blockId="pinP9" block="P9"
  P9 = 10,
  //% blockId="pinP10" block="P10"
  P10 = 6,
  //% blockId="pinP11" block="P11"
  P11 = 26,
  //% blockId="pinP12" block="P12"
  P12 = 20,
  //% blockId="pinP13" block="P13"
  P13 = 23,
  //% blockId="pinP14" block="P14"
  P14 = 22,
  //% blockId="pinP15" block="P15"
  P15 = 21,
  //% blockId="pinP16" block="P16"
  P16 = 16,
  //% blockId="pinP17" block="P17"
  P19 = 0,
  //% blockId="pinP18" block="P18"
  P20 = 30
};

enum class RemoteButton
{
  //% blockId="btnPower" block="POWER"
  Power = 0x0,
  //% blockId="btnUp" block="UP"
  Up = 0x1,
  //% blockId="btnLeft" block="LEFT"
  Left = 0x4,
  //% blockId="btnRight" block="RIGHT"
  Right = 0x6,
  //% blockId="btnDown" block="DWON"
  Down = 0x9,
  //% blockId="btnLight" block="LIGHT"
  Light = 0x2,
  //% blockId="btnBeep" block="BEEP"
  BEEP = 0x5,
  //% blockId="btnPlus" block="PLUS"
  Plus = 0xc,
  //% blockId="btnMinus" block="MINUS"
  Minus = 0xe,
  //% blockId="btnTLeft" block="TLEFT"
  TLeft = 0x8,
  //% blockId="btnTRight" block="TRIGHT"
  TRight = 0xA,
  //% blockId="btnNum0" block="0"
  NUM0 = 0xD,
  //% blockId="btnNum1" block="1"
  NUM1 = 0x10,
  //% blockId="btnNum2" block="2"
  NUM2 = 0x11,
  //% blockId="btnNum3" block="3"
  NUM3 = 0x12,
  //% blockId="btnNum4" block="4"
  NUM4 = 0x14,
  //% blockId="btnNum5" block="5"
  NUM5 = 0x15,
  //% blockId="btnNum6" block="6"
  NUM6 = 0x16,
  //% blockId="btnNum7" block="7"
  NUM7 = 0x18,
  //% blockId="btnNum8" block="8"
  NUM8 = 0x19,
  //% blockId="btnNum9" block="9"
  NUM9 = 0x1A
};

//% color=50 weight=19
//% icon="\uf1eb"
namespace Mbit_IR
{
map<RemoteButton, vA> actions;
map<RemoteButton, uint32_t> lastact;
Timer tsb;
uint8_t buf[32];
uint32_t now;
ReceiverIR *rx;
RemoteIR::Format fmt = RemoteIR::UNKNOWN;

/**
  * button pushed.
  */
//% blockId=ir_received_left_event
//% block="on |%btn| button pressed"
void onPressEvent(RemoteButton btn, Action body)
{
  //if(actions.find(btn) == actions.end()) actions[btn] = new vector();
  actions[btn].push_back(body);
}

void cA(vA runner)
{
  for (int i = 0; i < runner.size(); i++)
  {
    runAction0(runner[i]);
  }
}

void onReceivable()
{
  int x = rx->getData(&fmt, buf, 32 * 8);
  if (actions.find((RemoteButton)buf[2]) == actions.end())
    return;
  now = tsb.read_ms();
  if (now - lastact[(RemoteButton)buf[2]] < 100)
    return;
  lastact[(RemoteButton)buf[2]] = now;
  cA(actions[(RemoteButton)buf[2]]);
}

void monitorIR()
{
  while (1)
  {
    while (rx->getState() != ReceiverIR::Received)
    {
      uBit.sleep(50);
    }
    onReceivable();
  }
}

/**
  * initialises local variablesssss
  */
//% blockId=ir_init
//% block="connect ir receiver to %pin"
void init(Pins pin)
{
  rx = new ReceiverIR((PinName)pin);
  tsb.start(); //interrupt timer for debounce
  create_fiber(monitorIR);
}
} // namespace Mbit_IR