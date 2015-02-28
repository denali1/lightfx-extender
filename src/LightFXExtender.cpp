#ifndef LFXE_EXPORTS
#define LFXE_EXPORTS
#endif

#include "LightFXExtender.h"

// Project includes
#include "Managers/ConfigManager.h"
#include "Managers/DeviceManager.h"
#include "Managers/GameManager.h"
#include "Managers/LogManager.h"
#include "Managers/TrayManager.h"
#include "Managers/UpdateManager.h"
#include "Config/MainConfigFile.h"
#include "Utils/Windows.h"


using namespace std;
using namespace lightfx::config;
using namespace lightfx::managers;
using namespace lightfx::utils;

namespace lightfx {

    void LightFXExtender::Initialize() {
        shared_ptr<ConfigManager> configMgr = make_shared<ConfigManager>();
        shared_ptr<DeviceManager> deviceMgr = make_shared<DeviceManager>();
        shared_ptr<GameManager> gameMgr = make_shared<GameManager>();
        shared_ptr<LogManager> logMgr = make_shared<LogManager>();
        shared_ptr<TrayManager> trayMgr = make_shared<TrayManager>();
        shared_ptr<UpdateManager> updateMgr = make_shared<UpdateManager>();

        configMgr->SetLightFXExtender(shared_from_this());
        deviceMgr->SetLightFXExtender(shared_from_this());
        gameMgr->SetLightFXExtender(shared_from_this());
        logMgr->SetLightFXExtender(shared_from_this());
        trayMgr->SetLightFXExtender(shared_from_this());
        updateMgr->SetLightFXExtender(shared_from_this());

        this->configManager = configMgr;
        this->deviceManager = deviceMgr;
        this->gameManager = gameMgr;
        this->logManager = logMgr;
        this->trayManager = trayMgr;
        this->updateManager = updateMgr;
    }

    void LightFXExtender::Start() {
        this->logManager->Log(LogLevel::Info, L"Connected to " + GetProcessName());

        this->configManager->InitializeConfigs();
        this->updateManager->CheckAsync();
        this->deviceManager->InitializeDevices();
        this->gameManager->InitializeGames();
        this->trayManager->AddTrayIcon();
    }

    void LightFXExtender::Stop() {
        this->trayManager->RemoveTrayIcon();
        this->configManager->GetMainConfig()->Save();
        this->deviceManager->UninitializeDevices();
        this->gameManager->UninitializeGames();
    }

}
