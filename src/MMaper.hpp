//
// Copyright (c) 2017, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "SharedMemory.hpp"
#include "MMapOptions.hpp"
#include <tuple>

#ifndef __linux_posix_MMaper__
#define __linux_posix_MMaper__

namespace linux {
     namespace posix {
//////////////////////////////////////////////////////////////////
	  using UNMAP_AFTER_DESTROY = bool;
	  using MapInfo = std::tuple<void*, size_t>;
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
	  class MMaper {

	  public:
	       MMaper(const SharedMemory&,
		      const UNMAP_AFTER_DESTROY = false,
		      const MMapOptions = MMapOptions());
	       ~MMaper();

	       MMaper(const MMaper&) = delete;
	       MMaper& operator= (const MMaper&) = delete;
	       MMaper(const MMaper&&) = delete;
	       MMaper& operator= (const MMaper&&) = delete;

	       MapInfo map();
	       MapInfo map(const size_t);
	       void unmap() const;

	  private:
	       const SharedMemory& memory;
	       const UNMAP_AFTER_DESTROY unmap_mode;
	       MMapOptions options;

	       void* addr;
	       size_t mmap_size;

	       void error(const int) const;
	       MapInfo maping(const size_t);
	  };
//////////////////////////////////////////////////////////////////
     }
}
#endif // __linux_posix_MMaper__
