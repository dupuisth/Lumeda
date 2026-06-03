#include <Lumeda/Core/Transform.h>
#include <Lumeda/Node/Node.h>
#include <gtest/gtest.h>

#define ABS_ERROR 0.0001
#define EXPECT_VEC3_EQ(veca, vecb)                                                                                                                   \
    EXPECT_NEAR((veca).x, (vecb).x, ABS_ERROR);                                                                                                      \
    EXPECT_NEAR((veca).y, (vecb).y, ABS_ERROR);                                                                                                      \
    EXPECT_NEAR((veca).z, (vecb).z, ABS_ERROR)
#define ASSERT_VEC3_EQ(veca, vecb)                                                                                                                   \
    ASSERT_NEAR((veca).x, (vecb).x, ABS_ERROR);                                                                                                      \
    ASSERT_NEAR((veca).y, (vecb).y, ABS_ERROR);                                                                                                      \
    ASSERT_NEAR((veca).z, (vecb).z, ABS_ERROR)

#define EXPECT_QUAT_EQ(qa, qb)                                                                                                                       \
    EXPECT_NEAR((qa).w, (qb).w, ABS_ERROR);                                                                                                          \
    EXPECT_NEAR((qa).x, (qb).x, ABS_ERROR);                                                                                                          \
    EXPECT_NEAR((qa).y, (qb).y, ABS_ERROR);                                                                                                          \
    EXPECT_NEAR((qa).z, (qb).z, ABS_ERROR)
#define ASSERT_QUAT_EQ(qa, qb)                                                                                                                       \
    ASSERT_NEAR((qa).w, (qb).w, ABS_ERROR);                                                                                                          \
    ASSERT_NEAR((qa).x, (qb).x, ABS_ERROR);                                                                                                          \
    ASSERT_NEAR((qa).y, (qb).y, ABS_ERROR);                                                                                                          \
    ASSERT_NEAR((qa).z, (qb).z, ABS_ERROR)

