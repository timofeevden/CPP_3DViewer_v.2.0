#include "tests.h"

TEST(Affine, moving) {
  s21::Parser pars;
  std::string filename = "../../obj_test_file/cube.obj";
  pars.OpenFile(filename);

  s21::Affine aff;
  aff.SetArrayVertexes(pars.GetArrayVertexes());

  std::vector<s21::Vertex> expect_vertex = {
      {3.000000, 3.500000, -4.000000}, {3.000000, 3.500000, -2.000000},
      {1.000000, 3.500000, -2.000000}, {1.000000, 3.500000, -4.000000},
      {3.000000, 5.500000, -3.999999}, {2.999999, 5.500000, -1.999999},
      {1.000000, 5.500000, -2.000000}, {1.000000, 5.500000, -4.000000}};

  aff.MovingX(2);
  aff.MovingY(4.5);
  aff.MovingZ(-3);

  aff.SetPositionX(2);
  aff.SetPositionY(4.5);
  aff.SetPositionZ(-3);

  EXPECT_FLOAT_EQ(2, aff.GetPositionX());
  EXPECT_FLOAT_EQ(4.5, aff.GetPositionY());
  EXPECT_FLOAT_EQ(-3, aff.GetPositionZ());

  std::vector<s21::Vertex> vertex = aff.GetArrayVertexes();
  for (size_t i = 0; i < vertex.size(); ++i) {
    EXPECT_EQUAL_VERTEX(vertex[i], expect_vertex[i])
  }
}

TEST(Affine, rotation_x) {
  s21::Parser pars;
  std::string filename = "../../obj_test_file/cube.obj";
  pars.OpenFile(filename);

  s21::Affine aff;

  aff.SetArrayVertexes(pars.GetArrayVertexes());
  std::vector<s21::Vertex> expect_vertex = {
      {1.000000, 1.325444, -0.493151},   {1.000000, -0.493151, -1.325444},
      {-1.000000, -0.493151, -1.325444}, {-1.000000, 1.325444, -0.493151},
      {1.000000, 0.493150, 1.325444},    {0.999999, -1.325445, 0.493150},
      {-1.000000, -1.325444, 0.493151},  {-1.000000, 0.493151, 1.325444}};

  aff.RotationX(2);
  aff.SetRotateX(2);
  EXPECT_EQ(2, aff.GetRotateX());

  std::vector<s21::Vertex> vertex = aff.GetArrayVertexes();
  for (size_t i = 0; i < vertex.size(); ++i) {
    EXPECT_EQUAL_VERTEX(vertex[i], expect_vertex[i])
  }
}

TEST(Affine, rotation_y) {
  s21::Parser pars;
  std::string filename = "../../obj_test_file/cube.obj";
  pars.OpenFile(filename);

  s21::Affine aff;
  aff.SetArrayVertexes(pars.GetArrayVertexes());

  std::vector<s21::Vertex> expect_vertex = {
      {-1.325444, -1.000000, -0.493151}, {0.493151, -1.000000, -1.325444},
      {1.325444, -1.000000, 0.493151},   {-0.493151, -1.000000, 1.325444},
      {-1.325443, 1.000000, -0.493151},  {0.493152, 1.000000, -1.325444},
      {1.325444, 1.000000, 0.493151},    {-0.493151, 1.000000, 1.325444}};

  aff.RotationY(2);
  aff.SetRotateY(2);
  EXPECT_EQ(2, aff.GetRotateY());

  std::vector<s21::Vertex> vertex = aff.GetArrayVertexes();
  for (size_t i = 0; i < vertex.size(); ++i) {
    EXPECT_EQUAL_VERTEX(vertex[i], expect_vertex[i])
  }
}

