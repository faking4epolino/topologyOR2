#include <windows.h>
#include <math.h>

const wchar_t windowClass[] = L"win32app";
const wchar_t windowTitle[] = L"Win32API - topology of the OR2";

int b_x, b_y;
int g_x, g_y;
int r_x, r_y;
int period = 10;
int m_x, m_y;
int count_down = 0;

bool flag = 0;


void workspace(HDC hdc, HWND hWnd)
{
    HPEN pen, old_pen;
    HBRUSH brush, old_brush;

    RECT rect;
    GetClientRect(hWnd, &rect);


    //background
    brush = CreateSolidBrush(RGB(0, 0, 0));
    old_brush = (HBRUSH)SelectObject(hdc, brush);

    pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    old_pen = (HPEN)SelectObject(hdc, pen);

    Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

    SelectObject(hdc, old_pen);
    DeleteObject(pen);

    SelectObject(hdc, old_brush);
    DeleteObject(brush);

    pen = CreatePen(PS_SOLID, 1, RGB(120, 120, 120));
    old_pen = (HPEN)SelectObject(hdc, pen);

    for (int i = 0; i < rect.right; i += 40)
    {
        MoveToEx(hdc, i, 0, nullptr);
        LineTo(hdc, i, rect.bottom);
    }
    for (int j = 0; j < rect.bottom; j += 40)
    {
        MoveToEx(hdc, 0, j, nullptr);
        LineTo(hdc, rect.right, j);
    }

    SelectObject(hdc, old_pen);
    DeleteObject(pen);
}

void DrowLayout(HDC hdc, bool flag = false)
{
    HPEN pen, old_pen;
    HBRUSH brush, old_brush;

    if (flag)
    {
        brush = CreateSolidBrush(RGB(255, 255, 255));
        old_brush = (HBRUSH)SelectObject(hdc, brush);
        pen = CreatePen(PS_SOLID, 4 , RGB(255, 255, 255));
        old_pen = (HPEN)SelectObject(hdc, pen);

        MoveToEx(hdc, b_x - 10, b_y - 10, NULL);
        LineTo(hdc, b_x - 10, b_y + 360);

        MoveToEx(hdc, b_x + 190, b_y - 10, NULL);
        LineTo(hdc, b_x + 190, b_y + 360);

        MoveToEx(hdc, b_x - 10, b_y - 10, NULL);
        LineTo(hdc, b_x + 190, b_y - 10);

        MoveToEx(hdc, b_x - 10, b_y + 360, NULL);
        LineTo(hdc, b_x + 190, b_y + 360);

        SelectObject(hdc, old_pen);
        DeleteObject(pen);
        SelectObject(hdc, old_brush);
        DeleteObject(brush);
    }
 //topology green
    brush = CreateSolidBrush(RGB(0, 255, 0));
    old_brush = (HBRUSH)SelectObject(hdc, brush);

    pen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
    old_pen = (HPEN)SelectObject(hdc, pen);

    Rectangle(hdc, g_x + 10, g_y + 40, g_x + 170, g_y + 100);
    Rectangle(hdc, g_x + 110, g_y + 40, g_x + 170, g_y + 155);

    Rectangle(hdc, g_x + 10, g_y + 300, g_x + 170, g_y + 240);
    Rectangle(hdc, g_x + 110, g_y + 300, g_x + 170, g_y + 185);


    SelectObject(hdc, old_pen);
    DeleteObject(pen);

    SelectObject(hdc, old_brush);
    DeleteObject(brush);
//topology red 
    brush = CreateSolidBrush(RGB(255, 0, 0));
    old_brush = (HBRUSH)SelectObject(hdc, brush);

    pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    old_pen = (HPEN)SelectObject(hdc, pen);
    Rectangle(hdc, r_x + 33, r_y + 40, r_x + 48, r_y + 240);
    Rectangle(hdc, r_x + 83, r_y + 40, r_x + 98, r_y + 240);
    Rectangle(hdc, r_x + 133, r_y + 40, r_x + 148, r_y + 300);


    SelectObject(hdc, old_pen);
    DeleteObject(pen);

    SelectObject(hdc, old_brush);
    DeleteObject(brush);


 //topology blue
    brush = CreateSolidBrush(RGB(0, 0, 255));
    old_brush = (HBRUSH)SelectObject(hdc, brush);

    pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
    old_pen = (HPEN)SelectObject(hdc, pen);

    Rectangle(hdc, b_x, b_y, b_x + 180, b_y + 40);
    Rectangle(hdc, b_x, b_y + 300, b_x + 180, b_y + 340);


    Rectangle(hdc, b_x + 10, b_y + 50, b_x + 25, b_y + 130);
    Rectangle(hdc, b_x + 10, b_y + 120, b_x + 140, b_y + 130);
    Rectangle(hdc, b_x + 125, b_y + 130, b_x + 140, b_y + 230);

    Rectangle(hdc, b_x + 58, b_y + 220, b_x + 140, b_y + 230);
    Rectangle(hdc, b_x + 58, b_y + 220, b_x + 73, b_y + 280);
    Rectangle(hdc, b_x + 10, b_y + 300, b_x + 25, b_y + 240);

    Rectangle(hdc, b_x + 10, b_y + 145, b_x + 48, b_y + 185);
    Rectangle(hdc, b_x + 60, b_y + 145, b_x + 98, b_y + 185);

    Rectangle(hdc, b_x + 155, b_y + 50, b_x + 170, b_y + 280);

    SelectObject(hdc, old_pen);
    DeleteObject(pen);

    SelectObject(hdc, old_brush);
    DeleteObject(brush);

}

