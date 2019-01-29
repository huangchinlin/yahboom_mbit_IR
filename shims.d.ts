// Auto-generated. Do not edit.



    //% color=50 weight=19
    //% icon="\uf1eb" block="Mbit_IR"
declare namespace Mbit_IR {

    /**
     * button pushed.
     */
    //% blockId=ir_received_left_event
    //% block="on |%btn| button pressed"
    //% parts="Mbit_IR" shim=Mbit_IR::onPressEvent
    function onPressEvent(btn: RemoteButton, body: () => void): void;

    /**
     * initialises local variablesssss
     */
    //% blockId=ir_init
    //% block="connect ir receiver to %pin"
    //% parts="Mbit_IR" shim=Mbit_IR::init
    function init(pin: Pins): void;
}

// Auto-generated. Do not edit. Really.
