// [Fog-Svg]
//
// [License]
// MIT, See COPYING file in package

// [Guard]
#ifndef _FOG_SVG_TOOLS_SVGUTIL_H
#define _FOG_SVG_TOOLS_SVGUTIL_H

// [Dependencies]
#include <Fog/Core/Tools/Char.h>
#include <Fog/Core/Tools/List.h>
#include <Fog/Core/Tools/String.h>
#include <Fog/G2d/Geometry/Path.h>
#include <Fog/G2d/Geometry/Transform.h>
#include <Fog/G2d/Source/Color.h>
#include <Fog/Svg/Tools/SvgCoord.h>

namespace Fog {
namespace SvgUtil {

//! @addtogroup Fog_Svg_Tools
//! @{

// ============================================================================
// [Fog::SvgUtil - Parse]
// ============================================================================

//! @brief Parse SVG color and save it to @a dst. This method can also check
//! whether a given string is 'none' or URI to pattern definition.
//!
//! @return One of @c SVG_SOURCE_TYPE enumeration value is returned.
FOG_API uint32_t parseColor(Color& dst, const StringW& str);

//! @brief Parse SVG opacity value: 0.0 to 1.0 or 0% to 100% and clamp it if.
//! needed.
FOG_API err_t parseOpacity(float& dst, const StringW& str);

//! @brief Parse SVG matrix and save it to @a dst.
FOG_API err_t parseTransform(TransformF& dst, const StringW& str);

//! @brief Parse SVG coordinate and return it.
FOG_API err_t parseCoord(SvgCoord& coord, const StringW& str);

FOG_API err_t parseViewBox(BoxF& box, const StringW& str);

FOG_API err_t parsePoints(PathF& dst, const StringW& str, bool closePath);
FOG_API err_t parsePath(PathF& dst, const StringW& str);

// ============================================================================
// [Fog::SvgUtil - Serialize]
// ============================================================================

//! @brief Serialize SVG color using #RRGGBB notation.
FOG_API err_t serializeColor(StringW& dst, const Color& color);

//! @brief Serialize SVG coordinate to string.
FOG_API err_t serializeCoord(StringW& dst, const SvgCoord& coord);

//! @}

} // SvgUtil namespace
} // Fog namespace

// [Guard]
#endif // _FOG_SVG_TOOLS_SVGUTIL_H
