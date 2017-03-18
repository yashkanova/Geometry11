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
#include <G4Sphere.hh>
#include "DetGeometry.hh"
#include <G4VisAttributes.hh>

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

   G4Isotope* Br = new G4Isotope ("Br", 35,80, 79.8*g/mole );
    G4Isotope* La = new G4Isotope ("La", 57,139, 138,9*g/mole );
    G4Element* Br2 = new G4Element ("Br2","Br2" ,1 );
    G4Element* La2 = new G4Element ("La2","La2" ,1 );
    Br2->AddIsotope(Br, 100*perCent);
    La2->AddIsotope(La, 100*perCent);
    G4Material* LaBr3 = new G4Material ("LaBr3" , 5.053*g/cm3 ,2);
    LaBr3->AddElement(La2,0.25);
    LaBr3->AddElement(Br2,0.75);
    G4Orb *aa=new G4Orb("a1", 50);
    G4LogicalVolume* dd = new G4LogicalVolume(aa, LaBr3, "al");
    dd->SetVisAttributes(G4Color::Green());
    G4VPhysicalVolume* zz = new G4PVPlacement (0, G4ThreeVector(0,0,0),dd, "phyWorld", logicWorld , false, 0);


    G4Material* Br22 = nist->FindOrBuildMaterial("G4_Br");
    G4Material* La22 = nist->FindOrBuildMaterial("G4_La");
    G4Material* LaBr33 = new G4Material ("LaBr33" , 5.053*g/cm3 ,2);
    LaBr33->AddMaterial(La22,0.25);
    LaBr33->AddMaterial(Br22,0.75);
    G4Box *bb=new G4Box("a1e", 50,50,50);
    G4LogicalVolume* kk = new G4LogicalVolume(bb, LaBr33, "ale");
    kk->SetVisAttributes(G4Color::Blue());
    G4VPhysicalVolume* xx = new G4PVPlacement (0, G4ThreeVector(100,100,100),kk, "phyWorld", logicWorld , false, 0);


    G4Material* Fe = nist->FindOrBuildMaterial("G4_Fe");
    G4Material* Si = nist->FindOrBuildMaterial("G4_Si");
    G4Material* Mn = nist->FindOrBuildMaterial("G4_Mn");
    G4Material* Cr = nist->FindOrBuildMaterial("G4_Cr");
    G4Material* Ti = nist->FindOrBuildMaterial("G4_Ti");
    G4Material* Al = nist->FindOrBuildMaterial("G4_Al");
    G4Material* Cu = nist->FindOrBuildMaterial("G4_Cu");
    G4Material* Mg = nist->FindOrBuildMaterial("G4_Mg");
    G4Material* Zn = nist->FindOrBuildMaterial("G4_Fe");

    G4Material* AMG2 = new G4Material ("AMG2" , 7.11*g/cm3 ,9);
    AMG2->AddMaterial(Fe,0.005);
    AMG2->AddMaterial(Si,0.004);
    AMG2->AddMaterial(Mn,0.003);
    AMG2->AddMaterial(Cr,0.0005);
    AMG2->AddMaterial(Ti,0.0015);
    AMG2->AddMaterial(Al,0.963);
    AMG2->AddMaterial(Cu,0.0015);
    AMG2->AddMaterial(Mg,0.02);
    AMG2->AddMaterial(Zn,0.0015);
    G4Tubs *cc=new G4Tubs ("alen", 10, 15, 20, 0*deg, 360*deg);
    G4LogicalVolume* nn = new G4LogicalVolume(cc, AMG2, "alen");
    nn->SetVisAttributes(G4Color(1,0,2));
    G4VPhysicalVolume* yy = new G4PVPlacement (0, G4ThreeVector(-100,-100,-100),nn, "phyWorld", logicWorld , false, 0);


    return physWorld;
}


