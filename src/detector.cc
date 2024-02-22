#include "detector.hh"

SiPM::SiPM(G4String name) : G4VSensitiveDetector(name)
{

}

SiPM::~SiPM()
{

}

G4bool SiPM::ProcessHits(G4Step* step, G4TouchableHistory* ROhist)
{

}