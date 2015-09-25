#include <TattyUI/controller/layout/t2LayoutController.h>
#include <TattyUI/div/t2DivController.h>
#include <LinearList/t3Queue.h>
#include <TattyUI/common/t2Window.h>
#include <TattyUI/render/t2Renderer.h>

namespace TattyUI
{
    enum t2UpdateStatus
    {
        T2_UPDATESTATUS_ONE = 1,
        T2_UPDATESTATUS_ALL = 3
    };

    t2LayoutController::t2LayoutController()
    {

    }

    t2LayoutController* t2LayoutController::getInstance()
    {
        static t2LayoutController temp;
        return &temp;
    }

    void t2LayoutController::update()
    {
        t2DivController* divController = t2DivController::getInstance();

        for(auto it : divController->divTable)
        {
            if(it.second->getCSS().display != T2_DISPLAY_NONE)
                updateDiv(it.second);
        }
    }

    void t2LayoutController::updateAll()
    {
        t2DivController* divController = t2DivController::getInstance();

        for(auto it : divController->divTable)
        {
            // ����״̬ȫȨ����
            for(int i = T2_NORMAL; i <= T2_ACTIVE; i++)
            {
                it.second->setStatus(i);
                updateDiv(it.second);
            }

            it.second->setStatus(T2_NORMAL);
        }
    }

    void t2LayoutController::updateDiv(t2Div* div)
    {
        if(div->parent)
        {
            switch(div->parent->layout)
            {
            case T2_LINEAR_LAYOUT:
                linearLayout(div);
                break;
            case T2_LIST_LAYOUT:
                listLayout(div);
                break;

            default:
                t2PrintError("���󲼾ִ���");
                break;
            }
        }
        // ���ڵ�Ĭ��Ϊ���Բ���
        else
            linearLayout(div);
    }

    void t2LayoutController::linearLayout(t2Div* div)
    {
        t2Window* window = t2Window::getInstance();
        t2Div *parent = div->parent;

        t2Style& css = div->getCSS();
        // ���ڵ�
        if(!parent)
        {
            css.x = css.marginLeft;
            css.y = css.marginTop + window->getTitleBarHeight();

            css.contentSize.x = css.marginLeft + css.paddingLeft;
            css.contentSize.y = css.marginTop + css.paddingTop + window->getTitleBarHeight();

            int tempWidth = css.width - css.paddingLeft - css.paddingRight;
            css.contentSize.width = (tempWidth > 0) ? tempWidth : 0;

            int tempHeight = css.height - css.paddingTop - css.paddingBottom;
            css.contentSize.height = (tempHeight > 0) ? tempHeight : 0;

            return;
        }

        // ͨ�ò��� 
        t2Style& parentCSS = parent->getCSS();

        int allChildWidth = 0, allChildHeight = 0;
        int nowChildWidth = 0, nowChildHeight = 0, nowMaxHeight = 0;

        // ��ͷ������������֮ǰ�������ֵܽ��
        for(t2Div* childptr = parent->child; childptr != div; childptr = childptr->next)
        {
            t2Style& childCSS = childptr->getCSS();

            // x
            nowChildWidth = childCSS.marginLeft + childCSS.width + childCSS.marginRight;

            // ��ǰ�е���ʼλ��
            allChildWidth += nowChildWidth;

            // y
            nowChildHeight = childCSS.marginTop + childCSS.height + childCSS.marginBottom;
            // ��¼��ǰ�����߶�
            if(nowChildHeight > nowMaxHeight)
                nowMaxHeight = nowChildHeight;

            // �������ڵ�����ɵ������ʾ���(ȥ���ڱ߾�)�Զ�����
            if(childptr->next != div)
            {
                t2Style& x = childptr->next->getCSS();
                if(allChildWidth + x.width + x.marginLeft + x.marginRight > parentCSS.width - parentCSS.paddingLeft - parentCSS.paddingRight)
                {
                    allChildWidth = 0;

                    // �ۻ�yֵ
                    allChildHeight += nowMaxHeight;

                    nowMaxHeight = 0;
                }

                // ��������ֱ�Ӳü�����ʾ
                if(allChildHeight + x.height + x.marginTop + x.marginBottom > parentCSS.height - parentCSS.paddingTop - parentCSS.paddingBottom)
                    x.display = T2_DISPLAY_NONE;
            }
            else
            {
                // ���һ�����
                if(allChildWidth + css.width + css.marginLeft + css.marginRight > parentCSS.width - parentCSS.paddingLeft - parentCSS.paddingRight)
                {
                    allChildWidth = 0;

                    // �ۻ�yֵ
                    allChildHeight += nowMaxHeight;

                    nowMaxHeight = 0;
                }

                // ��������ֱ�Ӳü�����ʾ
                if(allChildHeight + css.height + css.marginTop + css.marginBottom > parentCSS.height - parentCSS.paddingTop - parentCSS.paddingBottom)
                    css.display = T2_DISPLAY_NONE;
            }
        }

        css.x = parentCSS.x + parentCSS.paddingLeft + allChildWidth;

        css.y = parentCSS.y + parentCSS.paddingTop + allChildHeight;

        css.contentSize.x = parentCSS.x + parentCSS.paddingLeft + allChildWidth +
            css.marginLeft + css.paddingLeft;

        css.contentSize.y = parentCSS.y + parentCSS.paddingTop + allChildHeight +
            css.marginTop + css.paddingTop;

        // ��ֹ�����ڱ߾������ڳ��ָ�ֵcontent-Size
        int tempWidth = css.width - css.paddingLeft - css.paddingRight;
        css.contentSize.width = (tempWidth) > 0 ? tempWidth : 0;

        int tempHeight = css.height - css.paddingTop - css.paddingBottom;
        css.contentSize.height = (tempHeight) > 0 ? tempHeight : 0;
    }

    // ����div���ڵ����ͽ�div����Ϊ�б��ַ�ʽ����
    void t2LayoutController::listLayout(t2Div* div)
    {

    }
}