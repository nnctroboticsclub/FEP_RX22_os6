/**
 *  @file   FEP_RX22.h
 *  @brief  FEP受信用ライブラリ
 *  @author 安澤瑠
 *  @date   22/10/6
 */
#ifndef FEP_RX22_H
#define FEP_RX22_H

#define TIMEOUT_COUNT 5
#define ControllerMode 0 // 1にするとコントローラー専用受信。0にすると汎用受信。

#include "mbed.h"

/**
 *  @class con 
 *  @brief class for FEP
 *  @note  RawSerialクラスを使用しているため mbed-os 6 では使えません。  Not compatible with mbed-os 6
 */
class FEP_RX22 : public mbed::UnbufferedSerial {
public :
    /** constructor
     *  @param tx   FEPと接続するSerialTX pin
     *  @param rx   FEPと接続するSerialRX pin
     *  @param addr コントローラーについてるFEPのアドレス
     *  @param baud 通信速度(デフォルト115200)
     */
    FEP_RX22(PinName tx, PinName rx, uint8_t addr_, int baud=115200);

    /** Start receiving
     */
    void StartReceive();
    
    /** Check timeout
     *  @brief 0.1秒毎のループで受信のタイムアウトをチェック
     */
    void TimeoutLoop();

    /** Interrupt input
     */
    void ReceiveBytes();

    /** extract the message
     */
    void CheckData();

    /** Write the received message
     *  @param data 受信メッセージを格納する配列
     */
    uint8_t getData(uint8_t *data);
    
    /** Set controller data
     */
    void getControllerState();
    
    bool getButton(uint8_t n); //! ボタンの値を返す。
    int16_t getStick(uint8_t n); //! スティックの値を返す。中心を0,範囲は-128 ~ 128とする。
    int16_t getTrigger(uint8_t n); //! トリガーの値を返す。
    uint8_t getTimeout();
    bool getStatus();
    

private :
    
    Ticker timeoutTimer;
    uint8_t addr;         //! 通信相手のアドレス
    uint8_t buffer[256];  //! 全受信データを格納するリングバッファ配列
    uint8_t msgdata[128]; //! メッセージのみを格納する配列
    uint8_t bufindex;     //! buffer の添え字変数
    uint8_t timeout;      //! 0.1秒間通信が成功していないと1増える
    uint8_t indexofR;     //! RBNの先頭文字の位置
    bool status;          //! (TIMEOUT_COUNT * 0.1)秒間通信が成り立っていない場合、false
    uint8_t datalen;      //! データバイトの長さ
    // コントローラ用
    uint8_t button[2];    //! ボタンの値を格納
    uint8_t stick[4];     //! スティックの値を格納
    uint8_t trigger[4];   //! トリガーの値を格納
};

#endif