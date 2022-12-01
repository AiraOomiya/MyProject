#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//プロトタイプ宣言
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd); //初期化処理
void UninitKeyboard(void); //終了処理
void UpdateKeyboard(void); //更新処理
bool GetKeyboardPress(int nKey); //プレス
bool GetKeyboardTrigger(int nKey); //トリガー
bool GetKeyboardRepeat(int nKey); //リピート

#endif