namespace
{
TEST(TransformTest, Basic)
{
    Lumeda::Transform transform;

    transform.SetLocalPosition(glm::vec3(0.0f));
    transform.SetLocalRotationEulerAngles(glm::vec3(0.0f));
    transform.SetLocalScale(glm::vec3(1.0f));

    EXPECT_VEC3_EQ(transform.GetPosition(), glm::vec3(0.0f));
    EXPECT_VEC3_EQ(transform.GetRotationEulerAngles(), glm::vec3(0.0f));
    EXPECT_VEC3_EQ(transform.GetScale(), glm::vec3(1.0f));

    EXPECT_VEC3_EQ(transform.GetForward(), glm::vec3(0.0f, 0.0f, 1.0f));
    EXPECT_VEC3_EQ(transform.GetRight(), glm::vec3(1.0f, 0.0f, 0.0f));
    EXPECT_VEC3_EQ(transform.GetUp(), glm::vec3(0.0f, 1.0f, 0.0f));
}

TEST(TransformTest, OrphanRotationXDirectionTest)
{
    Lumeda::Transform transform;

    // X by 90°
    transform.SetLocalPosition(glm::vec3(0.0f));
    transform.SetLocalRotationEulerAngles(glm::vec3(90.0f, 0.0f, 0.0f));
    transform.SetLocalScale(glm::vec3(1.0f));
    EXPECT_VEC3_EQ(transform.GetForward(), glm::vec3(0.0f, -1.0f, 0.0f));
    EXPECT_VEC3_EQ(transform.GetRight(), glm::vec3(1.0f, 0.0f, 0.0f));
    EXPECT_VEC3_EQ(transform.GetUp(), glm::vec3(0.0f, 0.0f, 1.0f));

    // X by 180°
    transform.SetLocalPosition(glm::vec3(0.0f));
    transform.SetLocalRotationEulerAngles(glm::vec3(180.0f, 0.0f, 0.0f));
    transform.SetLocalScale(glm::vec3(1.0f));
    EXPECT_VEC3_EQ(transform.GetForward(), glm::vec3(0.0f, 0.0f, -1.0f));
    EXPECT_VEC3_EQ(transform.GetRight(), glm::vec3(1.0f, 0.0f, 0.0f));
    EXPECT_VEC3_EQ(transform.GetUp(), glm::vec3(0.0f, -1.0f, 0.0f));

    // X by 360°
    transform.SetLocalPosition(glm::vec3(0.0f));
    transform.SetLocalRotationEulerAngles(glm::vec3(360.0f, 0.0f, 0.0f));
    transform.SetLocalScale(glm::vec3(1.0f));
    EXPECT_VEC3_EQ(transform.GetForward(), glm::vec3(0.0f, 0.0f, 1.0f));
    EXPECT_VEC3_EQ(transform.GetRight(), glm::vec3(1.0f, 0.0f, 0.0f));
    EXPECT_VEC3_EQ(transform.GetUp(), glm::vec3(0.0f, 1.0f, 0.0f));
}

TEST(TransformTest, OrphanRotationYDirectionTest)
{
    Lumeda::Transform transform;

    // Y by 90°
    transform.SetLocalPosition(glm::vec3(0.0f));
    transform.SetLocalRotationEulerAngles(glm::vec3(0.0f, 90.0f, 0.0f));
    transform.SetLocalScale(glm::vec3(1.0f));
    EXPECT_VEC3_EQ(transform.GetForward(), glm::vec3(1.0f, 0.0f, 0.0f));
    EXPECT_VEC3_EQ(transform.GetRight(), glm::vec3(0.0f, 0.0f, -1.0f));
    EXPECT_VEC3_EQ(transform.GetUp(), glm::vec3(0.0f, 1.0f, 0.0f));

    // Y by 180°
    transform.SetLocalPosition(glm::vec3(0.0f));
    transform.SetLocalRotationEulerAngles(glm::vec3(0.0f, 180.0f, 0.0f));
    transform.SetLocalScale(glm::vec3(1.0f));
    EXPECT_VEC3_EQ(transform.GetForward(), glm::vec3(0.0f, 0.0f, -1.0f));
    EXPECT_VEC3_EQ(transform.GetRight(), glm::vec3(-1.0f, 0.0f, 0.0f));
    EXPECT_VEC3_EQ(transform.GetUp(), glm::vec3(0.0f, 1.0f, 0.0f));

    // Y by 360°
    transform.SetLocalPosition(glm::vec3(0.0f));
    transform.SetLocalRotationEulerAngles(glm::vec3(0.0f, 360.0f, 0.0f));
    transform.SetLocalScale(glm::vec3(1.0f));
    EXPECT_VEC3_EQ(transform.GetForward(), glm::vec3(0.0f, 0.0f, 1.0f));
    EXPECT_VEC3_EQ(transform.GetRight(), glm::vec3(1.0f, 0.0f, 0.0f));
    EXPECT_VEC3_EQ(transform.GetUp(), glm::vec3(0.0f, 1.0f, 0.0f));
}

TEST(TransformTest, OrphanRotationZDirectionTest)
{
    Lumeda::Transform transform;

    // Z by 90°
    transform.SetLocalPosition(glm::vec3(0.0f));
    transform.SetLocalRotationEulerAngles(glm::vec3(0.0f, 0.0f, 90.0f));
    transform.SetLocalScale(glm::vec3(1.0f));
    EXPECT_VEC3_EQ(transform.GetForward(), glm::vec3(0.0f, 0.0f, 1.0f));
    EXPECT_VEC3_EQ(transform.GetRight(), glm::vec3(0.0f, 1.0f, 0.0f));
    EXPECT_VEC3_EQ(transform.GetUp(), glm::vec3(-1.0f, 0.0f, 0.0f));

    // Z by 180°
    transform.SetLocalPosition(glm::vec3(0.0f));
    transform.SetLocalRotationEulerAngles(glm::vec3(0.0f, 0.0f, 180.0f));
    transform.SetLocalScale(glm::vec3(1.0f));
    EXPECT_VEC3_EQ(transform.GetForward(), glm::vec3(0.0f, 0.0f, 1.0f));
    EXPECT_VEC3_EQ(transform.GetRight(), glm::vec3(-1.0f, 0.0f, 0.0f));
    EXPECT_VEC3_EQ(transform.GetUp(), glm::vec3(0.0f, -1.0f, 0.0f));

    // Z by 360°
    transform.SetLocalPosition(glm::vec3(0.0f));
    transform.SetLocalRotationEulerAngles(glm::vec3(0.0f, 0.0f, 360.0f));
    transform.SetLocalScale(glm::vec3(1.0f));
    EXPECT_VEC3_EQ(transform.GetForward(), glm::vec3(0.0f, 0.0f, 1.0f));
    EXPECT_VEC3_EQ(transform.GetRight(), glm::vec3(1.0f, 0.0f, 0.0f));
    EXPECT_VEC3_EQ(transform.GetUp(), glm::vec3(0.0f, 1.0f, 0.0f));
}

TEST(TransformTest, GlobalPositionWithoutRotationTest)
{
    Lumeda::Node* parentNode = LUMEDA_NEW(Lumeda::Node);
    Lumeda::Node* childNode = LUMEDA_NEW(Lumeda::Node);

    parentNode->AddChild(childNode);
    parentNode->ProcessLifecycle();

    parentNode->GetTransform().SetLocalPosition(glm::vec3(5.0f, 0.0f, 0.0f));
    childNode->GetTransform().SetLocalPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    ASSERT_VEC3_EQ(childNode->GetTransform().GetPosition(), glm::vec3(5.0f, 0.0f, 0.0f));

    parentNode->GetTransform().SetLocalPosition(glm::vec3(5.0f, 15.0f, 2.0f));
    childNode->GetTransform().SetLocalPosition(glm::vec3(50.0f, -10.0f, 8.5f));
    ASSERT_VEC3_EQ(childNode->GetTransform().GetPosition(), glm::vec3(55.0f, 5.0f, 10.5f));

    parentNode->GetTransform().SetLocalPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    childNode->GetTransform().SetLocalPosition(glm::vec3(5.0f, 0.0f, 0.0f));
    ASSERT_VEC3_EQ(childNode->GetTransform().GetPosition(), glm::vec3(5.0f, 0.0f, 0.0f));

    LUMEDA_FREE(parentNode);
    LUMEDA_FREE(childNode);
}

TEST(TransformTest, GlobalPositionWithXRotationTest)
{
    Lumeda::Node* parentNode = LUMEDA_NEW(Lumeda::Node);
    Lumeda::Node* childNode = LUMEDA_NEW(Lumeda::Node);

    parentNode->AddChild(childNode);
    parentNode->ProcessLifecycle();

    parentNode->GetTransform().SetLocalPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    parentNode->GetTransform().SetLocalRotationEulerAngles(glm::vec3(90.0f, 0.0f, 0.0f));
    childNode->GetTransform().SetLocalPosition(glm::vec3(10.0f, 15.0f, 5.0f));
    ASSERT_VEC3_EQ(childNode->GetTransform().GetPosition(), glm::vec3(10.0f, -5.0f, 15.0f));

    LUMEDA_FREE(parentNode);
    LUMEDA_FREE(childNode);
}

TEST(TransformTest, GlobalPositionWithYRotationTest)
{
    Lumeda::Node* parentNode = LUMEDA_NEW(Lumeda::Node);
    Lumeda::Node* childNode = LUMEDA_NEW(Lumeda::Node);

    parentNode->AddChild(childNode);
    parentNode->ProcessLifecycle();

    parentNode->GetTransform().SetLocalPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    parentNode->GetTransform().SetLocalRotationEulerAngles(glm::vec3(0.0f, 90.0f, 0.0f));
    childNode->GetTransform().SetLocalPosition(glm::vec3(5.0f, 10.0f, 15.0f));
    ASSERT_VEC3_EQ(childNode->GetTransform().GetPosition(), glm::vec3(15.0f, 10.0f, -5.0f));

    LUMEDA_FREE(parentNode);
    LUMEDA_FREE(childNode);
}

TEST(TransformTest, GlobalPositionWithZRotationTest)
{
    Lumeda::Node* parentNode = LUMEDA_NEW(Lumeda::Node);
    Lumeda::Node* childNode = LUMEDA_NEW(Lumeda::Node);

    parentNode->AddChild(childNode);
    parentNode->ProcessLifecycle();

    parentNode->GetTransform().SetLocalPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    parentNode->GetTransform().SetLocalRotationEulerAngles(glm::vec3(0.0f, 0.0f, 90.0f));
    childNode->GetTransform().SetLocalPosition(glm::vec3(5.0f, 10.0f, 15.0f));
    ASSERT_VEC3_EQ(childNode->GetTransform().GetPosition(), glm::vec3(-10.0f, 5.0f, 15.0f));

    LUMEDA_FREE(parentNode);
    LUMEDA_FREE(childNode);
}

TEST(TransformTest, GlobalRotationTest)
{
    Lumeda::Node* parentNode = LUMEDA_NEW(Lumeda::Node);
    Lumeda::Node* childNode = LUMEDA_NEW(Lumeda::Node);

    parentNode->AddChild(childNode);
    parentNode->ProcessLifecycle();

    glm::quat a = glm::quat(glm::radians(glm::vec3(45.0f, 45.0f, 45.0f)));
    glm::quat b = glm::quat(glm::radians(glm::vec3(10.0f, 20.0f, 30.0f)));
    glm::quat res = a * b;

    parentNode->GetTransform().SetLocalRotation(a);
    childNode->GetTransform().SetLocalRotation(b);

    ASSERT_QUAT_EQ(childNode->GetTransform().GetRotation(), res);

    LUMEDA_FREE(parentNode);
    LUMEDA_FREE(childNode);
}

TEST(TransformTest, GlobalScaleTest)
{
    Lumeda::Node* parentNode = LUMEDA_NEW(Lumeda::Node);
    Lumeda::Node* childNode = LUMEDA_NEW(Lumeda::Node);

    parentNode->AddChild(childNode);
    parentNode->ProcessLifecycle();

    parentNode->GetTransform().SetLocalScale(glm::vec3(2.0f, 3.0f, 4.0f));
    childNode->GetTransform().SetLocalScale(glm::vec3(5.0f, 6.0f, 7.0f));

    ASSERT_VEC3_EQ(childNode->GetTransform().GetScale(), glm::vec3(10.0f, 18.0f, 28.0f));

    LUMEDA_FREE(parentNode);
    LUMEDA_FREE(childNode);
}
} // namespace