TEST(Affine, rotation_z) {
  s21::Parser pars;
  std::string filename = "../../obj_test_file/cube.obj";
  pars.OpenFile(filename);

  s21::Affine aff;

  aff.SetArrayVertexes(pars.GetArrayVertexes());
  std::vector<s21::Vertex> expect_vertex = {
      {-1.325444, -0.493151, -1.0},     {-1.325444, -0.493151, 1.0},
      {-0.493151, 1.325444, 1.0},       {-0.493151, 1.325444, -1.0},
      {0.493151, -1.325444, -0.999999}, {0.493151, -1.325443, 1.000001},
      {1.325444, 0.493151, 1.0},        {1.325444, 0.493151, -1.0}};

  aff.RotationZ(2);
  aff.SetRotateZ(2);
  EXPECT_EQ(2, aff.GetRotateZ());

  std::vector<s21::Vertex> vertex = aff.GetArrayVertexes();
  for (size_t i = 0; i < vertex.size(); ++i) {
    EXPECT_EQUAL_VERTEX(vertex[i], expect_vertex[i])
  }
}

TEST(Affine, scaling) {
  s21::Parser pars;
  std::string filename = "../../obj_test_file/cube.obj";
  pars.OpenFile(filename);

  s21::Affine aff;
  aff.SetArrayVertexes(pars.GetArrayVertexes());

  std::vector<s21::Vertex> expect_vertex = {
      {2.000000, -2.000000, -2.000000}, {2.000000, -2.000000, 2.000000},
      {-2.000000, -2.000000, 2.000000}, {-2.000000, -2.000000, -2.000000},
      {2.000000, 2.000000, -1.999998},  {1.999998, 2.000000, 2.000002},
      {-2.000000, 2.000000, 2.000000},  {-2.000000, 2.000000, -2.000000}};

  aff.Scaling(2);
  aff.SetScaleRatio(2);
  EXPECT_EQ(2, aff.GetScaleRatio());

  std::vector<s21::Vertex> vertex = aff.GetArrayVertexes();
  for (size_t i = 0; i < vertex.size(); ++i) {
    EXPECT_EQUAL_VERTEX(vertex[i], expect_vertex[i])
  }

  aff.Scaling(1);
  aff.SetScaleRatio(1);
  EXPECT_EQ(1, aff.GetScaleRatio());
  aff.Scaling(2);
  aff.SetScaleRatio(2);
  EXPECT_EQ(2, aff.GetScaleRatio());

  for (size_t i = 0; i < vertex.size(); ++i) {
    EXPECT_EQUAL_VERTEX(vertex[i], expect_vertex[i])
  }
  aff.ResetPosition();
  EXPECT_EQ(1, aff.GetScaleRatio());
}

TEST(Affine, model) {
  s21::Model model;
  std::string filename = "../../obj_test_file/test_parcer.txt";
  model.LoadingFile(filename);

  std::vector<s21::Vertex> expect_vertex = {
      {1.65, 4.79324323, -3.139527},
      {2.1608108, 4.71283783, -3.007094588},
      {2.35, 4.20675677, -2.84155408},
      {1.6972973, 4.31081082, -3.15844592}};

  model.Moving(2, 4.5, -3);
  model.AddPosition(2, 4.5, -3);

  std::vector<s21::Vertex> vertex = model.GetArrayVertexes();
  for (size_t i = 0; i < vertex.size(); ++i) {
    EXPECT_EQUAL_VERTEX(vertex[i], expect_vertex[i])
  }

  model.ResetPosition();

  model.LoadingFile(filename);

  std::vector<s21::Vertex> expect_vertex_r = {
      {0.412296707, 0.196221857, -0.139527},
      {0.126611985, -0.234796636, -0.007094588},
      {-0.412296707, -0.196221857, 0.15844592},
      {-0.046060464, 0.353977265, -0.15844592}};

  model.Rotation(0, 0, 2);

  std::vector<s21::Vertex> vertex_r = model.GetArrayVertexes();
  for (size_t i = 0; i < vertex.size(); ++i) {
    EXPECT_EQUAL_VERTEX(vertex_r[i], expect_vertex_r[i])
  }

  model.Scaling(2);
  model.Scaling(1);
  for (size_t i = 0; i < vertex.size(); ++i) {
    EXPECT_EQUAL_VERTEX(vertex_r[i], expect_vertex_r[i])
  }
}
