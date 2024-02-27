#include "rviz_common/properties/property_tree_widget.hpp"
#include "rviz_common/interaction/selection_manager.hpp"
#include "rviz_common/visualization_manager.hpp"
#include "yuv_player_panel/yuv_player_panel.h"
#include <QLabel>

namespace mc
{
    namespace Images
    {
        static void rtspCallBack(uint8_t *yData,uint8_t * uData,uint8_t *vData,const int &ySize,const int &uSize,const int &vSize,void *ptr)
        {
            if(ptr==nullptr)
            {
                std::cout<<"opengl yuv widget not init"<<std::endl;
            }
        //     if(auto play = static_cast<YUVGLWidget*>(ptr))
        //     {
        //         play->Update(yData,uData,vData,ySize,uSize,vSize);
        // //        play->update();
        //     }
        }
        YuvPlayerPanel::YuvPlayerPanel(QWidget *parent)
            : rviz_common::Panel(parent)
            {
                InitWidget();
                InitConnect();
            }
        void YuvPlayerPanel::InitWidget()
        {
            mainLayout = new QFormLayout();
            radioButton = new QRadioButton(QStringLiteral("online 264"));
            CreateItem(false);
            mainLayout->addRow(radioButton);
            mainLayout->addRow(videoTopic,topicLineEdit);
            mainLayout->addRow(videoWith,widthLineEdit);
            mainLayout->addRow(videoLength,lengthLineEdit);
            mainLayout->addRow(playButton);
            connect(radioButton, &QRadioButton::toggled, this,[this](const bool &checked)
            {
                DeleteItem(checked);
                CreateItem(checked);
                if(checked)
                {
                    m_bChecked = true;
                    mainLayout->addRow(videoUrl,rtspLineEdit);
                    mainLayout->addRow(videoWith,widthLineEdit);
                    mainLayout->addRow(videoLength,lengthLineEdit);
                    mainLayout->addRow(playButton);
                    return ;
                }
                m_bChecked = false;
                mainLayout->addRow(videoTopic,topicLineEdit);
                mainLayout->addRow(videoWith,widthLineEdit);
                mainLayout->addRow(videoLength,lengthLineEdit);
                mainLayout->addRow(playButton);

            });
            connect(playButton,&QPushButton::clicked,this,[this](){
                int width_ = 0;
                int length_ = 0;
                std::string str_info = "";
                if(m_bChecked)
                {
                    m_bChecked = false;
                    if(widthLineEdit->text().isEmpty()||lengthLineEdit->text().isEmpty()||rtspLineEdit->text().isEmpty())
                    {
                        QMessageBox::warning(this, "Error", "Please enter all parameters.!");
                        return;
                    }
                    width_ = widthLineEdit->text().toInt();
                    length_ = lengthLineEdit->text().toInt();
                    str_info = rtspLineEdit->text().toStdString();
                    if(m_pRtspReceiver)
                    {
                        m_pRtspReceiver->Init(str_info);
                        m_pRtspReceiver->OpenAndCb(rtspCallBack,nullptr);
                    }
                }
                else
                {
                    if(widthLineEdit->text().isEmpty()||lengthLineEdit->text().isEmpty()||topicLineEdit->text().isEmpty())
                    {
                        QMessageBox::warning(this, "Error", "Please enter all parameters.!");
                        return ;
                    }
                    width_ = widthLineEdit->text().toInt();
                    length_ = lengthLineEdit->text().toInt();
                    str_info = topicLineEdit->text().toStdString();
                }
                //TODO:add widget init by width length
            });
            this->setLayout(mainLayout);
        }

        void YuvPlayerPanel::InitConnect()
        {

        }
        void YuvPlayerPanel::DeleteItem(const bool & checked)
        {
            if(mainLayout!=nullptr)
            {
                QLayoutItem *item;
                while ((item = mainLayout->takeAt(1)) != nullptr) {
                    QWidget *widget = item->widget();
                    delete widget; // 释放内存
                    widget = nullptr;
                    delete item;   // 释放内存
                    item = nullptr;
                }
                if(checked)
                {
                    delete videoUrl;
                    videoUrl = nullptr;
                    delete rtspLineEdit;
                    rtspLineEdit = nullptr;
                }
                else
                {
                    delete videoTopic;
                    videoTopic = nullptr;
                    delete topicLineEdit;
                    topicLineEdit = nullptr;
                }
            }
        }
        void YuvPlayerPanel::CreateItem(const bool & checked)
        {
            std::cout<<"create item "<<checked<<std::endl;
            playButton = new QPushButton(QStringLiteral("PLAY"));
            
            videoUrl = new QLabel("rtsp Address:");
            videoTopic = new QLabel("video Topic:");
            videoWith = new QLabel("video width:");
            videoLength = new QLabel("video height:");
            rtspLineEdit = new QLineEdit();
            topicLineEdit = new QLineEdit();
            widthLineEdit = new QLineEdit();
            lengthLineEdit = new QLineEdit();
        }
    } //namespace Images
        void Images::YuvPlayerPanel::onInitialize()
        {
            if(m_pRtspReceiver==nullptr)
            {
                m_pRtspReceiver = std::unique_ptr<mc::rtsp::RtspReceiver>(new mc::rtsp::RtspReceiver);
            }
        }
} // namespace mc
#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(mc::Images::YuvPlayerPanel, rviz_common::Panel)