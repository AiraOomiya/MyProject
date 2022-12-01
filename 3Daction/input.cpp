#include "Input.h"

//マクロ定義
#define NUM_KEY_MAX	(256) //キーの最大数

//グローバル変数
LPDIRECTINPUT8 g_pInput = NULL; //DirectInputオブジェクトへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL; //入力デバイス(キーボード)へのポインタ
BYTE g_aKeyState[NUM_KEY_MAX]; //プレス
BYTE g_aKeyStateTrigger[NUM_KEY_MAX]; //トリガー
BYTE g_aKeyStateRepeat[NUM_KEY_MAX]; //リピート
DWORD g_aCurrentTime[NUM_KEY_MAX]; //現在時刻
DWORD g_aExecLastTime[NUM_KEY_MAX]; //最後にTrueした時刻

									//キーボードの初期化処理
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	int nCount;//カウント	

			   //DirectInputオブジェクト
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void* *)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//入力デバイス(キーボード)の生成
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モード設定
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得
	g_pDevKeyboard->Acquire();

	for (nCount = 0; nCount < NUM_KEY_MAX; nCount++)
	{
		g_aCurrentTime[nCount] = 0; //初期化する
		g_aExecLastTime[nCount] = timeGetTime(); //現在時刻を取得(保存)
	}

	return S_OK;
}

//キーボードの終了処理
void UninitKeyboard(void)
{
	//入力デバイス(キーボード)の破棄
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire(); //キーボードへのアクセス権を放棄
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}
	//DirectInputオブジェクトの破棄
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//キーボードの更新処理
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;

	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey])&aKeyState[nCntKey]; //キーボードのトリガー情報を保存
			g_aKeyState[nCntKey] = aKeyState[nCntKey]; //キーボードのプレス情報を保存

			g_aCurrentTime[nCntKey] = timeGetTime();

			if (aKeyState[nCntKey] && (g_aCurrentTime[nCntKey] - g_aExecLastTime[nCntKey]) >= 150)
			{
				g_aExecLastTime[nCntKey] = g_aCurrentTime[nCntKey];
				g_aKeyStateRepeat[nCntKey] = aKeyState[nCntKey];
			}
			else
			{
				g_aKeyStateRepeat[nCntKey] = 0;
			}
		}
	}
	else
	{
		g_pDevKeyboard->Acquire(); //キーボードへのアクセス権獲得
	}
}

//キーボードのプレス情報を取得
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}

//キーボードのトリガー情報を取得
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//キーボードのリピート情報を取得
bool GetKeyboardRepeat(int nKey)
{
	return (g_aKeyStateRepeat[nKey] & 0x80) ? true : false;
}