#include "bodypryara.h"

BodyPRYARA::BodyPRYARA() {
    rootEntity = new Qt3DCore::QEntity();

    this->camera()->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    this->camera()->setPosition(QVector3D(0, 0, 25.0f));
    this->camera()->setViewCenter(QVector3D(0, 0, 0));

    camController = new Qt3DExtras::QOrbitCameraController(rootEntity);
    camController->setCamera(this->camera());
    camController->setLookSpeed(100);
    //camController->setpa(0.0f);

    planeEntity = new Qt3DCore::QEntity(rootEntity);

    planeMesh = new Qt3DRender::QMesh();
    planeMesh->setSource(QUrl::fromLocalFile("C:\\Users\\arrte\\Downloads\\Airplane\\A320_2112.obj"));
    planeEntity->addComponent(planeMesh);

    planeMaterial = new Qt3DExtras::QPhongMaterial();
    planeMaterial->setAmbient(QColor(QRgb(0xffffff)));
    planeEntity->addComponent(planeMaterial);

    planeTransform = new Qt3DCore::QTransform();
    planeTransform->setTranslation(QVector3D(0, 0, 0));
    planeTransform->setScale(0.05);
    planeEntity->addComponent(planeTransform);

    setRootEntity(rootEntity);

    CreateGlobalAxes();
    CreatePlaneAxes();

    this->defaultFrameGraph()->setClearColor(QColor(QRgb(0x2D2D2D)));

    // labels
    //xLabel = CreateLabelEntity("X: 0°", QVector3D(-5, 5, 4.9f), &xLabelText);
    //yLabel = CreateLabelEntity("Y: 0°", QVector3D(-5, 3, 4.9f), &yLabelText);
    //zLabel = CreateLabelEntity("Z: 0°", QVector3D(-5, 1, 4.9f), &zLabelText);

    //frameAction = new Qt3DLogic::QFrameAction();
    //connect(frameAction, &Qt3DLogic::QFrameAction::triggered, this, &BodyPRYARA::UpdateLabels);
    //rootEntity->addComponent(frameAction);
}

BodyPRYARA::~BodyPRYARA() {
    //delete xLabel;
    //delete yLabel;
    //delete zLabel;
    delete AoATransform;
    delete AoSTransform;
    delete planeTransform;
    delete planeMaterial;
    delete planeMesh;
    delete planeEntity;
    delete camController;
    delete rootEntity;

    //xLabel = nullptr;
    //yLabel = nullptr;
    //zLabel = nullptr;

    // TODO: Axes creates 6 variables that are not released, should be 7 total
}

void BodyPRYARA::SetPlanePitch(float degrees) {
    planeTransform->setRotationX(-degrees);
}

void BodyPRYARA::SetPlaneRoll(float degrees) {
    planeTransform->setRotationZ(degrees);
}

void BodyPRYARA::SetPlaneAoA(float degrees) {
    AoATransform->setRotationX(degrees - 90);
}

void BodyPRYARA::SetPlaneAoS(float degrees) {
    AoATransform->setRotationY(degrees);
}

