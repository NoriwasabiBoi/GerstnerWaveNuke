//
// Created by Robin Lemke on 12.12.24.
//

#include "DDImage/SourceGeo.h"
#include "DDImage/Scene.h"
#include "DDImage/Knobs.h"

using namespace DD::Image;

class GridNode : public SourceGeo {
private:
    int rows_;
    int cols_;
    float size_;

public:
    GridNode(Node* node) : SourceGeo(node), rows_(20), cols_(20), size_(1.0f) {}

    const char* Class() const override { return "GridNode"; }
    const char* node_help() const override { return "Generates a 20x20 grid geometry."; }

    // Add knobs (parameters) for grid customization
    void knobs(Knob_Callback f) override {
        Int_knob(f, &rows_, "rows", "Rows");
        Tooltip(f, "Number of rows in the grid.");
        Int_knob(f, &cols_, "cols", "Columns");
        Tooltip(f, "Number of columns in the grid.");
        Float_knob(f, &size_, "size", "Size");
        Tooltip(f, "Size of the grid (length of one side).");
    }

    // Generate geometry
    void get_geometry(Scene& scene, GeometryList& out) override {
        Geometry* geo = out.add_geometry();
        geo->clear();
        geo->add_points((rows_ + 1) * (cols_ + 1)); // Allocate points

        // Calculate spacing
        float step_x = size_ / cols_;
        float step_z = size_ / rows_;

        // Generate vertices
        for (int i = 0; i <= rows_; ++i) {
            for (int j = 0; j <= cols_; ++j) {
                float x = j * step_x - size_ / 2.0f; // Centered on origin
                float z = i * step_z - size_ / 2.0f;
                geo->set_point(i * (cols_ + 1) + j, Point(x, 0.0f, z));
            }
        }

        // Generate faces (quads)
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                int idx1 = i * (cols_ + 1) + j;
                int idx2 = idx1 + 1;
                int idx3 = idx1 + (cols_ + 1);
                int idx4 = idx3 + 1;
                geo->add_face({idx1, idx2, idx4, idx3});
            }
        }
    }
};

// Register the node
static const Op::Description description("GridNode", GridNode::create);
