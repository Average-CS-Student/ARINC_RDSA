#ifndef BODYPRYARA_H
#define BODYPRYARA_H

#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QMesh>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QPhongAlphaMaterial>
#include <Qt3DExtras/QForwardRenderer>
#include <QHBoxLayout>
#include <Qt3DExtras/QText2DEntity>
#include <Qt3DLogic/QFrameAction>
#include <Qt3DRender/QDepthTest>
#include <Qt3DRender/QRenderPass>
#include <Qt3DRender/QTechnique>

class BodyPRYARA : public Qt3DExtras::Qt3DWindow
{
public:
    BodyPRYARA();
    ~BodyPRYARA();

private:
    Qt3DCore::QEntity *rootEntity;
    //Qt3DRender::QCamera *camera;
    Qt3DExtras::QOrbitCameraController *camController;
    Qt3DCore::QEntity *planeEntity;
    Qt3DRender::QMesh *planeMesh;
    Qt3DExtras::QPhongMaterial *planeMaterial;
    Qt3DCore::QTransform *planeTransform;
    Qt3DCore::QTransform *AoATransform;
    Qt3DCore::QTransform *AoSTransform;

    void CreateGlobalAxes();
    void CreatePlaneAxes();

    //Qt3DExtras::QText2DEntity *xLabelText, *yLabelText, *zLabelText;
    //Qt3DCore::QEntity *xLabel, *yLabel, *zLabel;
    //Qt3DLogic::QFrameAction *frameAction;
    Qt3DCore::QEntity* CreateLabelEntity(const QString& text, const QVector3D& position, Qt3DExtras::QText2DEntity** textComponent);


public slots:
    void SetPlanePitch(float degrees);
    void SetPlaneRoll(float degrees);
    void SetPlaneAoA(float degrees);
    void SetPlaneAoS(float degrees);

private slots:
    void UpdateLabels(float dt);
};

#endif // BODYPRYARA_H
