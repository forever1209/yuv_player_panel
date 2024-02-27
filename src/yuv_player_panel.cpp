#include "rviz_common/properties/property_tree_widget.hpp"
#include "rviz_common/interaction/selection_manager.hpp"
#include "rviz_common/visualization_manager.hpp"
#include "yuv_player_panel/yuv_player_panel.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>
#include <QDialog>
#include <QLabel>
namespace mc
{
    namespace Images
    {
        YuvPlayerPanel::YuvPlayerPanel(QWidget *parent)
            : rviz_common::Panel(parent)
            {
                InitWidget();
                InitConnect();
            }
        void YuvPlayerPanel::InitWidget()
        {

        }

        void YuvPlayerPanel::InitConnect()
        {

        }
    } //namespace Images
} // namespace mc
#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(mc::Images::YuvPlayerPanel, rviz_common::Panel)