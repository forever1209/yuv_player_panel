#include <QMainWindow>
#include "rviz_common/panel.hpp"
namespace mc
{
    namespace Images
    {
        class YuvPlayerPanel : public rviz_common::Panel
        {
            Q_OBJECT
        public:
            explicit YuvPlayerPanel(QWidget *parent = nullptr);

        private:
            void InitWidget();
            void InitConnect();
        private:

        };
    }

}
