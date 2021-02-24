#ifndef ENJINCPPSDK_ENJINHOSTS_HPP
#define ENJINCPPSDK_ENJINHOSTS_HPP

#include "enjinsdk_export.h"

namespace enjin::sdk {

/// \brief The networks hosts used by the Enjin Cloud.
class ENJINSDK_EXPORT EnjinHosts {
public:
    /// \brief The URI for the kovan Enjin Cloud.
    constexpr static char KOVAN[] = "https://kovan.cloud.enjin.io/";

    /// \brief The URI for the main Enjin Cloud.
    constexpr static char MAIN_NET[] = "https://cloud.enjin.io/";
};

}

#endif //ENJINCPPSDK_ENJINHOSTS_HPP
