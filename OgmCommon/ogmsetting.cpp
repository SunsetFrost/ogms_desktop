#include "ogmsetting.h"

#include <QDir>

QString OgmSetting::defaultModelServerId="5952e96a-3963-4d17-80d7-e3c961f8e7b4";
QString OgmSetting::defaultDataServerId="4cdaae85-3b1b-4901-983d-816eaabbd8df";
QString OgmSetting::defaultFavorId="fefab154-37e7-4c2b-a0f6-c7e7e8f7d8b2";

QString OgmSetting::udxDataPath=QDir::currentPath()+"/tool/UDX_Data/Vge_Tools_UDX_Data.exe";
QString OgmSetting::udxSchemaPath=QDir::currentPath()+"/tool/UDX_schema/Vge_Tools_UDX_schema.exe";
QString OgmSetting::omsToolPath=QDir::currentPath()+"/tool/OmsPacker/mainwindows.exe";

QString OgmSetting::modelServerFilePath=QDir::currentPath()+"/modelServer.config";
QString OgmSetting::dataServerFilePath=QDir::currentPath()+"/dataServer.config";

QString OgmSetting::webDiagramIP="222.192.7.74";
QString OgmSetting::webDiagramPath=QDir::currentPath()+"/web/ui/flowChartModelInfopage.html";

OgmSetting::OgmSetting()
{

}
