#include "generator.hh"

PrimaryGenerator::PrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);
}

PrimaryGenerator::~PrimaryGenerator()
{
    delete fParticleGun;
}

void PrimaryGenerator::GeneratePrimaries(G4Event* event)
{
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName = "gamma";
    G4ParticleDefinition *particle = particleTable->FindParticle(particleName);

    G4ThreeVector position(0.0, 0.0, 0.0);
    G4ThreeVector momentum(0.0, 0.0, 1.0);

    fParticleGun->SetParticlePosition(position);
    fParticleGun->SetParticleMomentumDirection(momentum);
    fParticleGun->SetParticleMomentum(511*keV);
    fParticleGun->SetParticleDefinition(particle);

    fParticleGun->GeneratePrimaryVertex(event);
}