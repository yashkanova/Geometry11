
#include <G4PhysicalConstants.hh>
#include "DetGeometry.hh"

DetGeometry::DetGeometry() {
    world_sizeXYZ   = 50 * m;
    nist            = G4NistManager::Instance();
    world_mat       = nist->FindOrBuildMaterial("G4_AIR");
    solidWorld      = new G4Box("solWorld", 0.5*world_sizeXYZ, 0.5*world_sizeXYZ, 0.5*world_sizeXYZ);
    logicWorld      = new G4LogicalVolume(solidWorld, world_mat, "logWorld");
    physWorld       = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "phyWorld", 0, false, 0);

    G4cout<<"Geometry of detector is build successfully\t\t\t\t\t\tOK!!!"<<G4endl;
}

DetGeometry::~DetGeometry() {}

G4VPhysicalVolume* DetGeometry::Construct(){
    G4double box_size = 20 *mm; //20*20*20
    G4Material* box_mat = nist->FindOrBuildMaterial("G4_A-150_TISSUE");
    G4Box* test_box = new G4Box("my_box",0.5*box_size,0.5*box_size,box_size);

    G4LogicalVolume* test_box_log = new G4LogicalVolume(test_box,box_mat,"my_box_log");

    G4VPhysicalVolume* test_box_phys = new G4PVPlacement(0,G4ThreeVector(),test_box_log,"my_box_phys",logicWorld,false,0);
    G4RotationMatrix* rotm = new G4RotationMatrix(pi/4,pi/4,pi/4);

    G4VPhysicalVolume* test_box_phys_2 = new G4PVPlacement(rotm,G4ThreeVector(0,0,100*mm),test_box_log,"my_box_phys_2",logicWorld,false,0);

    return physWorld;
}


