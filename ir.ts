//% color=50 weight=19
//% icon="\uf1eb" block="Mbit_IR"
namespace Mbit_IR {
    /**
     * button pushed.
     */
    //% blockId=ir_received_left_event
    //% block="on |%btn| button pressed" shim=Mbit_IR::onPressEvent
    export function onPressEvent(btn: RemoteButton, body: Action): void {}
    /**
     * initialises local variablesssss
     */
    //% blockId=ir_init
    //% block="connect ir receiver to %pin" shim=Mbit_IR::init
    export function init(pin: Pins): void {}
}