void BodyPRYARA::CreateGlobalAxes() {
    float Length = 100.0f, Thickness = 0.1f, Transperency = 0.2f;

    // X-axis (Red)
    Qt3DCore::QEntity *xAxis = new Qt3DCore::QEntity(rootEntity);
    Qt3DExtras::QCylinderMesh *xMesh = new Qt3DExtras::QCylinderMesh();
    xMesh->setRadius(Thickness);
    xMesh->setLength(Length);
    xAxis->addComponent(xMesh);

    Qt3DExtras::QPhongAlphaMaterial *xMaterial = new Qt3DExtras::QPhongAlphaMaterial();
    xMaterial->setDiffuse(Qt::red);
    xMaterial->setAlpha(Transperency);
    xAxis->addComponent(xMaterial);

    Qt3DCore::QTransform *xTransform = new Qt3DCore::QTransform();
    xTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), 90.0f));
    xAxis->addComponent(xTransform);

    // Y-axis (Green)
    Qt3DCore::QEntity *yAxis = new Qt3DCore::QEntity(rootEntity);
    Qt3DExtras::QCylinderMesh *yMesh = new Qt3DExtras::QCylinderMesh();
    yMesh->setRadius(Thickness);
    yMesh->setLength(Length);
    yAxis->addComponent(yMesh);

    Qt3DExtras::QPhongAlphaMaterial *yMaterial = new Qt3DExtras::QPhongAlphaMaterial();
    yMaterial->setDiffuse(Qt::green);
    yMaterial->setAlpha(Transperency);
    yAxis->addComponent(yMaterial);

    Qt3DCore::QTransform *yTransform = new Qt3DCore::QTransform();
    yTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), -90.0f));
    yAxis->addComponent(yTransform);

    // Z-axis (Blue)
    Qt3DCore::QEntity *zAxis = new Qt3DCore::QEntity(rootEntity);
    Qt3DExtras::QCylinderMesh *zMesh = new Qt3DExtras::QCylinderMesh();
    zMesh->setRadius(Thickness);
    zMesh->setLength(Length);
    zAxis->addComponent(zMesh);

    Qt3DExtras::QPhongAlphaMaterial *zMaterial = new Qt3DExtras::QPhongAlphaMaterial();
    zMaterial->setDiffuse(Qt::blue);
    zMaterial->setAlpha(Transperency);
    zAxis->addComponent(zMaterial);

    Qt3DCore::QTransform *zTransform = new Qt3DCore::QTransform();
    zTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0, 0, 1), -90.0f));
    zAxis->addComponent(zTransform);
}

void BodyPRYARA::CreatePlaneAxes() {

    float Length = 2000.0f, Thickness = 2.0f, Transperency = 0.5f;

    Qt3DCore::QEntity *xAxis = new Qt3DCore::QEntity(planeEntity);
    Qt3DCore::QEntity *yAxis = new Qt3DCore::QEntity(planeEntity);
    Qt3DCore::QEntity *zAxis = new Qt3DCore::QEntity(planeEntity);
    Qt3DCore::QEntity *AoA = new Qt3DCore::QEntity(planeEntity);
    Qt3DCore::QEntity *AoS = new Qt3DCore::QEntity(planeEntity);

    // Y-axis (Red)
    Qt3DExtras::QCylinderMesh *xMesh = new Qt3DExtras::QCylinderMesh();
    xMesh->setRadius(Thickness);
    xMesh->setLength(Length);
    xAxis->addComponent(xMesh);

    Qt3DExtras::QPhongAlphaMaterial *xMaterial = new Qt3DExtras::QPhongAlphaMaterial();
    xMaterial->setDiffuse(Qt::red);
    xMaterial->setAlpha(Transperency);
    xAxis->addComponent(xMaterial);

    Qt3DCore::QTransform *xTransform = new Qt3DCore::QTransform();
    xTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), 90.0f));
    xAxis->addComponent(xTransform);

    // Z-axis (Green)
    Qt3DExtras::QCylinderMesh *yMesh = new Qt3DExtras::QCylinderMesh();
    yMesh->setRadius(Thickness);
    yMesh->setLength(Length);
    yAxis->addComponent(yMesh);

    Qt3DExtras::QPhongAlphaMaterial *yMaterial = new Qt3DExtras::QPhongAlphaMaterial();
    yMaterial->setDiffuse(Qt::green);
    yMaterial->setAlpha(Transperency);
    yAxis->addComponent(yMaterial);

    Qt3DCore::QTransform *yTransform = new Qt3DCore::QTransform();
    yTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), -90.0f));
    yAxis->addComponent(yTransform);

    // X-axis (Blue)
    Qt3DExtras::QCylinderMesh *zMesh = new Qt3DExtras::QCylinderMesh();
    zMesh->setRadius(Thickness);
    zMesh->setLength(Length);
    zAxis->addComponent(zMesh);

    Qt3DExtras::QPhongAlphaMaterial *zMaterial = new Qt3DExtras::QPhongAlphaMaterial();
    zMaterial->setDiffuse(Qt::blue);
    zMaterial->setAlpha(Transperency);
    zAxis->addComponent(zMaterial);

    Qt3DCore::QTransform *zTransform = new Qt3DCore::QTransform();
    zTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0, 0, 1), -90.0f));
    zAxis->addComponent(zTransform);

    // AoA
    Qt3DExtras::QCylinderMesh *AoAMesh = new Qt3DExtras::QCylinderMesh();
    AoAMesh->setRadius(Thickness / 2);
    AoAMesh->setLength(Length / 2);
    AoA->addComponent(AoAMesh);

    Qt3DExtras::QPhongAlphaMaterial *AoAMaterial = new Qt3DExtras::QPhongAlphaMaterial();
    AoAMaterial->setDiffuse(Qt::magenta);
    AoAMaterial->setAlpha(Transperency);
    AoA->addComponent(AoAMaterial);

    AoATransform = new Qt3DCore::QTransform();
    AoATransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), -90.0f));
    AoATransform->setTranslation(QVector3D(130, 16, -26));
    AoA->addComponent(AoATransform);

    // AoS
    Qt3DExtras::QCylinderMesh *AoSMesh = new Qt3DExtras::QCylinderMesh();
    AoSMesh->setRadius(Thickness / 2);
    AoSMesh->setLength(Length / 2);
    AoS->addComponent(AoSMesh);

    Qt3DExtras::QPhongAlphaMaterial *AoSMaterial = new Qt3DExtras::QPhongAlphaMaterial();
    AoSMaterial->setDiffuse(QColor(QRgb(0xFFDE21)));
    AoSMaterial->setAlpha(Transperency);
    AoS->addComponent(AoSMaterial);

    AoSTransform = new Qt3DCore::QTransform();
    AoSTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), -90.0f));
    AoSTransform->setTranslation(QVector3D(0, 25, 0));
    AoS->addComponent(AoSTransform);
}

