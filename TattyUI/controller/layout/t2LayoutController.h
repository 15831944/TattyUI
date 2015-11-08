#ifndef T2_LAYOUTCONTROLLER_H
#define T2_LAYOUTCONTROLLER_H


namespace TattyUI
{
    enum T2Layout
    {
        // ���Բ���
        T2_LINEAR_LAYOUT,
        // �б���
        T2_LIST_LAYOUT
    };

    class t2Div;
    class t2LayoutController
    {
    public:
        static t2LayoutController* getInstance();
        
        // ������div��ǰ״̬����
        void update();

        // div����״̬ȫ�ָ���
        void updateAll();

    private:
        // ����ָ��div��״̬����
        void updateDiv(t2Div* div, bool bCondition = false);

        // ����div���ڵ����ͽ�div����Ϊ���Բ��ַ�ʽ����
        void linearLayout(t2Div* div, bool bCondition = false);

        // ����div���ڵ����ͽ�div����Ϊ�б��ַ�ʽ����
        void listLayout(t2Div* div, bool bCondition = false);

        // ����ɾ�� ���ɸ��� �����Լ�����ʵ��
        t2LayoutController();
        t2LayoutController(const t2LayoutController&) {}
        ~t2LayoutController() {}
        t2LayoutController& operator=(const t2LayoutController& event) const {}
    };
}

#endif