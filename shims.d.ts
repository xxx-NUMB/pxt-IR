// Auto-generated. Do not edit.



    //% color=50 weight=19 block="Mbit_IR"
    //% icon="\uf1eb"
declare namespace Mbit_IR {

    /**
     * 判断遥控器的按键是否按下
     */
    //% block="on |%btn| button pressed" shim=Mbit_IR::onPressEvent
    function onPressEvent(btn: RemoteButton, body: () => void): void;

    /**
     * 选择红外接收头连接的引脚
     */
    //% block="connect ir receiver to %pin" shim=Mbit_IR::init
    function init(pin: Pins): void;
}

// Auto-generated. Do not edit. Really.
