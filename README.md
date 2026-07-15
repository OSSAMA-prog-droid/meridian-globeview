# Meridian GlobeView

The C++17 / OpenGL real-time 3D map client for the Meridian fleet platform. It
streams Web Mercator tiles, renders terrain with level-of-detail, draws
country/zone overlays, and tracks thousands of live vehicle markers on a
planet-scale scene.

> The world is ~40,000,000 metres across and the camera goes from continent view
> down to a single street. Most bugs here live at the edges: far from the origin,
> near the poles, across the date line, or under a flood of concurrent updates.
> "It looks fine on my machine, in my city" is where they hide.

## Layout

```
include/globeview/     Shared types — math, geo/mercator, a thin GL layer
src/render/            Rendering pipeline (camera, tiles, terrain, overlays, markers)
src/cache/             GPU resource caches
src/main.cpp           App entry point / frame loop
```

## Building

```bash
cmake -S . -B build
cmake --build build
```

The GL entry points are declared in `include/globeview/Gl.h`. For offline builds
and CI they resolve to lightweight stubs (`GLOBEVIEW_STUB_GL`, on by default), so
the project compiles and the logic can be exercised without a GPU/driver. Wire in
a real loader (GLAD/GLEW) by defining `-DGLOBEVIEW_STUB_GL=0` and linking it.

## Modules

| Area | Files |
|------|-------|
| Camera & projection | `src/render/Camera.*`, `src/render/DepthConfig.h` |
| Tile rendering | `src/render/TileRenderer.*`, `src/render/TextureUpload.*` |
| Color | `src/render/ColorPipeline.*` |
| Terrain | `src/render/TerrainMesh.*` |
| Overlays | `src/render/OverlayRenderer.*` |
| Live markers | `src/render/MarkerBuffer.*` |
| Frame submission | `src/render/FrameGraph.*` |
| Tile GPU cache | `src/cache/TileCache.*` |
