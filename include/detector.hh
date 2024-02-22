#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "G4VSensitiveDetector.hh"

class SiPM : public G4VSensitiveDetector
{
    public:
        SiPM(G4String);
        ~SiPM();
    private:
        virtual G4bool ProcessHits(G4Step*, G4TouchableHistory*);
};

#endif