#include <DDImage/SourceGeo.h>
#include <DDImage/GeometryList.h>
#include <DDImage/Primitive.h>
#include <DDImage/Vector3.h>
#include <DDImage/Scene.h>

using namespace DD::Image;

class GridNode : public SourceGeo {
public:
    GridNode(Node* node) : SourceGeo(node) {}

    void get_geometry(Scene& scene, GeometryList& out) override {
        int rows = 20;
        int cols = 20;
        float spacing = 1.0f;

        Primitive* geo = out.add_primitive();

        // Add grid vertices
        for (int i = 0; i <= rows; ++i) {
            for (int j = 0; j <= cols; ++j) {
                float x = j * spacing;
                float z = i * spacing;
                geo->add_point(Vector3(x, 0.0f, z));
            }
        }

        // Add grid faces (quads)
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int p0 = i * (cols + 1) + j;
                int p1 = p0 + 1;
                int p2 = p0 + (cols + 1);
                int p3 = p2 + 1;

                geo->add_face(p0, p1, p3, p2); // Quad face
            }
        }
    }

    static Op* create(Node* node) {
        return new GridNode(node);
    }

    const char* Class() const override { return "GridNode"; }
    const char* node_help() const override { return "Creates a 20x20 grid."; }
};

static const Op::Description description(
    "GridNode", 
    "Geometry/GridNode", 
    GridNode::create
);