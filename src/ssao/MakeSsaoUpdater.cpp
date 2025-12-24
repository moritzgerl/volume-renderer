#include <ssao/MakeSsaoUpdater.h>

#include <storage/Storage.h>

SsaoUpdater Factory::MakeSsaoUpdater(Storage& storage)
{
    return SsaoUpdater {
        storage.GetGuiUpdateFlags(),
        storage.GetGuiParameters(),
        storage.GetSsaoKernel(),
        storage.GetTexture(TextureId::SsaoNoise),
        storage.GetShader(ShaderId::Ssao),
        storage.GetShader(ShaderId::SsaoFinal)
	};
}
