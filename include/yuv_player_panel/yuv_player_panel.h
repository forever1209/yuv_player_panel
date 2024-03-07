#include <QMainWindow>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QRadioButton>
#include <QMessageBox>
#include <QDialog>
#include <QLabel>
#include <memory>
#include "rviz_common/panel.hpp"
#include "rstp/rtsp_receiver.h"
class YUVGLWidget;
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
            void DeleteItem(const bool & checked);
            void CreateItem(const bool & checked);
        protected:
            void onInitialize() override;
        private:
            QFormLayout * mainLayout = nullptr;
            QPushButton * playButton = nullptr;
            QRadioButton * radioButton = nullptr;
            QLabel * videoUrl = nullptr;
            QLabel * videoTopic = nullptr;
            QLabel * videoWith = nullptr;
            QLabel * videoLength = nullptr;
            QLineEdit * rtspLineEdit = nullptr;
            QLineEdit * topicLineEdit = nullptr;
            QLineEdit * widthLineEdit = nullptr;
            QLineEdit * lengthLineEdit = nullptr;
            bool m_bChecked = false;
            std::unique_ptr<mc::rtsp::RtspReceiver> m_pRtspReceiver = nullptr;
            YUVGLWidget * yuvWidget = nullptr;
        };
    }

}
