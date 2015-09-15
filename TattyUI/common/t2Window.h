#ifndef T2_WINDOW_H
#define T2_WINDOW_H

#include <TattyUI/render/t2Image.h>
#include <TattyUI/common/t2WindowBase.h>

namespace TattyUI
{
    class t2LinearGradient;
    class t2BoxGradient;
    //class t2WindowBase;
    // ���óɵ�������֧�ֶര�� ���˸о�û��ϵ
    class t2Window
    {
    public:
        static t2Window* getInstance();

        void init(string title, int width, int height, int positionX = 0, int positionY = 0);

        void draw();

        void setTitleBar(int height);

        int getTitleBar();

        void setDrag(bool drag);

        void setDoubleClick(bool doubleClick);

        void setClose(t2Image normal, t2Image hover, t2Image pressed);

        void setMaximize(t2Image normal, t2Image hover, t2Image pressed);

        void setMinimize(t2Image normal, t2Image hover, t2Image pressed);

        void setWindowRadius(int raidus);

        // �������Ƿ��ڱ�������
        bool inTitleBar(int x, int y);

        // ʵ�ʴ���
        t2WindowBase* window;

    protected:
        // ����ɾ�� ���ɸ��� �����Լ�����ʵ��
        t2Window();
        t2Window(const t2Window&) {}
        ~t2Window() {}
        t2Window& operator=(const t2Window& event) const {}

        friend class t2EventController;

        // �����϶����� ˫�����ڵ��¼�
        virtual void onMousePressed(int x, int y, int px, int py, int button);

        virtual void onMouseReleased(int x, int y, int px, int py, int button);

        virtual void onMouseMoved(int x, int y, int px, int py);

        // ��С�� ��� �رհ�ť
        class t2Button;
        t2Button *close, *maximize, *minimize;

        // �������߶�
        int titleBarHeight;

        // ����Բ��
        int windowRadius;

        bool bDoubleClick, bDrag;
        bool bPressed;

        // ������
        t2LinearGradient *titleBar;
        t2BoxGradient *titleBarShadow;
    };
}

#endif