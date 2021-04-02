 
#include "LocalConfig.h"

LocalConfig::LocalConfig(Context* ctx)
{
	this->ctx = ctx;
}

LocalConfig::~LocalConfig()
{
}

bool LocalConfig::readConfig()
{
	bool flag = this->fsys.isFile(this->ctx->getConstants()->__LOCAL_CONFIG__.pLocalConfig);
	return flag;
}
