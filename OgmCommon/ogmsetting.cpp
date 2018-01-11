#include "ogmsetting.h"

#include <QDir>

QString OgmSetting::defaultModelServerId="998e3675-d845-4826-a425-db01abc849fd";
QString OgmSetting::defaultDataServerId="f6d09c5b-7798-41e8-928e-c162c1e02009";
QString OgmSetting::defaultFavorId="fefab154-37e7-4c2b-a0f6-c7e7e8f7d8b2";

QString OgmSetting::udxDataPath=QDir::currentPath()+"/tool/UDX_Data/Vge_Tools_UDX_Data.exe";
QString OgmSetting::udxSchemaPath=QDir::currentPath()+"/tool/UDX_schema/Vge_Tools_UDX_schema.exe";
QString OgmSetting::omsToolPath=QDir::currentPath()+"/tool/OmsPacker/mainwindows.exe";

QString OgmSetting::modelServerFilePath=QDir::currentPath()+"/modelServer.config";
QString OgmSetting::dataServerFilePath=QDir::currentPath()+"/dataServer.config";

QString OgmSetting::webDiagramIP="222.192.7.74";
QString OgmSetting::webDiagramPath=QDir::currentPath()+"/web/ui/flowChartModelInfopage.html";
QString OgmSetting::webDiagramLayout=QDir::currentPath()+"/web/ui/layout.xml";

//QString OgmSetting::urlAggragationNewSolution="http://223.2.45.127:9990/aggregation/solution/new";
QString OgmSetting::urlAggragationNewSolution="http://223.2.45.127:9990/integration/solution/new";
QString OgmSetting::urlAggragationQuerySolution="http://223.2.45.127:9990/integration/solution/query";
QString OgmSetting::urlAggragationQueryTask="http://223.2.45.127:9990/integration/task/query";

QString OgmSetting::taskPath=QDir::currentPath()+"/task";
QString OgmSetting::visualPath=QDir::currentPath()+"/visual/services";

QString OgmSetting::dataServerUserName="admin";

OgmSetting::OgmSetting()
{

}
