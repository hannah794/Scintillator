#include "construction.hh"

DetectorConstruction::DetectorConstruction()
{

}

DetectorConstruction::~DetectorConstruction()
{

}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4NistManager* nistManager = G4NistManager::Instance();

    G4Material* Air = nistManager->FindOrBuildMaterial("G4_AIR");
    // Optical properties for the world volume, i.e. air
    G4MaterialPropertiesTable* MPT_Air = new G4MaterialPropertiesTable();
    MPT_Air->AddProperty("RINDEX", "Air");
    Air->SetMaterialPropertiesTable(MPT_Air);
    // std::cout << "Material properties table for Air:" << std::endl;
    MPT_Air->DumpTable();

    G4Element* O  = nistManager->FindOrBuildElement( "O" , false );
    G4Element* Si = nistManager->FindOrBuildElement( "Si", false );
    G4Element* Lu = nistManager->FindOrBuildElement( "Lu", false );
    G4Material* LSO = new G4Material( "Lu2SiO5", 7.4*g/cm3, 3 );
    LSO->AddElement( Lu, 2 );
    LSO->AddElement( Si, 1 );
    LSO->AddElement( O , 5 );
    //LSO optical properties
    G4MaterialPropertiesTable* MPT_LSO = new G4MaterialPropertiesTable();
    std::vector<G4double> photonEnergy = {2.07*eV, 3.26*eV}; // taken from emission spectrum and corresponds to wavelengths 380-600nm
    std::vector<G4double> rIndex = {1.82, 1.82}; // assuming that stable over different wavelengths
    std::vector<G4double> absLength = {1.15*cm, 1.15*cm}; //assuming that stable over different wavelengths
    std::vector<G4double> scintilFast = {1.00, 1.00}; 
    MPT_LSO->AddProperty("RINDEX", photonEnergy, rIndex);
    MPT_LSO->AddProperty("ABSLENGTH", photonEnergy, absLength);
    MPT_LSO->AddConstProperty("SCINTILLATIONYIELD",30./keV); //assuming that it is independent of the incident particle
    MPT_LSO->AddProperty("SCINTILLATIONCOMPONENT1",photonEnergy, scintilFast);
    MPT_LSO->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 40.*ns);
    MPT_LSO->AddConstProperty("RESOLUTIONSCALE",0.00); //variation of the number of photons produced at step, if 0 then no fluctuation
  
    LSO->SetMaterialPropertiesTable(MPT_LSO);
    std::cout << "Material properties table for LSO:" << std::endl;
    MPT_LSO->DumpTable();

    // define world 
    G4Box* worldSolid = new G4Box("worldSolid", 10*cm, 10*cm, 10*cm);

    G4LogicalVolume* worldLV = new G4LogicalVolume(worldSolid, Air, "worldLV");

    G4VPhysicalVolume* worldPV = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, 0.0), worldLV, "worldPV", 0, false, 0, true);

    //define crystal array 5x5
    G4float size_x = 3.2*mm;
    G4float size_y = 3.2*mm;
    G4float size_z = 20.*mm;

    G4int nReplicas_x = 5;
    G4int nReplicas_y = 5;

    G4Box* singleSolid = new G4Box("singleSolid", size_x/2, size_y/2, size_z/2);

    G4LogicalVolume* singleLV = new G4LogicalVolume(singleSolid, LSO, "singleLV");

    for(unsigned int i=0; i<nReplicas_x; i++){
        for(unsigned int j=0; j<nReplicas_y; j++){
            G4VPhysicalVolume* singlePV = new G4PVPlacement(0, G4ThreeVector(-1*size_x*(nReplicas_x-1)*0.5 + i*size_x, -1*size_y*(nReplicas_y-1)*0.5 + j*size_y, 2*cm), singleLV, "singlePV", worldLV, false, i+j/25, true);
        }
    }
    
    //define SiPM array 4x4
    G4float SiPM_size_x = 4.*mm;
    G4float SiPM_size_y = 4.*mm;
    G4float SiPM_size_z = 5.*mm;

    G4int SiPM_nReplicas_x = 4;
    G4int SiPM_nReplicas_y = 4;

    G4Box* singleSiPMSolid = new G4Box("singleSiPMSolid", SiPM_size_x/2, SiPM_size_y/2, SiPM_size_z/2);

    G4LogicalVolume* singleSiPMLV = new G4LogicalVolume(singleSiPMSolid, Air, "singleSiPMLV");

    for(unsigned int i=0; i<SiPM_nReplicas_x; i++){
        for(unsigned int j=0; j<SiPM_nReplicas_y; j++){
            G4VPhysicalVolume* singleSiPMPV = new G4PVPlacement(0, G4ThreeVector(-1*SiPM_size_x*(SiPM_nReplicas_x-1)*0.5 + i*SiPM_size_x, -1*SiPM_size_y*(SiPM_nReplicas_y-1)*0.5 + j*SiPM_size_y, 5*cm), singleSiPMLV, "singleSiPMPV", worldLV, false, i+j/16, true);
        }
    }

    return worldPV;
} 
