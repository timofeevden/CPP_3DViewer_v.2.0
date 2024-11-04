#include "tests.h"

TEST(Parser, test_1) {
  s21::Parser pars;
  std::string filename = "../../obj_test_file/cube.obj";
  pars.OpenFile(filename);

  EXPECT_EQ(pars.GetVertexes(), 8);
  EXPECT_EQ(pars.GetPolygons(), 12);

  std::string filename_2 = "../../obj_test_file/Wolf_obj.obj";
  pars.OpenFile(filename_2);

  EXPECT_EQ(pars.GetVertexes(), 1690);
  EXPECT_EQ(pars.GetPolygons(), 1566);
}

TEST(Parser, test_2) {
  s21::Parser pars;
  std::string filename = "nofile.obj";
  pars.OpenFile(filename);

  EXPECT_EQ(pars.GetError(), 1);
}

TEST(Parser, test_3) {
  s21::Parser pars;
  std::vector<s21::Vertex> expect_vertex = {{-0.55, 0.67, 0.15},
                                            {0.53, 0.5, 0.43},
                                            {0.93, -0.57, 0.78},
                                            {-0.45, -0.35, 0.11}};
  std::vector<s21::Polygon> expect_polygon = {{0, 1}, {1, 2}, {2, 0}, {1, 2},
                                              {2, 0}, {0, 3}, {3, 1}};

  std::string filename = "../../obj_test_file/test_parcer.txt";
  pars.OpenFile(filename);

  EXPECT_EQ(pars.GetVertexes(), 4);
  EXPECT_EQ(pars.GetPolygons(), 2);

  std::vector<s21::Vertex> vertex = pars.GetArrayVertexes();
  for (size_t i = 0; i < vertex.size(); i++) {
    EXPECT_EQUAL_VERTEX(vertex[i], expect_vertex[i]);
  }

  std::vector<s21::Polygon> polygons = pars.GetArrayPolygons();
  for (size_t i = 0; i < polygons.size(); i++) {
    EXPECT_EQUAL_POLYGONS(polygons[i], expect_polygon[i]);
  }
}

TEST(Parser, test_4) {
  s21::Parser pars;
  std::string filename = "../../obj_test_file/test_parcer_2.txt";
  pars.OpenFile(filename);

  EXPECT_EQ(pars.GetError(), 2);

  filename = "../../obj_test_file/test_parcer_3.txt";
  pars.OpenFile(filename);

  EXPECT_EQ(pars.GetError(), 3);

  filename = "../../obj_test_file/test_parcer_4.txt";
  pars.OpenFile(filename);

  EXPECT_EQ(pars.GetError(), 4);
}

TEST(Model, test_1) {
  s21::Model model;  //  с центровкой
  std::vector<s21::Vertex> expect_vertex = {
      {-0.35, 0.29324323, -0.139527},
      {0.1608108, 0.21283783, -0.0070945877},
      {0.35, -0.29324323, 0.15844592},
      {-0.3027027, -0.18918918, -0.15844592}};

  std::vector<s21::Polygon> expect_polygon = {{0, 1}, {1, 2}, {2, 0}, {1, 2},
                                              {2, 0}, {0, 3}, {3, 1}};

  std::string filename = "../../obj_test_file/test_parcer.txt";
  model.LoadingFile(filename);

  EXPECT_EQ(model.GetCntVertexes(), 4);
  EXPECT_EQ(model.GetCntPolygons(), 2);
  EXPECT_FLOAT_EQ(model.GetRange().x_min, -0.55);
  EXPECT_FLOAT_EQ(model.GetRange().x_max, 0.93);
  EXPECT_FLOAT_EQ(model.GetRange().y_min, -0.57);
  EXPECT_FLOAT_EQ(model.GetRange().y_max, 0.67);
  EXPECT_FLOAT_EQ(model.GetRange().z_min, 0.11);
  EXPECT_FLOAT_EQ(model.GetRange().z_max, 0.78);

  std::vector<s21::Vertex> vertex(model.GetArrayVertexes());

  for (auto i = 0; i < model.GetCntVertexes(); ++i) {
    EXPECT_EQUAL_VERTEX(vertex[i], expect_vertex[i]);
  }

  std::vector<s21::Polygon> polygons = model.GetArrayPolygons();

  for (size_t i = 0; i < polygons.size(); ++i) {
    EXPECT_EQUAL_POLYGONS(polygons[i], expect_polygon[i]);
  }
}
