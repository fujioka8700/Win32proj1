// ************************************
// Ex マウスのイベント処理を行う①
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

//文字列描画用配列
TCHAR   szstr[256] = _T("ボタンを押していません");

//  開始点
POINT  pt_start = { 0, 0 };
//  終了点
POINT pt_end = { 0, 0 };
//  ドラッグ中かどうかを示すフラグ
INT iDragFlag = 0;

//  インスタンス（グローバル変数）
HINSTANCE hInst;

//  ウィンドウプロシージャのコールバック関数
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    static TCHAR szWindowClass[] = _T("Sample06");
    static TCHAR szTitle[] = _T("マウスイベントを処理するプログラム②");

    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
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
            _T("Sample06"),
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
            _T("Sample06"),
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
    switch (message)
    {
    case WM_PAINT:
        //  描画処理の開始
        hdc = BeginPaint(hWnd, &ps);
        // ドラッグ中だったら、始点から終点まで線を引く
        if (iDragFlag) {
            MoveToEx(hdc, pt_start.x, pt_start.y, NULL);
            LineTo(hdc, pt_end.x, pt_end.y);
        }
        //  ペイント処理の終了
        EndPaint(hWnd, &ps);
        break;
        //キーを押した
        return 0;
        //左クリック
    case WM_LBUTTONDOWN:
        //  始点の位置の座標を取得
        pt_start.x = LOWORD(lParam);
        pt_start.y = HIWORD(lParam);
        //  ドラッグ中でなければ、終点もこの点に設定する。
        if (!iDragFlag) {
            pt_end = pt_start;
            //  ドラッグ中かどうかのフラグを立てる
            iDragFlag = 1;
        }
        //  描画の更新
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_LBUTTONUP:
        //  ドラッグ中かどうかのフラグを元に戻す
        iDragFlag = 0;
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_LBUTTONDBLCLK:
        break;
    case WM_RBUTTONDOWN:
        break;
    case WM_RBUTTONUP:
        break;
    case WM_RBUTTONDBLCLK:
        break;
    case WM_MBUTTONDOWN:
        break;
    case WM_MBUTTONUP:
        break;
    case WM_MBUTTONDBLCLK:
        break;
    case WM_MOUSEMOVE:
        //  マウスが移動した
        if (iDragFlag) {
            pt_end.x = LOWORD(lParam);
            pt_end.y = HIWORD(lParam);
            //再描画メッセージを発生させる
            InvalidateRect(hWnd, NULL, TRUE);
            return 0;
        }
        break;
        //キーを押した
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            //終了メッセージを発生させる
            PostMessage(hWnd, WM_CLOSE, 0, 0);
            break;
        }
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