void DrawPlot(HDC hdc, HWND hWnd)
{
    HPEN pen, old_pen;
    HBRUSH brush, old_brush;

    RECT rect;
    GetClientRect(hWnd, &rect);


    int width = (rect.right - rect.left) / 3;
    int height = (rect.bottom -rect.top ) / 3;
    double step = period * 3.14159 / (width);


    brush = CreateSolidBrush(RGB(255, 255, 255));
    old_brush = (HBRUSH)SelectObject(hdc, brush);

    pen = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
    old_pen = (HPEN)SelectObject(hdc, pen);

    Rectangle(hdc, 0, height*2, width, height*3);

    SelectObject(hdc, old_pen);
    DeleteObject(pen);

    SelectObject(hdc, old_brush);
    DeleteObject(brush);

    //Drawing coordinate axes
    MoveToEx(hdc, 0, (height/ 2) + 2*height, nullptr);
    LineTo(hdc, width, (height/2) + 2*height);



    for (double x = 0; x < width; x += 0.1)
    {
        double y = cos(x * step);
        int pixelY = (height/ 2) - (y * height / 4) + 2*height; // Масштабируем график косинуса
        SetPixel(hdc, x, pixelY, RGB(0, 0, 0));
    }
}



long __stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

    PAINTSTRUCT ps;
    HDC hdc;

    HPEN pen, old_pen;
    HBRUSH brush, old_brush;

    RECT rect;
    GetClientRect(hWnd, &rect);

    int width = (rect.right - rect.left) / 3;
    int height = (rect.bottom - rect.top) / 3;
    double step = 10 * 3.14159;



   switch (message)
   {
    case WM_KEYDOWN:
    {
        switch (LOWORD(wParam))
        {
        case VK_OEM_PLUS:
            if (period < 30) 
            {
                period += 2;
                InvalidateRect(hWnd, nullptr, true);
            }
            break;
        case VK_OEM_MINUS:
            if (period > 0) 
            {
                period -= 2;
                InvalidateRect(hWnd, nullptr, true);
            }
            break;
        default:
            break;
        }

    }
    break;

    case WM_LBUTTONDOWN:
    {
        if ((wParam & MK_CONTROL) && flag)
        {

            b_x = LOWORD(lParam);
            b_y = HIWORD(lParam);

            g_x = LOWORD(lParam);
            g_y = HIWORD(lParam);

            r_x = LOWORD(lParam);
            r_y = HIWORD(lParam);
        }
        if ((rect.right - rect.left) < (b_x + 180) || (rect.bottom - rect.top) < (b_y + 340)) { break; }


        if ((rect.bottom - b_y-100) < (2*height) && (rect.left + b_x < width)) { break; }
        InvalidateRect(hWnd, nullptr, true);
    }
    break;

    case WM_RBUTTONDOWN:
    {
        count_down++;

        m_x = LOWORD(lParam);
        m_y = HIWORD(lParam);
        for (int x = b_x; x <= (b_x + 180); x++)
        {
            for (int y = b_y; y <= (b_y + 340); y++)
            {
                if (x == m_x && y == m_y)
                {
                    if (count_down == 1)
                    {
                        flag = true;
                    }
                    if(count_down != 1)
                    {
                        flag = false;
                        count_down = 0;
                    }

                    InvalidateRect(hWnd, nullptr, true);
                    break;

                }
            }
        }
    }
        
    break;

    case WM_CLOSE:
    {
        if (MessageBox(hWnd, L"Сlose the window ?", L"Info", MB_YESNO | MB_ICONINFORMATION) == IDNO)
            return 0;
    }
    break;

    case WM_DESTROY:

        PostQuitMessage(0);

        break;

    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);

        workspace(hdc, hWnd);

        DrowLayout(hdc, flag);

        DrawPlot(hdc, hWnd);

        EndPaint(hWnd, &ps);

        break;
    }
   }
    return DefWindowProc(hWnd, message, wParam, lParam);
}



int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
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
    wcex.lpszClassName = windowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

    if (!RegisterClassEx(&wcex)) {
        MessageBox(NULL, L"Cant register window class!", L"Win32 API Test", NULL);
        return 1;
    }

    HWND hWnd = CreateWindow(windowClass, windowTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1200, 800, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        MessageBox(NULL, L"Cant create window!", L"Win32 API Test", NULL);
        return 1;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}