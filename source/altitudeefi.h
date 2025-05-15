#ifndef ALTITUDEEFI_H
#define ALTITUDEEFI_H

#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QMesh>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QPhongAlphaMaterial>
#include <Qt3DExtras/QForwardRenderer>
#include <QHBoxLayout>
#include <Qt3DExtras/QText2DEntity>
#include <Qt3DLogic/QFrameAction>
#include <Qt3DRender/QDepthTest>
#include <Qt3DRender/QRenderPass>
#include <Qt3DRender/QTechnique>

class AltitudeEFI : public Qt3DExtras::Qt3DWindow
{
public:
    AltitudeEFI();
    ~AltitudeEFI();

private:
    Qt3DCore::QEntity *rootEntity;
    Qt3DExtras::QOrbitCameraController *camController;
    Qt3DCore::QEntity *planeEntity;
    Qt3DRender::QMesh *planeMesh;
    Qt3DExtras::QPhongMaterial *planeMaterial;
    Qt3DCore::QTransform *planeTransform;

    void CreateGlobalGround();
    void CreateAltitudeAxis();

public slots:
    void SetPlaneAltitude(float altitude);
    void SetPlaneEFI(float EFI);
};

#endif // ALTITUDEEFI_H