void BodyPRYARA::UpdateLabels(float dt) {
    //Q_UNUSED(dt);
    //auto rotation = planeTransform->rotation().toEulerAngles();
//
    //auto GetTextComponent = [](Qt3DCore::QEntity* label) -> Qt3DExtras::QText2DEntity* {
    //    auto components = label->componentsOfType<Qt3DExtras::QText2DEntity>();
    //    return components.isEmpty() ? nullptr : components.first();
    //};
//
    //if (auto xText = GetTextComponent(xLabel)) {
    //    xText->setText(QString("X: %1°").arg(rotation.x()));
    //}
    //if (auto yText = GetTextComponent(yLabel)) {
    //    yText->setText(QString("Y: %1°").arg(rotation.y()));
    //}
    //if (auto zText = GetTextComponent(zLabel)) {
    //    zText->setText(QString("Z: %1°").arg(rotation.z()));
    //}
}

Qt3DCore::QEntity* BodyPRYARA::CreateLabelEntity(const QString& text, const QVector3D& position, Qt3DExtras::QText2DEntity** textComponent) {
    Qt3DCore::QEntity* labelEntity = new Qt3DCore::QEntity(rootEntity);

    // Text component
    *textComponent = new Qt3DExtras::QText2DEntity(labelEntity);
    (*textComponent)->setText(text);
    (*textComponent)->setFont(QFont("Arial", 20, QFont::Bold));
    (*textComponent)->setColor(Qt::white);

    // Transform for positioning
    Qt3DCore::QTransform* transform = new Qt3DCore::QTransform();
    transform->setTranslation(position);
    labelEntity->addComponent(transform);

    // Custom material to disable depth testing
    Qt3DRender::QMaterial* material = new Qt3DRender::QMaterial(labelEntity);
    Qt3DRender::QEffect* effect = new Qt3DRender::QEffect();
    Qt3DRender::QTechnique* technique = new Qt3DRender::QTechnique();
    Qt3DRender::QRenderPass* renderPass = new Qt3DRender::QRenderPass();

    Qt3DRender::QDepthTest* depthTest = new Qt3DRender::QDepthTest();
    depthTest->setDepthFunction(Qt3DRender::QDepthTest::Always);  // Always render on top

    renderPass->addRenderState(depthTest);
    technique->addRenderPass(renderPass);
    effect->addTechnique(technique);
    material->setEffect(effect);

    labelEntity->addComponent(material);

    return labelEntity;
}
