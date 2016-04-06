/*
 * Copyright (c) 2008-2016 the MRtrix3 contributors
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/
 *
 * MRtrix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * For more details, see www.mrtrix.org
 *
 */

#ifndef __registration_warp_utils_h__
#define __registration_warp_utils_h__

namespace MR
{
  namespace Registration
  {

    namespace Warp
    {

      template <class InputWarpType>
      transform_type parse_linear_transform (InputWarpType& input_warps, std::string name) {
        transform_type linear;
        const auto it = input_warps.keyval().find (name);
        if (it != input_warps.keyval().end()) {
          const auto lines = split_lines (it->second);
          if (lines.size() != 3)
            throw Exception ("linear transform in initialisation syn warps image headerdoes not contain 3 rows");
          for (size_t row = 0; row < 3; ++row) {
            const auto values = MR::split (lines[row], " ");
            if (values.size() != 4)
              throw Exception ("linear transform in initialisation syn warps image header does not contain 4 rows");
            for (size_t col = 0; col < 4; ++col)
              linear (row, col) = std::stod (values[col]);
          }
        } else {
          throw Exception ("no linear transform found in initialisation syn warps image header");
        }

        return linear;
      }

    }
  }
}

#endif
