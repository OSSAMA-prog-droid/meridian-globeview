// Meridian GlobeView — minimal frame-loop harness that wires the renderer
// together. With the stub GL layer this runs without a GPU; swap in a real
// loader and window to drive it on-screen.

#include "render/Camera.h"
#include "render/ColorPipeline.h"
#include "render/TileRenderer.h"
#include "render/TerrainMesh.h"
#include "render/OverlayRenderer.h"
#include "render/MarkerBuffer.h"
#include "render/FrameGraph.h"
#include "cache/TileCache.h"

#include <cstdio>
#include <vector>

using namespace gv;

int main() {
  Camera camera;
  camera.setViewport(1280, 720);
  camera.setTarget({ 37.7749, -122.4194 }, 2000.0);  // San Francisco, 2 km out

  ColorPipeline color;
  TileRenderer  tiles;
  TileCache     cache;
  OverlayRenderer overlays;
  MarkerBuffer  markers;
  FrameGraph    frame;

  markers.init(4096);

  for (int f = 0; f < 3; ++f) {
    color.beginColorPass();

    Mat4f view = camera.viewMatrix();
    Mat4f proj = camera.projectionMatrix();
    (void)view; (void)proj;

    TileKey key{ 12, 655, 1585 };
    cache.getOrLoad(key);
    auto quad = tiles.buildTileQuad(key);
    (void)quad;

    PolygonRing zone{ { {37.70, -122.52}, {37.83, -122.52}, {37.83, -122.36}, {37.70, -122.36} } };
    auto tris = overlays.triangulate(zone);

    std::vector<OverlayDraw> draws;
    draws.push_back(OverlayDraw{ 1, {}, static_cast<int>(tris.size()), Mat4f::identity() });
    frame.renderOverlays(draws);

    std::vector<Marker> positions{ { 1, 37.7749, -122.4194 } };
    markers.updatePositions(positions);
    markers.draw();

    camera.applyDragRotation(1.0, 0.5);
  }

  std::printf("GlobeView frame loop complete — %zu tiles cached.\n", cache.size());
  return 0;
}
