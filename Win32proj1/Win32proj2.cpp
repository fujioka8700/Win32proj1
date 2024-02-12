// ************************************
// Ex 文字列を表示するプログラム
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

int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    static TCHAR szWindowClass[] = _T("Sample03");
    static TCHAR szTitle[] = _T("ウィンドウを使ったアプリのサンプル②");

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
            _T("Sample03"),
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
            _T("Sample03"),
            NULL);
        return 1;
    }

    // ウィンドウの表示に必要なパラメータ:
    // hWnd     : CreateWindowの戻り値
    // nCmdShow : WinMainの引数の4番目
    ShowWindow(hWnd,
        nCmdShow);
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
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR greeting[] = _T("Hello, World!");
    switch (message)
    {
    case WM_PAINT:
        //  描画処理の開始
        hdc = BeginPaint(hWnd, &ps);
        // 文字列の出力。「Hello, World!」と出力する。
        TextOut(hdc,
            5, 5,
            greeting, _tcslen(greeting));
        //  ペイント処理の終了
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}