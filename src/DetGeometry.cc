//Вариант 1
//
//Реализовать геометрию со следующими параметрами:
//Расположить в плоскости XZ G4Cons G4Para и G4Tubs по вершинам вписанного в окружность равностороннего треугольника
//в плоскости Y фигуры должны распологаться одна над другой (начиная с G4Cons заканчивая G4Tubs)

#include <G4Tubs.hh>
#include <G4Cons.hh>
#include <G4Para.hh>
#include <G4PhysicalConstants.hh>
#include <G4Orb.hh>
#include "DetGeometry.hh"

DetGeometry::DetGeometry() {
    world_sizeXYZ = 50 * m;
    nist = G4NistManager::Instance();
    world_mat = nist->FindOrBuildMaterial("G4_AIR");
    solidWorld = new G4Box("solWorld", 0.5*world_sizeXYZ, 0.5*world_sizeXYZ, 0.5*world_sizeXYZ);
    logicWorld = new G4LogicalVolume(solidWorld, world_mat, "logWorld");
    physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "phyWorld", 0, false, 0);

    G4cout<<"Geometry of detector is build successfully\t\t\t\t\t\tOK!!!"<<G4endl;
}

DetGeometry::~DetGeometry() {}

G4VPhysicalVolume* DetGeometry::Construct(){
    G4Material* c_material = nist->FindOrBuildMaterial("G4_Fe");
    G4Material* p_material = nist->FindOrBuildMaterial("G4_ALANINE");
    G4Material* t_material = nist->FindOrBuildMaterial("G4_ANTHRACENE");

    G4Cons *a=new G4Cons("alena1",
                         5,
                         10,
                         20,
                         25,
                         40,
                         0,
                         4/3*pi);

    G4Para *b=new G4Para("alena2",
                         30,
                         40,
                         60,
                         0*360,
                         0*360,
                         0*360);

    G4Tubs *c=new G4Tubs ("alena3",
                          10,
                          15,
                          20,
                          0*deg,
                          360*deg);

    G4Orb*x=new G4Orb ("alena4",
                   20);

    G4LogicalVolume* d = new G4LogicalVolume(a, c_material, "alena1");
    G4LogicalVolume* e = new G4LogicalVolume(b, c_material, "alena2");
    G4LogicalVolume* f = new G4LogicalVolume(c, c_material, "alena3");
    G4LogicalVolume* y = new G4LogicalVolume(x, c_material, "alena4");

//G4VPhysicalVolume* g = new G4PVPlacement (0, G4ThreeVector( 1*m, 1*m,0), d, "phyWorld", logicWorld , false, 0);
// G4VPhysicalVolume* h = new G4PVPlacement (0, G4ThreeVector(1*m, 0,0), e, "phyWorld", logicWorld , false, 0);
// G4VPhysicalVolume* i = new G4PVPlacement (0, G4ThreeVector(-(1/2)*m, sqrt(3/4)*m,0),f, "phyWorld", logicWorld , false, 0);

    G4VPhysicalVolume* g = new G4PVPlacement (0, G4ThreeVector( 0, 1000,0), d, "phyWorld", logicWorld , false, 0);
    G4VPhysicalVolume* h = new G4PVPlacement (0, G4ThreeVector(800, -500,0), e, "phyWorld", logicWorld , false, 0);
    G4VPhysicalVolume* i = new G4PVPlacement (0, G4ThreeVector(-800, -500,0),f, "phyWorld", logicWorld , false, 0);
    G4VPhysicalVolume* z = new G4PVPlacement (0, G4ThreeVector(0,0,0),y, "phyWorld", logicWorld , false, 0);

    return physWorld;
}
