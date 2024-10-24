#include <cstdint>
#include <sstream>

#include "map_renderer.h"

MapRenderer::MapRenderer(RenderSets rs) : render_sets_(rs) {}

svg::Polyline MapRenderer::MakeRenderPolyline(const std::vector<const domain::Stop *> &stops, const SphereProjector &point_mapper, const size_t& pallet_num) const {
    svg::Polyline line;
    const size_t pallet_count = render_sets_.color_palette.size();
    for (const auto &stop : stops) {
        line.AddPoint(point_mapper((*stop).coordinate));
    }
    line.SetFillColor("none").SetStrokeColor(render_sets_.color_palette.at(pallet_num%pallet_count)).SetStrokeLineCap(svg::StrokeLineCap::ROUND).SetStrokeLineJoin(svg::StrokeLineJoin::ROUND).SetStrokeWidth(render_sets_.line_width);
    return line;
}

void MapRenderer::Render(std::vector<svg::Polyline> &polyline, std::ostream &out) const {
    svg::Document doc;
    for (auto line : polyline) {
        doc.Add(std::move(line));
    }
    doc.Render(out);
}

const RenderSets &MapRenderer::GetSets() const {
    return render_sets_;
}