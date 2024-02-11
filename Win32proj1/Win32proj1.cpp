// ***************************************
// ダイアログを表示するサンプル
// ***************************************

//必要なヘッダーファイルのインクルード
#define STRICT
#include <windows.h>
#include <tchar.h>

//--------------------------------------------
// Name:WinMain()
// Desc:アプリケーションのエントリー関数
//--------------------------------------------
INT WINAPI WinMain(_In_ HINSTANCE hInstance,
        _In_opt_  HINSTANCE hPrevInstance,
        _In_ LPSTR lpCmdLine,
        _In_ int nShowCmd)
{
    MessageBox(NULL, _T(""), _T(""), MB_OK);

    return 0;
}