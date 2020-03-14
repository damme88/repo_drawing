#pragma once

// TViewCore command target

class __declspec(dllexport) TViewCore : public CObject
{
public:
	TViewCore();
	virtual ~TViewCore();

public:
    BOOL InitializeOpenGL(HWND hwnd);
    void OnSize(const INT& nWidth, const INT& nHeight);
    void Renderscene();

private:
    HGLRC   m_hRC;
    HDC     m_hDC;
};


