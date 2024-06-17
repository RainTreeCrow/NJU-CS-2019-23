// WindowsProject1.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "WindowsProject1.h"
#include <vector>
#include <cmath>
using std::vector;
vector<POINT> points;

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void plus(TCHAR num1[], TCHAR num2[], TCHAR result[]);
void minus(TCHAR num1[], TCHAR num2[], TCHAR result[]);
void multiply(TCHAR num1[], TCHAR num2[], TCHAR result[]);
void division(TCHAR num1[], TCHAR num2[], TCHAR result[]);
void calcLongestDistance(POINT &p1, POINT &p2);





int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hEditNumA, hEditNumB, btn1, show1, show2;
    static bool flag1 = false, flag2 = false;;
    TCHAR numA[100], numB[100];
    TCHAR answer[100];
    POINT pt, pt2;
    switch (message)
    {
    case WM_LBUTTONDOWN: // 鼠标左键
        if (flag1) {
            pt.x = LOWORD(lParam);
            pt.y = HIWORD(lParam);
            points.push_back(pt);
            wsprintf(answer, TEXT("x：%ld，y：%ld"), pt.x, pt.y);
            LPCWSTR str = answer;
            SetWindowText(show1, str);
        }
    case WM_KEYDOWN:
        if (flag2) {
            wsprintf(answer, TEXT("ASCII: %d"), wParam);
            LPCWSTR str = answer;
            SetWindowText(show2, str);
        }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_PLUS: // 加法
                hEditNumA = CreateWindow(TEXT("edit"), TEXT(""),
                    WS_CHILD | WS_VISIBLE | WS_BORDER /*数A*/ | ES_AUTOHSCROLL /*水平滚动*/,
                    80, 20, 200, 26,
                    hWnd, (HMENU)3, hInst, NULL
                );
                hEditNumB = CreateWindow(TEXT("edit"), TEXT(""),
                    WS_CHILD | WS_VISIBLE | WS_BORDER /*数B*/ | ES_AUTOHSCROLL /*水平滚动*/,
                    80, 56, 200, 26,
                    hWnd, (HMENU)4, hInst, NULL
                );
                //创建按钮控件
                btn1 = CreateWindow(TEXT("button"), TEXT("确认"),
                    WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT/*扁平样式*/,
                    80, 92, 200, 30,
                    hWnd, (HMENU)5, hInst, NULL
                    );
                break;
            case IDM_MINUS: // 减法
                hEditNumA = CreateWindow(TEXT("edit"), TEXT(""),
                    WS_CHILD | WS_VISIBLE | WS_BORDER /*数A*/ | ES_AUTOHSCROLL /*水平滚动*/,
                    80, 20, 200, 26,
                    hWnd, (HMENU)3, hInst, NULL
                    );
                hEditNumB = CreateWindow(TEXT("edit"), TEXT(""),
                    WS_CHILD | WS_VISIBLE | WS_BORDER /*数B*/ | ES_AUTOHSCROLL /*水平滚动*/,
                    80, 56, 200, 26,
                    hWnd, (HMENU)4, hInst, NULL
                    );
                //创建按钮控件
                btn1 = CreateWindow(TEXT("button"), TEXT("确认"),
                    WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT/*扁平样式*/,
                    80, 92, 200, 30,
                    hWnd, (HMENU)6, hInst, NULL
                    );
                break;
            case IDM_Multiply: // 乘法
                hEditNumA = CreateWindow(TEXT("edit"), TEXT(""),
                    WS_CHILD | WS_VISIBLE | WS_BORDER /*数A*/ | ES_AUTOHSCROLL /*水平滚动*/,
                    80, 20, 200, 26,
                    hWnd, (HMENU)3, hInst, NULL
                    );
                hEditNumB = CreateWindow(TEXT("edit"), TEXT(""),
                    WS_CHILD | WS_VISIBLE | WS_BORDER /*数B*/ | ES_AUTOHSCROLL /*水平滚动*/,
                    80, 56, 200, 26,
                    hWnd, (HMENU)4, hInst, NULL
                    );
                //创建按钮控件
                btn1 = CreateWindow(TEXT("button"), TEXT("确认"),
                    WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT/*扁平样式*/,
                    80, 92, 200, 30,
                    hWnd, (HMENU)7, hInst, NULL
                    );
                break;
            case IDM_DIVISION: // 除法
                hEditNumA = CreateWindow(TEXT("edit"), TEXT(""),
                    WS_CHILD | WS_VISIBLE | WS_BORDER /*数A*/ | ES_AUTOHSCROLL /*水平滚动*/,
                    80, 20, 200, 26,
                    hWnd, (HMENU)3, hInst, NULL
                    );
                hEditNumB = CreateWindow(TEXT("edit"), TEXT(""),
                    WS_CHILD | WS_VISIBLE | WS_BORDER /*数B*/ | ES_AUTOHSCROLL /*水平滚动*/,
                    80, 56, 200, 26,
                    hWnd, (HMENU)4, hInst, NULL
                    );
                //创建按钮控件
                btn1 = CreateWindow(TEXT("button"), TEXT("确认"),
                    WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT/*扁平样式*/,
                    80, 92, 200, 30,
                    hWnd, (HMENU)8, hInst, NULL
                    );
                break;
            case IDM_POINT: // 取点
                show1 = CreateWindow(TEXT("static"), TEXT("点："),
                    WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE /*垂直居中*/ | SS_CENTER /*水平居右*/,
                    150, 56, 200, 26,
                    hWnd, (HMENU)2, hInst, NULL
                    );
                flag1 = true;
                break;

            case IDM_DISTANCE: // 最长距
                if (points.size() == 0) { break; }
                calcLongestDistance(pt, pt2);
                wsprintf(answer, TEXT("x1：%ld，y1：%ld, x2: %ld, y2: %ld"), pt.x, pt.y, pt2.x, pt2.y);
                MessageBox(hWnd, answer, TEXT("结果"), MB_ICONINFORMATION);
                break;

            case IDM_LETTER:
                show2 = CreateWindow(TEXT("static"), TEXT("键："),
                    WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE /*垂直居中*/ | SS_CENTER /*水平居右*/,
                    200, 56, 200, 26,
                    hWnd, (HMENU)2, hInst, NULL
                );
                flag2 = true;
                break;

            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case 5: // 加法按钮参数
                GetWindowText(hEditNumA, numA, 100);
                GetWindowText(hEditNumB, numB, 100);
                plus(numA, numB, answer);
                MessageBox(hWnd, answer, TEXT("结果"), MB_ICONINFORMATION);
                break;
            case 6: // 减法按钮参数
                GetWindowText(hEditNumA, numA, 100);
                GetWindowText(hEditNumB, numB, 100);
                minus(numA, numB, answer);
                MessageBox(hWnd, answer, TEXT("结果"), MB_ICONINFORMATION);
                break;
            case 7: // 乘法按钮参数
                GetWindowText(hEditNumA, numA, 100);
                GetWindowText(hEditNumB, numB, 100);
                multiply(numA, numB, answer);
                MessageBox(hWnd, answer, TEXT("结果"), MB_ICONINFORMATION);
                break;
            case 8: // 除法按钮参数
                GetWindowText(hEditNumA, numA, 100);
                GetWindowText(hEditNumB, numB, 100);
                division(numA, numB, answer);
                MessageBox(hWnd, answer, TEXT("结果"), MB_ICONINFORMATION);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int toInt(TCHAR num[]) {
    int sum = 0;
    int len = _tcslen(num);
    for (int i = 0; i < len; i++) {
        sum = sum * 10 + (num[i] - '0');
    }
    return sum;
}
void toTCHAR(int num, TCHAR result[]) {
    if (num == 0) { result[0] = (TCHAR)('0'); return; }
    int temp = num;
    int len = 0;
    while (temp > 0) { len++; temp = temp / 10; }
    result[len] = 0;
    for (int i = len - 1; i >= 0; i--) {
        result[i] = (TCHAR)(num % 10 + '0');
        num = num / 10;
    }
}

void plus(TCHAR num1[], TCHAR num2[], TCHAR result[]) {
    int ans = toInt(num1) + toInt(num2);
    toTCHAR(ans, result);
}

void minus(TCHAR num1[], TCHAR num2[], TCHAR result[]) {
    int ans = toInt(num1) - toInt(num2);
    toTCHAR(ans, result);
}

void multiply(TCHAR num1[], TCHAR num2[], TCHAR result[]) {
    int ans = toInt(num1) * toInt(num2);
    toTCHAR(ans, result);
}

void division(TCHAR num1[], TCHAR num2[], TCHAR result[]) {
    int ans = toInt(num1) / toInt(num2);
    toTCHAR(ans, result);
}

void calcLongestDistance(POINT& p1, POINT& p2) {
    if (points.size() == 0) { return; }
    POINT ansp1 = points[0], ansp2 = points[0];
    double distance = 0.0;
    for (int i = 0; i < points.size(); i++) {
        for (int j = 0; j < points.size(); j++) {
            if (i == j) { continue; }
            double newdis = pow(points[i].x - points[j].x, 2) + pow(points[i].y - points[j].y, 2);
            if (newdis > distance) {
                distance = newdis;
                ansp1 = points[i];
                ansp2 = points[j];
            }
        }
    }
    p1 = ansp1;
    p2 = ansp2;
}