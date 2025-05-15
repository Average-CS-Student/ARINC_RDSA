#include "altitudeefi.h"

AltitudeEFI::AltitudeEFI() {
    rootEntity = new Qt3DCore::QEntity();

    this->camera()->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    this->camera()->setPosition(QVector3D(40, 0, 0.0f));
    this->camera()->setViewCenter(QVector3D(0, 0, 0));

    camController = new Qt3DExtras::QOrbitCameraController(rootEntity);
    camController->setCamera(this->camera());
    camController->setLookSpeed(100);
    camController->setEnabled(false);

    planeEntity = new Qt3DCore::QEntity(rootEntity);

    planeMesh = new Qt3DRender::QMesh();
    planeMesh->setSource(QUrl::fromLocalFile("C:\\Users\\arrte\\Downloads\\Airplane\\A320_2112.obj"));
    planeEntity->addComponent(planeMesh);

    planeMaterial = new Qt3DExtras::QPhongMaterial();
    planeMaterial->setAmbient(QColor(QRgb(0xffffff)));
    planeEntity->addComponent(planeMaterial);

    planeTransform = new Qt3DCore::QTransform();
    planeTransform->setTranslation(QVector3D(0, -9, 0));
    planeTransform->setScale(0.05);
    planeEntity->addComponent(planeTransform);

    setRootEntity(rootEntity);

    CreateGlobalGround();
    CreateAltitudeAxis();

    this->defaultFrameGraph()->setClearColor(QColor(QRgb(0x2D2D2D)));
}

AltitudeEFI::~AltitudeEFI() {
    delete rootEntity;
}

void AltitudeEFI::CreateGlobalGround() {
    float Width = 1000.0f, Height = 1000.0f;

    Qt3DCore::QEntity *ground = new Qt3DCore::QEntity(rootEntity);
    Qt3DExtras::QPlaneMesh *groundMesh = new Qt3DExtras::QPlaneMesh();
    groundMesh->setHeight(Height);
    groundMesh->setWidth(Width);
    ground->addComponent(groundMesh);

    Qt3DExtras::QPhongMaterial *groundMaterial = new Qt3DExtras::QPhongMaterial();
    groundMaterial->setDiffuse(QColor(QRgb(0x117c13)));
    ground->addComponent(groundMaterial);

    Qt3DCore::QTransform *groundTransform = new Qt3DCore::QTransform();
    //groundTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), 90.0f));
    groundTransform->setTranslation(QVector3D(0, -10, 0));
    ground->addComponent(groundTransform);
}

void AltitudeEFI::CreateAltitudeAxis() {
    float Thickness = 2.0f, Length = 2000.0f, Transperency = 0.6f;

    Qt3DCore::QEntity *xAxis = new Qt3DCore::QEntity(planeEntity);
    Qt3DExtras::QCylinderMesh *xMesh = new Qt3DExtras::QCylinderMesh();
    xMesh->setRadius(Thickness);
    xMesh->setLength(Length);
    xAxis->addComponent(xMesh);

    //Qt3DExtras::QPhongAlphaMaterial *xMaterial = new Qt3DExtras::QPhongAlphaMaterial();
    Qt3DExtras::QPhongMaterial *xMaterial = new Qt3DExtras::QPhongMaterial();
    xMaterial->setDiffuse(Qt::red);
    //xMaterial->setAlpha(Transperency);
    xAxis->addComponent(xMaterial);

    Qt3DCore::QTransform *xTransform = new Qt3DCore::QTransform();
    xTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), 90.0f));
    xTransform->setTranslation(QVector3D(0, -Length / 2, 0));
    xAxis->addComponent(xTransform);
}

void AltitudeEFI::SetPlaneAltitude(float altitude) {
    // map 0 to 131072 -> -9 to +9
    planeTransform->setTranslation(QVector3D(0, altitude / 131072 * 18 - 9, 0));
}

void AltitudeEFI::SetPlaneEFI(float EFI) {
    //
}
