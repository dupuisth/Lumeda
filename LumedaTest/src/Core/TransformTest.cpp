#include <gtest/gtest.h>

#include <Lumeda/Core/Transform.h>

#define ABS_ERROR 0.000001
#define EXPECT_VEC3_EQ(veca, vecb) \
    EXPECT_NEAR((veca).x, (vecb).x, ABS_ERROR); \
    EXPECT_NEAR((veca).y, (vecb).y, ABS_ERROR); \
    EXPECT_NEAR((veca).z, (vecb).z, ABS_ERROR)

namespace
{
    TEST(TransformTest, Basic)
    {
        Lumeda::Transform transform;

        transform.SetPosition(glm::vec3(0.0f));
        transform.SetRotation(glm::vec3(0.0f));
        transform.SetScale(glm::vec3(1.0f));

        EXPECT_VEC3_EQ(transform.GetPosition(), glm::vec3(0.0f));
        EXPECT_VEC3_EQ(transform.GetRotation(), glm::vec3(0.0f));
        EXPECT_VEC3_EQ(transform.GetScale(), glm::vec3(1.0f));

        EXPECT_VEC3_EQ(transform.GetForward(), glm::vec3(0.0f, 0.0f, 1.0f));
        EXPECT_VEC3_EQ(transform.GetRight(), glm::vec3(1.0f, 0.0f, 0.0f));
        EXPECT_VEC3_EQ(transform.GetUp(), glm::vec3(0.0f, 1.0f, 0.0f));
    }

