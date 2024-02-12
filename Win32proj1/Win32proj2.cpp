// ************************************
// Ex ウインドウ描画の雛形
// ************************************
//必要なヘッダーファイルのインクルード
#define STRICT

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

// シンボル定義及びマクロ
#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600

//  インスタンス（グローバル変数）
HINSTANCE hInst;

//  ウィンドウプロシージャのコールバック関数
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(_In_ HINSTANCE hInstance,
        _In_opt_  HINSTANCE hPrevInstance,
        _In_ LPSTR lpCmdLine,
        _In_ int nShowCmd)
{
    static TCHAR szWindowClass[] = _T("Sample02");
    static TCHAR szTitle[] = _T("ウィンドウを使ったアプリのサンプル①");

    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("RegisterClassExの処理に失敗しました"),
            _T("Sample02"),
            NULL);

        return 1;
    }

    hInst = hInstance; // グローバル変数に値を入れる

    // The parameters to CreateWindow explained:
    // szWindowClass                : アプリケーションの名前
    // szTitle                      : タイトルバーに現れる文字列
    // WS_OVERLAPPEDWINDOW          : 生成するウィンドウのタイプ
    // CW_USEDEFAULT, CW_USEDEFAULT : 最初に置くポジション (x, y)
    // WINDOW_WIDTH, WINDOW_HEIGHT  : 最初のサイズ (幅, 高さ)
    // NULL                         : このウィンドウの親ウィンドウのハンドル
    // NULL                         : メニューバー（このサンプルでは使用せず）
    // hInstance                    : WinMain関数の最初のパラメータ
    // NULL                         : WM_CREATE情報（このアプリケーションでは使用せず）
    HWND hWnd = CreateWindow(
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    //  ウィンドウが生成できなかった場合
    if (!hWnd)
    {
        MessageBox(NULL,
            _T("ウィンドウ生成に失敗しました!"),
            _T("Sample02"),
            NULL);
        return 1;
    }

    // ウィンドウの表示に必要なパラメータ:
    // hWnd     : CreateWindowの戻り値
    // nCmdShow : WinMainの引数の4番目
    ShowWindow(hWnd,
        nShowCmd);
    UpdateWindow(hWnd);

    // メインのメッセージループ:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

//  ウィンドウプロシージャ（メッセージに対するコールバック関数）
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}