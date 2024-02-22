#include "detector.hh"

SiPM::SiPM(G4String name) : G4VSensitiveDetector(name)
{

}

SiPM::~SiPM()
{

}

G4bool SiPM::ProcessHits(G4Step* step, G4TouchableHistory* ROhist)
{
    G4Track* track = step->GetTrack();

    //kill photons after they enter the SiPM
    track->SetTrackStatus(fStopAndKill);

    G4StepPoint* preStepPoint = step->GetPreStepPoint();
    G4StepPoint* postStepPoint = step->GetPostStepPoint();

    G4ThreeVector posPhoton = preStepPoint->GetPosition();
    // G4cout << "Photon position = " << posPhoton << G4endl;

    const G4VTouchable* touchable = step->GetPreStepPoint()->GetTouchable();
    G4int copyNo = touchable->GetCopyNumber();
    G4cout << "SiPM numer which registered the hit: " << copyNo << G4endl;

    G4VPhysicalVolume* vol = touchable->GetVolume();
    G4ThreeVector posSiPM = vol->GetTranslation();

    G4cout << "Position of SiPM that registered hit: " << posSiPM << G4endl;

}