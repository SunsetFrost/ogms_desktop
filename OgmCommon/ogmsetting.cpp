#include "ogmsetting.h"

#include <QDir>

QString OgmSetting::defaultModelServerId="0001";
QString OgmSetting::defaultDataServerId="1000";
QString OgmSetting::defaultFavorId="{fefab154-37e7-4c2b-a0f6-c7e7e8f7d8b2}";

QString OgmSetting::udxDataPath=QDir::currentPath()+"/tool/UDX_Data/Vge_Tools_UDX_Data.exe";
QString OgmSetting::udxSchemaPath=QDir::currentPath()+"/tool/UDX_schema/Vge_Tools_UDX_schema.exe";
QString OgmSetting::omsToolPath=QDir::currentPath()+"/tool/OmsPacker/mainwindows.exe";

QString OgmSetting::serverFilePath=QDir::currentPath()+"/server.config";

OgmSetting::OgmSetting()
{

}
