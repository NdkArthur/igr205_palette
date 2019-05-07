#pragma once

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>
#include <QVector2D>
#include <vector>
#include <memory>
#include <QOpenGLTexture>
#include "alignedbox.hh"

class QOpenGLShaderProgram;

class Model
{
public:
  static std::unique_ptr<Model> load(const char *filename);

  void drawScene(int s, QOpenGLShaderProgram &prog);
  AlignedBox sceneAlignedBox(int s);

private:
  struct Material
  {
    QVector4D base_color_factor = QVector4D(1, 1, 1, 1);
    std::unique_ptr<QOpenGLTexture> color_map;

    QVector2D metallic_roughness_values = QVector2D(1, 1);
    bool has_occlusion_map = false;
    float occlusion_strength = 1.0;
    std::unique_ptr<QOpenGLTexture> metallic_roughness_map;

    std::unique_ptr<QOpenGLTexture> normal_map;

    QVector3D emissive_factor = QVector3D(1, 1, 1);
    std::unique_ptr<QOpenGLTexture> emissive_map;
  };

  struct Primitive
  {
    int vao_id;
    int material_id;
    GLenum mode;
    size_t count;
    GLenum component_type;
    size_t offset;
    AlignedBox aabb;
  };

  struct Node
  {
    QMatrix4x4 transform;
    std::vector<int> children;
    int first_primitive = -1;
    int primitive_number = 0;
  };

  struct Scene
  {
    std::vector<int> nodes;
  };

  void drawNode(const Node &node, QOpenGLShaderProgram &prog, const QMatrix4x4 &transform);
  void drawPrimitive(const Primitive &primitive, QOpenGLShaderProgram &prog, const QMatrix4x4 &transform);
  AlignedBox nodeAlignedBox(const Node &node, const QMatrix4x4 &transform);

  std::vector<Scene> scenes_;
  std::vector<Node> nodes_;
  std::vector<std::unique_ptr<QOpenGLBuffer>> buffers_;
  std::vector<std::unique_ptr<QOpenGLVertexArrayObject>> vertex_arrays_;
  std::vector<Primitive> primitives_;
  std::vector<Material> materials_;
};