    TEST(TransformTest, Directions)
    {
        Lumeda::Transform transform;

        // Default
        transform.SetPosition(glm::vec3(0.0f));
        transform.SetRotation(glm::vec3(0.0f));
        transform.SetScale(glm::vec3(1.0f));
        EXPECT_VEC3_EQ(transform.GetForward(), glm::vec3(0.0f, 0.0f, 1.0f));
        EXPECT_VEC3_EQ(transform.GetRight(), glm::vec3(1.0f, 0.0f, 0.0f));
        EXPECT_VEC3_EQ(transform.GetUp(), glm::vec3(0.0f, 1.0f, 0.0f));

        // Y by 90°
        transform.SetPosition(glm::vec3(0.0f));
        transform.SetRotation(glm::vec3(0.0f, 90.0f, 0.0f));
        transform.SetScale(glm::vec3(1.0f));
        EXPECT_VEC3_EQ(transform.GetForward(), glm::vec3(-1.0f, 0.0f, 0.0f));
        EXPECT_VEC3_EQ(transform.GetRight(), glm::vec3(0.0f, 0.0f, -1.0f));
        EXPECT_VEC3_EQ(transform.GetUp(), glm::vec3(0.0f, 1.0f, 0.0f));

        // Y by 180°
        transform.SetPosition(glm::vec3(0.0f));
        transform.SetRotation(glm::vec3(0.0f, 180.0f, 0.0f));
        transform.SetScale(glm::vec3(1.0f));
        EXPECT_VEC3_EQ(transform.GetForward(), glm::vec3(0.0f, 0.0f, -1.0f));
        EXPECT_VEC3_EQ(transform.GetRight(), glm::vec3(-1.0f, 0.0f, 0.0f));
        EXPECT_VEC3_EQ(transform.GetUp(), glm::vec3(0.0f, 1.0f, 0.0f));

        // Y by 360°
        transform.SetPosition(glm::vec3(0.0f));
        transform.SetRotation(glm::vec3(0.0f, 360.0f, 0.0f));
        transform.SetScale(glm::vec3(1.0f));
        EXPECT_VEC3_EQ(transform.GetForward(), glm::vec3(0.0f, 0.0f, 1.0f));
        EXPECT_VEC3_EQ(transform.GetRight(), glm::vec3(1.0f, 0.0f, 0.0f));
        EXPECT_VEC3_EQ(transform.GetUp(), glm::vec3(0.0f, 1.0f, 0.0f));


        // X by 90°
        transform.SetPosition(glm::vec3(0.0f));
        transform.SetRotation(glm::vec3(90.0f, 0.0f, 0.0f));
        transform.SetScale(glm::vec3(1.0f));
        EXPECT_VEC3_EQ(transform.GetForward(), glm::vec3(0.0f, 1.0f, 0.0f));
        EXPECT_VEC3_EQ(transform.GetRight(), glm::vec3(1.0f, 0.0f, 0.0f));
        EXPECT_VEC3_EQ(transform.GetUp(), glm::vec3(0.0f, 0.0f, -1.0f));

        // X by 180°
        transform.SetPosition(glm::vec3(0.0f));
        transform.SetRotation(glm::vec3(180.0f, 0.0f, 0.0f));
        transform.SetScale(glm::vec3(1.0f));
        EXPECT_VEC3_EQ(transform.GetForward(), glm::vec3(0.0f, 0.0f, -1.0f));
        EXPECT_VEC3_EQ(transform.GetRight(), glm::vec3(1.0f, 0.0f, 0.0f));
        EXPECT_VEC3_EQ(transform.GetUp(), glm::vec3(0.0f, -1.0f, 0.0f));

        // X by 360°
        transform.SetPosition(glm::vec3(0.0f));
        transform.SetRotation(glm::vec3(360.0f, 0.0f, 0.0f));
        transform.SetScale(glm::vec3(1.0f));
        EXPECT_VEC3_EQ(transform.GetForward(), glm::vec3(0.0f, 0.0f, 1.0f));
        EXPECT_VEC3_EQ(transform.GetRight(), glm::vec3(1.0f, 0.0f, 0.0f));
        EXPECT_VEC3_EQ(transform.GetUp(), glm::vec3(0.0f, 1.0f, 0.0f));

        // Z by 90°
        transform.SetPosition(glm::vec3(0.0f));
        transform.SetRotation(glm::vec3(0.0f, 0.0f, 90.0f));
        transform.SetScale(glm::vec3(1.0f));
        EXPECT_VEC3_EQ(transform.GetForward(), glm::vec3(0.0f, 0.0f, 1.0f));
        EXPECT_VEC3_EQ(transform.GetRight(), glm::vec3(0.0f, -1.0f, 0.0f));
        EXPECT_VEC3_EQ(transform.GetUp(), glm::vec3(1.0f, 0.0f, 0.0f));

        // Z by 180°
        transform.SetPosition(glm::vec3(0.0f));
        transform.SetRotation(glm::vec3(0.0f, 0.0f, 180.0f));
        transform.SetScale(glm::vec3(1.0f));
        EXPECT_VEC3_EQ(transform.GetForward(), glm::vec3(0.0f, 0.0f, 1.0f));
        EXPECT_VEC3_EQ(transform.GetRight(), glm::vec3(-1.0f, 0.0f, 0.0f));
        EXPECT_VEC3_EQ(transform.GetUp(), glm::vec3(0.0f, -1.0f, 0.0f));

        // Z by 360°
        transform.SetPosition(glm::vec3(0.0f));
        transform.SetRotation(glm::vec3(0.0f, 0.0f, 360.0f));
        transform.SetScale(glm::vec3(1.0f));
        EXPECT_VEC3_EQ(transform.GetForward(), glm::vec3(0.0f, 0.0f, 1.0f));
        EXPECT_VEC3_EQ(transform.GetRight(), glm::vec3(1.0f, 0.0f, 0.0f));
        EXPECT_VEC3_EQ(transform.GetUp(), glm::vec3(0.0f, 1.0f, 0.0f));
    }

    TEST(TransformTest, DirectionsFormOrthonormalBasis)
    {
        Lumeda::Transform transform;

        // Some arbitrary rotation (not aligned to axes)
        transform.SetPosition(glm::vec3(1.0f, 2.0f, 3.0f));
        transform.SetRotation(glm::vec3(37.5f, 123.0f, -42.0f));
        transform.SetScale(glm::vec3(1.0f));

        glm::vec3 f = transform.GetForward();
        glm::vec3 r = transform.GetRight();
        glm::vec3 u = transform.GetUp();

        // Unit length
        EXPECT_NEAR(glm::length(f), 1.0f, ABS_ERROR);
        EXPECT_NEAR(glm::length(r), 1.0f, ABS_ERROR);
        EXPECT_NEAR(glm::length(u), 1.0f, ABS_ERROR);

        // Pairwise orthogonal
        EXPECT_NEAR(glm::dot(f, r), 0.0f, 1e-5f);
        EXPECT_NEAR(glm::dot(f, u), 0.0f, 1e-5f);
        EXPECT_NEAR(glm::dot(r, u), 0.0f, 1e-5f);

        // Right-handed basis: f x r should point roughly along u.
        glm::vec3 fxr = glm::cross(f, r);
        EXPECT_NEAR(fxr.x, u.x, 1e-4f);
        EXPECT_NEAR(fxr.y, u.y, 1e-4f);
        EXPECT_NEAR(fxr.z, u.z, 1e-4f);
    }
}