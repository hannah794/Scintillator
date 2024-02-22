#include <iostream>

#include "G4RunManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4VModularPhysicsList.hh"
#include "QBBC.hh"
#include "G4StepLimiterPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4OpticalPhysics.hh"

#include "construction.hh"
#include "action.hh"
#include "generator.hh"

int main(int argc, char** argv)
{
    G4RunManager* runManager = new G4RunManager();
    runManager->SetUserInitialization(new DetectorConstruction());
    G4VModularPhysicsList* physicsList = new QBBC();
    physicsList->RegisterPhysics( new G4StepLimiterPhysics() );
    physicsList->RegisterPhysics( new G4RadioactiveDecayPhysics() ); // For the tracers
    physicsList->RegisterPhysics( new G4OpticalPhysics() ); // For optical photons
    runManager->SetUserInitialization( physicsList );

    runManager->SetUserInitialization(new ActionInitialization());
    runManager->Initialize();

    G4UIExecutive* ui = new G4UIExecutive(argc, argv);

    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

    G4UImanager* uiManager = G4UImanager::GetUIpointer();
    uiManager->ApplyCommand("/vis/open OGL");
    uiManager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
    uiManager->ApplyCommand("/vis/drawVolume");
    uiManager->ApplyCommand("/vis/viewer/set/autoRefresh true");
    uiManager->ApplyCommand("/vis/scene/add/trajectories smooth");

    ui->SessionStart();

    return 0;
}